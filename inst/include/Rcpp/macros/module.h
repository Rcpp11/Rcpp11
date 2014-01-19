#ifndef RCPP_MODULE_MACROS_H
#define RCPP_MODULE_MACROS_H

/** This macros should be used by packages using modules when a type is used
 *  as a parameter of a function or method exposed by modules. This defines
 *  the necessary trait that makes the class as<>'able
 */
#define RCPP_EXPOSED_AS(CLASS)                                                \
    namespace Rcpp{ namespace traits{                                         \
    template<> struct r_type_traits< CLASS* >{                                \
        typedef r_type_module_object_pointer_tag r_category ;                 \
    } ;                                                                       \
    template<> struct r_type_traits< const CLASS* >{                          \
        typedef r_type_module_object_const_pointer_tag r_category ;           \
    } ;                                                                       \
    template<> struct r_type_traits< CLASS >{                                 \
        typedef r_type_module_object_tag r_category ;                         \
    } ;                                                                       \
    template<> struct r_type_traits< CLASS& >{                                \
        typedef r_type_module_object_reference_tag r_category ;               \
    } ;                                                                       \
    template<> struct r_type_traits< const CLASS& >{                          \
        typedef r_type_module_object_const_reference_tag r_category ;         \
    } ;                                                                       \
    template<> struct input_parameter< CLASS* >{                              \
        typedef Rcpp::InputParameter<CLASS*> type ;                           \
    } ;                                                                       \
    template<> struct input_parameter< const CLASS* >{                        \
        typedef Rcpp::InputParameter<const CLASS*> type ;                     \
    } ;                                                                       \
    template<> struct input_parameter< CLASS >{                               \
        typedef Rcpp::InputParameter<CLASS> type ;                            \
    } ;                                                                       \
    template<> struct input_parameter< CLASS& >{                              \
        typedef Rcpp::InputParameter<CLASS&> type ;                           \
    } ;                                                                       \
    template<> struct input_parameter< const CLASS& >{                        \
        typedef Rcpp::InputParameter<const CLASS&> type ;                     \
    } ;                                                                       \
    }}
    
#define RCPP_EXPOSED_WRAP(CLASS) namespace Rcpp{ namespace traits{ template<> struct wrap_type_traits< CLASS >{typedef wrap_type_module_object_tag wrap_category ; } ; }}

#define RCPP_EXPOSED_CLASS_NODECL(CLASS) \
  RCPP_EXPOSED_AS(CLASS)          \
  RCPP_EXPOSED_WRAP(CLASS)

#define RCPP_EXPOSED_CLASS(CLASS) \
  class CLASS;                    \
  RCPP_EXPOSED_CLASS_NODECL(CLASS)
 
#endif
