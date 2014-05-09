#ifndef Rcpp_storage_NoProtectStorage_h
#define Rcpp_storage_NoProtectStorage_h

namespace Rcpp{ 

    template <typename CLASS>
    class NoProtectStorage {
    public:
        NoProtectStorage(): data(R_NilValue){}
        NoProtectStorage(SEXP data_) : data(data_){}
        inline NoProtectStorage& operator=(SEXP x){ 
            data = x ;
            return *this ;
        }
        inline operator SEXP() const { return data; }
        
    private:
        SEXP data ;
        
    } ;
    
}

#endif
