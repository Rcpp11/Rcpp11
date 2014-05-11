#ifndef Rcpp_NamedDots_h
#define Rcpp_NamedDots_h

namespace Rcpp{ 
    
    template <typename Storage>
    class NamedDots_Impl {
    public:
        typedef Environment_Impl<Storage> Environment ;
        typedef Promise_Impl<Storage> Promise ;
        
        NamedDots_Impl( Environment env ){
            SEXP dots = env.find("...") ;
            while(dots != R_NilValue){
                promises.push_back(CAR(dots)) ;
                SEXP tag = TAG(dots) ;
                if(tag==R_NilValue) 
                    stop("unnamed contribution to ... in NamedDots") ; 
                symbols.push_back(tag) ;
                dots = CDR(dots);
            }
        }
        
        inline int size() const {
            return promises.size() ;    
        }
        
        inline Promise& promise(int i) {
            return promises[i] ;
        }
        
        inline Environment environment(int i){
            return promises[i].environment() ;    
        }
        
        inline Symbol& symbol(int i){
            return symbols[i] ;
        }
        
    private:
        std::vector<Promise> promises ;   
        std::vector<Symbol> symbols ;
    } ;
    
    typedef NamedDots_Impl<NoProtectStorage> NamedDots ; 
    
}

#endif
