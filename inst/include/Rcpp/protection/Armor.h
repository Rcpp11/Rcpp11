#ifndef Rcpp__protection_Armor_h
#define Rcpp__protection_Armor_h

namespace Rcpp{
    
    template <typename T>
    class Armor {
    public:
        
        Armor() {
            init(R_NilValue) ;    
        }
        
        template <typename U> 
        Armor( U x ) {
            init( wrap(x) ) ;
        }
        
        Armor(const Armor&) = delete ;
        Armor& operator=(const Armor&) = delete ;
        
        inline operator SEXP() const {
            return data ;
        }
              
        template <typename U>
        inline Armor& operator=( U x ) {
            REPROTECT(data = wrap(x), index) ;
            return *this ;    
        }
        
        ~Armor(){
            UNPROTECT(1) ;
        }
        
    private:
        void init(SEXP x){
           PROTECT_WITH_INDEX( data = x, &index ) ;     
        }
        
        SEXP data ;
        PROTECT_INDEX index ;
         
    } ;
    
}

#endif
