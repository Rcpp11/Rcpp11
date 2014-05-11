#ifndef Rcpp_Dots_h
#define Rcpp_Dots_h

namespace Rcpp{ 
    
    template <typename Storage>
    class Dots_Impl {
    public:
        typedef Environment_Impl<Storage> Environment ;
        typedef Promise_Impl<Storage> Promise ;
        
        Dots_Impl( Environment env){
            SEXP dots = env.find("...") ;
            if( dots != R_MissingArg ){ 
                while(dots != R_NilValue){
                    promises.push_back(CAR(dots)) ;
                    dots = CDR(dots);
                }
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
        
    private:
        
        std::vector<Promise> promises ;
    } ;
    
    typedef Dots_Impl<NoProtectStorage> Dots ;
    
}

#endif
