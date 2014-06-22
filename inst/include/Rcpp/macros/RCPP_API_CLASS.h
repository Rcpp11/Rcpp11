#ifndef Rcpp_RCPP_API_CLASS_h
#define Rcpp_RCPP_API_CLASS_h

#define RCPP_API_CLASS(__CLASS__)                          \
template < typename Storage > class __CLASS__ :            \
    public SlotProxyPolicy<__CLASS__<Storage>>,            \
    public AttributeProxyPolicy<__CLASS__<Storage>>,       \
    public AttributesProxyPolicy<__CLASS__<Storage>>       \
    
#endif
