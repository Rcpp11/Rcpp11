#ifndef Rcpp__DataFrame_h
#define Rcpp__DataFrame_h

namespace Rcpp{
     
    template < template <class> class StoragePolicy>
    class DataFrame_Impl : 
        public RObjectMethods<DataFrame_Impl<StoragePolicy>>, 
        public AttributeProxyPolicy<DataFrame_Impl<StoragePolicy>>
        {
    public:
        typedef Vector<VECSXP, StoragePolicy> List ; 
        
        DataFrame_Impl() : data(empty_data_frame()){}
        DataFrame_Impl(SEXP x) {
            set_sexp(x) ;        
        }
        DataFrame_Impl( const DataFrame_Impl& other) : data(other.data){}
                
        template <typename T> 
        DataFrame_Impl( const T& obj) {
            set_sexp(wrap(obj));
        }
                
        template <typename Proxy>                     
        DataFrame_Impl( const GenericProxy<Proxy>& proxy ) {
            set_sexp( proxy.get() ); 
        }
        
        DataFrame_Impl& 
        operator=( DataFrame_Impl& other) {
            data = other.data ;
            return *this ;    
        }
        DataFrame_Impl& operator=( SEXP x) {
            set_sexp(x) ;    
        }
               
        inline int size() const {
            return data.size() ;    
        }
        
        int nrows() const {
            SEXP att = ATTRIB( get() ); 
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
        static DataFrame_Impl create(const Args&... args){
            return from_list( List::create( args...) ) ;
        }
           
        inline typename List::Proxy operator[](int i){ return data[i] ; }
        inline typename List::const_Proxy operator[](int i) const { return data[i] ; }
        
        inline typename List::NameProxy operator[]( const std::string& name ){
            return data[name] ;
        }
        inline typename List::const_NameProxy operator[]( const std::string& name ) const {
            return data[name] ;
        }
             
        inline operator SEXP() const {
            return get() ;
        }
        
    private:
        List data ;
        
        void set_sexp(SEXP x) {
            if( ::Rf_inherits( x, "data.frame" )){
                data = x ;
            } else{
                data = internal::convert_using_rfunction( x, "as.data.frame" ) ;
                
            }    
        }
        
        inline SEXP get() const {
            return data ;    
        }
        
        static DataFrame_Impl from_list( Rcpp::List obj ) {
            std::vector<SEXP> columns ;
            std::vector<std::string> out_names ;
            
            bool use_default_strings_as_factors = true ;
            bool strings_as_factors = true ;
            int n = obj.size() ;
            CharacterVector names = obj.attr( "names" ) ;
            if( !names.isNULL() ){
                for( int i=0; i<n; i++){
                    if( names[i] == "stringsAsFactors" ){
                        use_default_strings_as_factors = false ;        
                        if( !as<bool>(obj[i]) ) strings_as_factors = false ;
                        break ;         
                    } else {
                        columns.push_back( obj[i] ) ;
                        out_names.push_back( std::string(names[i]) ) ;
                    }
                }
            }
            if( use_default_strings_as_factors ) 
                return DataFrame(obj) ;
            
            obj = wrap(columns) ;
            obj.names() = wrap(out_names) ;
            
            SEXP as_df_symb = Rf_install("as.data.frame");
            SEXP strings_as_factors_symb = Rf_install("stringsAsFactors");
            
            Shield<SEXP> call  = Rf_lang3(as_df_symb, obj, wrap( strings_as_factors ) ) ;
            SET_TAG( CDDR(call),  strings_as_factors_symb ) ;   
            Shield<SEXP> res = Rcpp_eval( call ) ; 
            DataFrame out( res ) ;
            return out ;
        
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
