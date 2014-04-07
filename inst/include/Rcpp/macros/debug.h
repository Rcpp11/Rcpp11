#ifndef Rcpp_macros_debug_h
#define Rcpp_macros_debug_h

#include <iostream>
#include <fstream>

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

// A user-level logging class
// Usage:
// 1. debug(fmt, ...) writes debug output to screen
// 2. RcppLogger(file); flog(fmt, ...) writes log output to file
namespace Rcpp {

template <typename... Args>
inline void stop(const char* fmt, Args... args);

struct __RCPP_LOGGER_CLASS__ {
  
  FILE* __RCPP_LOG_FILE__;

  __RCPP_LOGGER_CLASS__() = delete;
  __RCPP_LOGGER_CLASS__(const char* file, const char* mode = "w") {
    __RCPP_LOG_FILE__ = fopen(file, mode);
    if (__RCPP_LOG_FILE__ == 0) {
      stop("Could not open file '%s' for logging", file);
    }
  }
  
  ~__RCPP_LOGGER_CLASS__() {
    if (__RCPP_LOG_FILE__ != 0) {
      fclose(__RCPP_LOG_FILE__);
    }
  }
  
};

#define RcppLogger(file) \
  __RCPP_LOGGER_CLASS__ __RCPP_LOGGER_INSTANCE__(file);

#define flog(fmt, ...) { \
  std::string msg = tfm::format(fmt, __VA_ARGS__); \
  fprintf(__RCPP_LOGGER_INSTANCE__.__RCPP_LOG_FILE__, "(%s:%d):  %s\n", short_file_name(__FILE__), __LINE__, msg.c_str()); \
}

#define debug(fmt, ...) { \
  std::string msg = tfm::format(fmt, __VA_ARGS__); \
  Rprintf("(%s:%d):  %s\n", short_file_name(__FILE__), __LINE__, msg.c_str()); \
}

}

#endif
