#ifndef Rcpp__vector__swap_h
#define Rcpp__vector__swap_h

namespace std {

#undef RCPP_GENERATE_SWAP
#define RCPP_GENERATE_SWAP(TYPE,RTYPE)                             \
    template<> inline void swap< Rcpp::internal::TYPE<RTYPE> >(    \
        Rcpp::internal::TYPE<RTYPE>& a ,                            \
        Rcpp::internal::TYPE<RTYPE>& b) {                             \
            a.swap(b) ;                                                \
        }

RCPP_GENERATE_SWAP(generic_proxy,VECSXP)
RCPP_GENERATE_SWAP(generic_proxy,EXPRSXP)
RCPP_GENERATE_SWAP(string_proxy,STRSXP)
#undef RCPP_GENERATE_SWAP

}

#endif
