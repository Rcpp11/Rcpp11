#ifndef Rcpp_storage_NoProtectStorage_h
#define Rcpp_storage_NoProtectStorage_h

namespace Rcpp{ 

    class NoProtectStorage {
    public:
        NoProtectStorage(): data(R_NilValue){}
        NoProtectStorage(SEXP data_) : data(data_){}
        inline NoProtectStorage& operator=(SEXP x){ 
            data = x ;
            return *this ;
        }
        inline operator SEXP() const { return data; }
        
        // allowing Shield to be used with R internals macros
        inline SEXP operator->() const {
            return data;
        }
        
    private:
        SEXP data ;
        
    } ;
    
}

#endif
