#ifndef Rcpp__protection_Armor_h
#define Rcpp__protection_Armor_h

namespace Rcpp{
    
    template <typename T>
    class Armor {
    public:
        
        Armor() : data(R_NilValue), index(-1) {}
        
        Armor( SEXP x ) {
            init(x) ;
        }
        
        Armor(Armor&& other ) {
            index = other.index ;
            data = other.data ;
            
            other.index = -1 ;
            other.data = R_NilValue ;
        }
        
        Armor(const Armor&) = delete ;
        Armor& operator=(const Armor&) = delete ;
        
        inline operator SEXP() const {
            return data ;
        }
              
        template <typename U>
        inline Armor& operator=( const U& x ) {
            if( index < 0 ){
                init( wrap(x) ) ;
            } else {
                REPROTECT(data = wrap(x), index) ;
            }
            return *this ;    
        }
        
        ~Armor(){
            if( index >= 0 ) UNPROTECT_PTR(data) ;
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
