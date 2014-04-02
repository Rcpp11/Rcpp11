#ifndef Rcpp__DataFrame_h
#define Rcpp__DataFrame_h

namespace Rcpp{
     
    template < template <class> class StoragePolicy>
    class DataFrame_Impl {
    public:    
        DataFrame_Impl() : data(empty_data_frame()){}
        DataFrame_Impl(SEXP x) {
            set_sexp(x) ;        
        }
        DataFrame_Impl( const DataFrame_Impl& other) : data(other.data){}
                
        template <typename T> 
        DataFrame_Impl( const T& obj) : DataFrame_Impl(wrap(obj)){}
                
        DataFrame_Impl& 
        operator=( DataFrame_Impl& other) {
            data = other.data ;
            return *this ;    
        }
        DataFrame_Impl& operator=( SEXP x) {
            set_sexp(x) ;    
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

    private:
        
        void set_sexp(SEXP x) {
            if( ::Rf_inherits( x, "data.frame" )){
                data = x ;
            } else{
                data = internal::convert_using_rfunction( x, "as.data.frame" ) ;
                
            }    
        }
        
        inline SEXP get(){
            return data ;    
        }
        
        static DataFrame_Impl from_list( Rcpp::List ) {
            bool use_default_strings_as_factors = true ;
            bool strings_as_factors = true ;
            int strings_as_factors_index = -1 ;
            int n = obj.size() ;
            CharacterVector names = obj.attr( "names" ) ;
            if( !names.isNULL() ){
                for( int i=0; i<n; i++){
                    if( names[i] == "stringsAsFactors" ){
                        strings_as_factors_index = i ;
                        use_default_strings_as_factors = false ;        
                        if( !as<bool>(obj[i]) ) strings_as_factors = false ;
                        break ;         
                    }
                }
            }
            if( use_default_strings_as_factors ) 
                return DataFrame(obj) ;
            SEXP as_df_symb = Rf_install("as.data.frame");
            SEXP strings_as_factors_symb = Rf_install("stringsAsFactors");
            
            obj.erase(strings_as_factors_index) ;
            names.erase(strings_as_factors_index) ;
            obj.attr( "names") = names ;
            Shield<SEXP> call  = Rf_lang3(as_df_symb, obj, wrap( strings_as_factors ) ) ;
            SET_TAG( CDDR(call),  strings_as_factors_symb ) ;   
            Shield<SEXP> res = Rcpp_eval( call ) ; 
            DataFrame out( res ) ;
            return out ;
        
        }
        
        Vector<VECSXP, StoragePolicy> data ;
        
        inline SEXP empty_data_frame(){
            Shield<SEXP> df = Rf_allocVector(VECXSP, 0) ;
            Rf_setAttrib( df, R_NamesSymbol, Rf_allocVector(STRSXP,0) ) ;
            Rf_setAttrib( df, R_RowNamesSymbol, Rf_allocVector(STRSXP,0) ) ;
            Rf_setAttrib( df, R_ClassSymbol, Rf_mkString( "data.frame" ) );
            return df ;
        }
        
    } ;
        
}

#endif
