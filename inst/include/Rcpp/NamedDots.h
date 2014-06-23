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
            if( dots != R_MissingArg ){
                while(dots != R_NilValue){
                    promises.push_back(CAR(dots)) ;
                    SEXP tag = TAG(dots) ;
                    if(tag==R_NilValue) 
                        stop("unnamed contribution to ... in NamedDots") ; 
                    symbols.push_back(tag) ;
                    dots = CDR(dots);
                }
            }
        }
        
        inline R_xlen_t size() const {
            return promises.size() ;    
        }
        
        inline Promise& promise(R_xlen_t i) {
            return promises[i] ;
        }
        
        inline Environment environment(R_xlen_t i){
            return promises[i].environment() ;    
        }
        
        inline Symbol& symbol(R_xlen_t i){
            return symbols[i] ;
        }
        
    private:
        std::vector<Promise> promises ;   
        std::vector<Symbol> symbols ;
    } ;
    
    typedef NamedDots_Impl<NoProtectStorage> NamedDots ; 
    
}

#endif
