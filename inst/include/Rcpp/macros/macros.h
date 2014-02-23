#ifndef Rcpp_macros_macros_h
#define Rcpp_macros_macros_h

#define RCPP_DECORATE(__FUN__) __FUN__##__rcpp__wrapper__
#define RCPP_GET_NAMES(x)       Rf_getAttrib(x, R_NamesSymbol)
#define RCPP_GET_CLASS(x)       Rf_getAttrib(x, R_ClassSymbol)

#ifndef BEGIN_RCPP
#define BEGIN_RCPP try{ 
#endif 

#ifndef VOID_END_RCPP
#define VOID_END_RCPP } catch( std::exception& __ex__ ){ Rcpp::forward_exception_to_r( __ex__ ) ; } catch(...){ ::Rf_error( "c++ exception (unknown reason)" ) ; }
#endif

#ifndef END_RCPP
#define END_RCPP VOID_END_RCPP return R_NilValue;
#endif

#ifndef END_RCPP_RETURN_ERROR
#define END_RCPP_RETURN_ERROR } catch( std::exception& __ex__ ){ return Rcpp::exception_to_try_error( __ex__ ) ; } catch(...){ return Rcpp::string_to_try_error( "c++ exception (unknown reason)" ) ; } return R_NilValue;
#endif

#define Rcpp_error(MESSAGE) throw Rcpp::exception( MESSAGE, __FILE__, __LINE__ ) 

#include <Rcpp/macros/debug.h>
#include <Rcpp/macros/dispatch.h>
#include <Rcpp/macros/interface.h>
#include <Rcpp/macros/get_callable.h>

#endif
