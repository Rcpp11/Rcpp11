#ifndef Rcpp_platform_h
#define Rcpp_platform_h

#if defined(__clang__) 
    #define RCPP_HAS_UNDERLYING_TYPE 
#elif defined(__GNUC__)

    # if defined(__GNUC_PATCHLEVEL__)
    #  define __GNUC_VERSION__ (__GNUC__ * 10000 \
                                + __GNUC_MINOR__ * 100 \
                                + __GNUC_PATCHLEVEL__)
    # else
    #  define __GNUC_VERSION__ (__GNUC__ * 10000 \
                                + __GNUC_MINOR__ * 100)
    # endif

    #if __GNUC_VERSION__ > 406003
        #define RCPP_HAS_UNDERLYING_TYPE
    #endif

#endif

#endif
