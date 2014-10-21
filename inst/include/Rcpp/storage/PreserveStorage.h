#ifndef Rcpp_storage_PreserveStorage_h
#define Rcpp_storage_PreserveStorage_h

namespace Rcpp{ 

    
    #ifndef RCPP11_EXPERIMENTAL_PRESERVE
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
    
    #else 
    static SEXP* PreserveListData ;
    static int PreserveListTop ;
    
    inline SEXP* get_preserve_list(){
        if( ! PreserveListData ){
            SEXP v = Rf_allocVector(VECSXP, 1024) ;
            R_PreserveObject(v) ;
            PreserveListData = VECTOR_PTR(v) ;
            PreserveListTop = 0 ;
        }
        return PreserveListData ;
    }
    
    inline int preserve_object(SEXP x){
        get_preserve_list()[PreserveListTop++] = x ;
        return PreserveListTop ;
    }
    
    inline void release_object(SEXP x, int hint){
        SEXP* data = get_preserve_list() ;
        if( x == R_NilValue ) return ;
        
        // goes down the PreserveListData from the hint
        for( ; hint >= 0 && data[hint] == x; hint--) ;
        
        if( hint < 0 ) return ;
        
        // move down the objects that are
        // TODO: use memmove instead
        for( ; hint < PreserveListTop-1; hint++){
            data[hint] = data[hint+1] ;
        }
        
    }
    
    inline int replace_object(SEXP x, SEXP y, int hint){
        if( x == R_NilValue ) return preserve_object(y) ;
        if( y != R_NilValue ){ 
            SEXP* data = get_preserve_list() ;
            for( ; hint >= 0 && data[hint] != x; hint--) ;
            data[hint] = y ; 
        }
        return hint ;
    }
    
    class PreserveStorage {
    public:
        
        // default ctor: set data to R_NilValue
        PreserveStorage() : data(R_NilValue){}
        
        // SEXP ctor: we protect the data
        PreserveStorage(SEXP data_) : data(data_){
            hint = preserve_object(data) ;
        }
        
        // destructor : we release the data
        ~PreserveStorage(){
            release_object(data, hint) ;
        }
        
        // copy constructor: we protect again
        PreserveStorage(const PreserveStorage& other ) : 
            data(other.data)
        {
            hint = preserve_object(data) ;    
        }
        
        // move constructor: we steal data
        PreserveStorage(PreserveStorage&& other) : data(other.data), hint(other.hint){
            other.data = R_NilValue ;
        }
        
        // assignment : we release the previous data, and protect again the one from other
        PreserveStorage& operator=(const PreserveStorage& other) {
            hint = replace_object( data, other.data, hint ) ;
            data = other.data ;
            return *this ;
        }
        
        // move assignment: we just steal data
        PreserveStorage& operator=(PreserveStorage&& other) {
            data = other.data ; 
            hint = other.hint ;
            other.data = R_NilValue ;
            return *this ;
        }
        
        inline operator SEXP() const { return data; }
        
        inline PreserveStorage& operator=( SEXP x){
            hint = replace_object(data, x, hint) ;
            data = x ;
            return *this ;
        }
        
        // allowing Shield to be used with R internals macros
        inline SEXP operator->() const {
            return data;
        }
        
    private:
        SEXP data ;
        int hint ;
    } ;
    #endif

}

#endif
