#ifndef Rcpp_storage_PreserveStorage_h
#define Rcpp_storage_PreserveStorage_h

namespace Rcpp{ 

    inline SEXP Rcpp_PreserveObject(SEXP x){
        if( x != R_NilValue ) {
            R_PreserveObject(x);
        }
        return x ;
    }

    inline void Rcpp_ReleaseObject(SEXP x){
        if (x != R_NilValue) {
            R_ReleaseObject(x);
        }
    }

    inline SEXP Rcpp_ReplaceObject(SEXP x, SEXP y){
        if( x == R_NilValue ){
            Rcpp_PreserveObject( y ) ;
        } else if( y == R_NilValue ){
            Rcpp_ReleaseObject( x ) ;
        } else {
            // if we are setting to the same SEXP as we already have, do nothing
            if (x != y) {

                // the previous SEXP was not NULL, so release it
                Rcpp_ReleaseObject(x);

                // the new SEXP is not NULL, so preserve it
                Rcpp_PreserveObject(y);
            }
        }
        return y ;
    }
    
    class PreserveStorage {
    public:
        
        // default ctor: set data to R_NilValue
        PreserveStorage() : data(R_NilValue){}
        
        // SEXP ctor: we protect the data
        PreserveStorage(SEXP data_) : data(Rcpp_PreserveObject(data_)){}
        
        // destructor : we release the data
        ~PreserveStorage(){
            Rcpp_ReleaseObject(data) ;
            data = R_NilValue;
        }
        
        // copy constructor: we protect again
        PreserveStorage(const PreserveStorage& other ) : data( Rcpp_PreserveObject(other.data) ){}
        
        // move constructor: we steal data
        PreserveStorage(PreserveStorage&& other) : data(other.data){
            other.data = R_NilValue ;    
        }
        
        // assignment : we release the previous data, and protect again the one from other
        PreserveStorage& operator=(const PreserveStorage& other) {
            Rcpp_ReplaceObject( data, other.data ) ;
            data = other.data ;
            return *this ;
        }
        
        // move assignment: we just steal data
        PreserveStorage& operator=(PreserveStorage&& other) {
            data = other.data ; other.data = R_NilValue ;
            return *this ;
        }
        
        inline operator SEXP() const { return data; }
        
        inline PreserveStorage& operator=( SEXP x){
            data = Rcpp_ReplaceObject(data, x) ;
            return *this ;
        }
        
        // allowing Shield to be used with R internals macros
        inline SEXP operator->() const {
            return data;
        }
        
    private:
        SEXP data ;
        
    } ;
    
    
}

#endif
