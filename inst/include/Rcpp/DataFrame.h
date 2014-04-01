#ifndef Rcpp__DataFrame_h
#define Rcpp__DataFrame_h

namespace Rcpp{
      
    template < template <class> class StoragePolicy>
    class DataFrame_Impl : public Vector<VECSXP, StoragePolicy> {
    public:    
        using Storage = typename Vector<VECSXP, StoragePolicy>::Storage ;
        
        DataFrame_Impl() ;
        DataFrame_Impl(SEXP x) ;
        DataFrame_Impl( const DataFrame_Impl& other) ;
                
        template <typename T> DataFrame_Impl( const T& obj) ; 
                
        DataFrame_Impl& operator=( DataFrame_Impl& other) ;
        DataFrame_Impl& operator=( SEXP x)  ;
                
        ~DataFrame_Impl() ;

        int nrows() const {
            SEXP att = ATTRIB( Storage::get__() ); 
            while( att != R_NilValue ){
                if( TAG(att) == R_RowNamesSymbol ){
                    SEXP rn = CAR(att) ; 
                    if( TYPEOF(rn) == INTSXP && LENGTH(rn) == 2 && INTEGER(rn)[0] == NA_INTEGER ) return -INTEGER(rn)[1] ;
                    return LENGTH(rn) ;        
                }
                att = CDR(att) ;    
            }
            return 0 ;
        }
        
        template <typename... Args>
        static DataFrame_Impl create(const Args&... args){
            return from_list( List::create( args...) ) ;
        }

    private:
        void set_sexp(SEXP x) ;
        static DataFrame_Impl from_list( Rcpp::List ) ;
        
    } ;
        
}

#endif
