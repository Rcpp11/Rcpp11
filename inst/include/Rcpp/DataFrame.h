#ifndef Rcpp__DataFrame_h
#define Rcpp__DataFrame_h

namespace Rcpp{
     
    namespace internal{
        
        template <typename Data> 
        class DataFrameProxy : public GenericProxy<DataFrameProxy<Data>>{
        public:
            friend class Proxy_Iterator<DataFrameProxy> ;
            
            DataFrameProxy( Data& v, int i ) : parent(v), index(i){}
    
            DataFrameProxy& operator=(SEXP rhs) { 
                set(rhs) ;
                return *this ;
            }
        
            DataFrameProxy& operator=(const DataFrameProxy& rhs) {
                set(rhs.get());
                return *this ;
            }
    
            template <typename T>
            DataFrameProxy& operator=( const T& rhs){
                set(wrap(rhs)) ;
                return *this; 
            }
        
            inline operator SEXP() const { 
                return get() ;
            }
            inline operator bool() const { 
                return ::Rcpp::as<bool>(get()) ; 
            }
            inline operator int() const { 
                return ::Rcpp::as<int>(get()) ; 
            }
        
            template <typename U> 
            inline operator U() const {
                return ::Rcpp::as<U>(get()) ;
            }
            
            friend inline void swap( DataFrameProxy& a, DataFrameProxy& b){
                Shield<SEXP> tmp = a.get() ;
                a.set( b.get() ) ;
                b.set(tmp) ;    
            }
            
        private:
            
            Data& parent; 
            int index ;
            
            inline void set(SEXP x) {
                if( XLENGTH(x) == parent.nrows() ){
                    SET_VECTOR_ELT( parent, index, x ) ;
                } else {
                    List v = (SEXP)parent ;
                    v[index] = x ;
                    parent = Data( (SEXP)v ) ;
                }
            } 
            inline SEXP get() const { 
                return VECTOR_ELT(parent, index ); 
            } 
        
        }  ;
    
    }
    
    template <typename Storage>
    class DataFrame_Impl {
        public:
            friend class internal::DataFrameProxy<DataFrame_Impl> ;
            
            typedef internal::DataFrameProxy<DataFrame_Impl> Proxy ;
            typedef internal::Proxy_Iterator<Proxy> iterator  ; 
        
        RCPP_API_IMPL(DataFrame_Impl)    
            
        inline void set(SEXP x){
            if( inherits( x, "data.frame" )){
                data = x ;
            } else{
                data = as_data_frame(x) ;
            }          
        }
        
        DataFrame_Impl() : data(empty_data_frame()){}
        
        int nrows() const {
            SEXP att = ATTRIB( data ); 
            while( att != R_NilValue ){
                if( TAG(att) == R_RowNamesSymbol ){
                    SEXP rn = CAR(att) ; 
                    if( TYPEOF(rn) == INTSXP && LENGTH(rn) == 2 && INTEGER(rn)[0] == NA_INTEGER ) return abs(INTEGER(rn)[1]) ;
                    return LENGTH(rn) ;        
                }
                att = CDR(att) ;    
            }
            return 0 ;
        }
        
        template <typename... Args>
        static DataFrame_Impl create( Args&&... args){
            List l = list( std::forward<Args>(args)... ) ;
            return DataFrame_Impl( (SEXP)l ) ;
        }
          
        #define Vector DataFrame
        #include <Rcpp/vector/impl/RCPP_VECTOR_PROXY_BASED_API.h>
        #undef Vector
        
        inline R_xlen_t length() const { return XLENGTH((SEXP)data) ; }
        inline R_xlen_t size() const { return length() ; }
        
        R_xlen_t offset(const std::string& name) const {
            SEXP names = RCPP_GET_NAMES(data) ;
            R_xlen_t n = size() ;
        
            SEXP* data = internal::r_vector_start<STRSXP>(names) ;
            R_xlen_t index = std::find( data, data+n, Rf_mkChar(name.c_str()) ) - data ;
            if( index == n ) stop("no such column name '%s'", name) ;
            return index ;
        }
    
        class NameProxy {
        public:
            NameProxy(DataFrame& parent_, const std::string& name_): parent(parent_), name(name_){}
            
            template <typename T>
            inline operator T() const {
                auto res = parent[ parent.offset(name) ] ;
                return res ;
            }
            
            template <typename T>
            inline DataFrame& operator=( const T& rhs ){
                int index = 0 ;
                try{
                    index = parent.offset(name) ;
                    parent[ index ] = rhs ;
                } catch( ... ){
                    List v(parent) ;
                    v[name] = rhs ;
                    parent = DataFrame( (SEXP)v ) ;
                }
                return parent ;
            }
            
        private:
            DataFrame& parent; 
            const std::string& name ;
        };
        
        inline NameProxy operator[]( const std::string& name){
            return NameProxy( *this, name ) ;
        }
        
        inline const NameProxy operator[]( const std::string& name) const {
            return NameProxy( const_cast<DataFrame&>(*this), name ) ;
        }
        
    private:
        
        inline SEXP as_data_frame(SEXP df){
            Function asdf( "as.data.frame" ) ;
            return asdf(df, _["stringsAsFactors"] = false );
        }
        
        inline SEXP empty_data_frame(){
            Shield<SEXP> df = Rf_allocVector(VECSXP, 0) ;
            Rf_setAttrib( df, R_NamesSymbol, Rf_allocVector(STRSXP,0) ) ;
            Rf_setAttrib( df, R_RowNamesSymbol, Rf_allocVector(STRSXP,0) ) ;
            Rf_setAttrib( df, R_ClassSymbol, Rf_mkString( "data.frame" ) );
            return df ;
        }
        
    } ;
        
}

#endif
