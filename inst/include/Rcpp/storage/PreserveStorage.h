#ifndef Rcpp_storage_PreserveStorage_h
#define Rcpp_storage_PreserveStorage_h

namespace Rcpp{ 

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
        
    private:
        SEXP data ;
        
    } ;
    
}

#endif
