#ifndef RCPP_LONG_LONG_H
#define RCPP_LONG_LONG_H

namespace Rcpp{
    namespace traits{

        template<> struct r_sexptype_traits<long long>{ enum{ rtype = REALSXP } ; } ;
        template<> struct r_sexptype_traits<unsigned long long>{ enum{ rtype = REALSXP } ; } ;
    
        template<> struct r_type_traits<long long>{ typedef r_type_primitive_tag r_category ; } ;
        template<> struct r_type_traits< std::pair<const std::string,long long> >{ typedef r_type_primitive_tag r_category ; } ;
        template<> struct r_type_traits<unsigned long long>{ typedef r_type_primitive_tag r_category ; } ;
        template<> struct r_type_traits< std::pair<const std::string,unsigned long long> >{ typedef r_type_primitive_tag r_category ; } ;
    
        template <> struct wrap_type_traits<long long> { typedef wrap_type_primitive_tag wrap_category; } ;
        template <> struct wrap_type_traits<unsigned long long> { typedef wrap_type_primitive_tag wrap_category; } ;
    }
}

#endif
