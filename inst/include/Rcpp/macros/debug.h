#ifndef Rcpp_macros_debug_h
#define Rcpp_macros_debug_h

// simple logging help
#ifndef RCPP_DEBUG_LEVEL
    #define RCPP_DEBUG_LEVEL 0
#endif

#define PRETTY_BOOL(x) ( x ? "true" : "false" )
#if RCPP_DEBUG_LEVEL > 0
    #define RCPP_DEBUG( fmt, ... ) Rprintf( "%20s:%4d             " fmt "\n" , short_file_name(__FILE__), __LINE__, ##__VA_ARGS__ ) ; 
    #define RCPP_DEBUG_OBJECT(OBJ) Rf_PrintValue( Rf_eval( Rf_lang2( Rf_install( "str"), OBJ ), R_GlobalEnv ) ) ;
    #define RCPP_INSPECT_OBJECT(OBJ) Rf_PrintValue( Rf_eval( Rf_lang2( Rf_install( ".Internal"), Rf_lang2( Rf_install( "inspect" ), OBJ ) ), R_GlobalEnv ) ) ;
    #define RCPP_DEBUG_CLASS( CLASS, fmt, ... ) Rprintf( "%20s:%4d   [%s]" fmt "\n" , short_file_name(__FILE__), __LINE__, DEMANGLE(CLASS), ##__VA_ARGS__ ) ;
    #define RCPP_DEBUG_CTOR( CLASS, fmt, ... ) Rprintf( "%20s:%4d   [%s]::ctor" fmt "\n" , short_file_name(__FILE__), __LINE__, DEMANGLE(CLASS), ##__VA_ARGS__ ) ;
    #define RCPP_DEBUG_MOVE_CTOR( CLASS, fmt, ... ) Rprintf( "%20s:%4d   [%s]::move_ctor" fmt "\n" , short_file_name(__FILE__), __LINE__, DEMANGLE(CLASS), ##__VA_ARGS__ ) ;
    #define RCPP_DEBUG_DTOR( CLASS, fmt, ... ) Rprintf( "%20s:%4d   [%s]::dtor" fmt "\n" , short_file_name(__FILE__), __LINE__, DEMANGLE(CLASS), ##__VA_ARGS__ ) ;
#else
    #define RCPP_DEBUG( MSG, ... )
    #define RCPP_DEBUG_OBJECT(OBJ)
    #define RCPP_INSPECT_OBJECT(OBJ)
    #define RCPP_DEBUG_CLASS( CLASS, fmt, ... )
    #define RCPP_DEBUG_CTOR( CLASS, fmt, ... )
    #define RCPP_DEBUG_MOVE_CTOR( CLASS, fmt, ... )
    #define RCPP_DEBUG_DTOR( CLASS, fmt, ... )
#endif

#endif
