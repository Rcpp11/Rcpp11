#ifndef RCPP_LOGGER_H
#define RCPP_LOGGER_H

#ifdef RCPP_DEBUG_MODE

  #ifndef RCPP_LOG_FILE

    // these macros go to the console
    #define debug(...) { \
      std::string msg = tfm::format(__VA_ARGS__); \
      Rprintf("(%20s:%4d):  %s\n", short_file_name(__FILE__), __LINE__, msg.c_str()); \
    }
    
    #define debug0(...) { \
      std::string msg = tfm::format(__VA_ARGS__); \
      Rprintf("%s\n", msg.c_str()); \
    }
    
    #define log_value(x) { \
      Rprintf("(%20s:%4d):  Object '%s' value:\n", short_file_name(__FILE__), __LINE__, #x); \
      Rf_PrintValue(x); \
    }
    
    #define log_str(x) { \
      Rprintf("(%20s:%4d):  Object '%s' structure:\n", short_file_name(__FILE__), __LINE__, #x); \
      Shield<SEXP> call = Rf_lang2( Rf_install("str"), x ); \
      Rf_eval(call, R_GlobalEnv); \
    }
    
  #else // RCPP_LOG_FILE defined
  
    #ifndef RCPP_LOG_MODE
      #define RCPP_LOG_MODE "a"
    #endif
    
    Rcpp::Function RCPP_CAPTURE("capture.output");
    
    // macros write to file
    #define debug(...) { \
      FILE* __RCPP_LOG_FILE__ = fopen(RCPP_LOG_FILE, RCPP_LOG_MODE); \
      if (__RCPP_LOG_FILE__ == nullptr) { \
        stop("could not open file '%s' for logging", RCPP_LOG_FILE); \
      } \
      std::string msg = tfm::format(__VA_ARGS__); \
      fprintf(__RCPP_LOG_FILE__, "(%20s:%4d):  %s\n", short_file_name(__FILE__), __LINE__, msg.c_str()); \
      fclose(__RCPP_LOG_FILE__); \
    }
    
    #define debug0(...) { \
      FILE* __RCPP_LOG_FILE__ = fopen(RCPP_LOG_FILE, RCPP_LOG_MODE); \
      if (__RCPP_LOG_FILE__ == nullptr) { \
        stop("could not open file '%s' for logging", RCPP_LOG_FILE); \
      } \
      std::string msg = tfm::format(__VA_ARGS__); \
      fprintf(__RCPP_LOG_FILE__, "%s\n", msg.c_str()); \
      fclose(__RCPP_LOG_FILE__); \
    }
    
    #define log_value(x) { \
      RCPP_CAPTURE(  \
        Rf_lang2( Rf_install("print"), x ), \
        _["file"] = RCPP_LOG_FILE, \
        _["append"] = TRUE \
      ); \
    }
    
    #define log_str(x) { \
      RCPP_CAPTURE( \
        Rf_lang2( Rf_install("str"), x ), \
        _["file"] = RCPP_LOG_FILE, \
        _["append"] = TRUE \
      ); \
    }
    
  #endif

#else
  
  #ifndef debug
    #define debug(...)
  #endif
  
  #ifndef debug0
    #define debug0(...)
  #endif
  
  #ifndef log_value
    #define log_value(...)
  #endif
  
  #ifndef log_str
    #define log_str(...)
  #endif

#endif

#endif
