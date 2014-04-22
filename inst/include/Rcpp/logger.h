#ifndef Rcpp__logger__h
#define Rcpp__logger__h

namespace Rcpp {

#ifdef RCPP_DEBUG_MODE

#define NARGS(...) VA_NUM_ARGS_IMPL(__VA_ARGS__, 10,9,8,7,6,5,4,3,2,1)
#define VA_NUM_ARGS_IMPL(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,N,...) N

#ifndef log_message
#define log_message(fmt, ...) do { \
    static char buff[1024 * 8 + 1]; \
    snprintf(buff, 1024 * 8, fmt, __VA_ARGS__); \
    Rprintf("(%s:%d):  %s\n\n", short_file_name(__FILE__), __LINE__, buff); \
} while (0)
#else
#warning "log_message already defined!"
#endif

#ifndef log_value
#define log_value(x, ...) do { \
    if (NARGS(__VA_ARGS__)) { \
        std::string msg = tfm::format(__VA_ARGS__); \
        Rprintf("(%s:%d):  Object '%s' value (%s):\n", short_file_name(__FILE__), __LINE__, #x, msg.c_str()); \
    } else { \
        Rprintf("(%s:%d):  Object '%s' value:\n", short_file_name(__FILE__), __LINE__, #x); \
    } \
    Rf_PrintValue(x); \
    Rprintf("\n"); \
} while (0)
#else
#warning "log_value already defined!"
#endif

#ifndef log_str
#define log_str(x, ...) do { \
    if (NARGS(__VA_ARGS__)) { \
        std::string msg = tfm::format(__VA_ARGS__);  \
        Rprintf("(%s:%d):  Object '%s' structure (%s):\n", short_file_name(__FILE__), __LINE__, #x, msg.c_str()); \
    } else { \
        Rprintf("(%s:%d):  Object '%s' structure:\n", short_file_name(__FILE__), __LINE__, #x); \
    } \
    Shield<SEXP> call(Rf_lang2( Rf_install("str"), x )); \
    Rf_eval(call, R_GlobalEnv); \
    Rprintf("\n"); \
} while (0)
#else
#warning "log_str already defined!"
#endif

#ifndef log_internals
#define log_internals(x, ...) do { \
    if (NARGS(__VA_ARGS__)) { \
        std::string msg = tfm::format(__VA_ARGS__); \
        Rprintf("(%s:%d):  Object '%s' internals (%s):\n", short_file_name(__FILE__), __LINE__, #x, msg.c_str()); \
    } else { \
        Rprintf("(%s:%d):  Object '%s' internals:\n", short_file_name(__FILE__), __LINE__, #x); \
    } \
    Shield<SEXP> innercall(Rf_lang2( Rf_install("inspect"), x )); \
    Shield<SEXP> call(Rf_lang2( Rf_install(".Internal"), innercall )); \
    Rf_eval(call, R_GlobalEnv); \
    Rprintf("\n"); \
} while (0)
#else
#warning "log_inspect already defined!"
#endif

#else // RCPP_DEBUG_MODE off

#ifndef log_message
#define log_message
#endif

#ifndef log_value
#define log_value
#endif

#ifndef log_str
#define log_str
#endif

#ifndef log_internals
#define log_internals
#endif

#endif

} // namespace Rcpp

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

#endif
