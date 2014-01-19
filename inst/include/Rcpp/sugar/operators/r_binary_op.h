#ifndef Rcpp__sugar__r_binary_op_h
#define Rcpp__sugar__r_binary_op_h

namespace Rcpp{
namespace sugar{

#undef RCPP_OP
#define RCPP_OP(NAME,OP)   	                                     \
template <int RTYPE>                                                \
class NAME {                                                        \
public:                                                             \
	typedef typename traits::storage_type<RTYPE>::type STORAGE ;    \
	inline int operator()( STORAGE lhs, STORAGE rhs) const {       \
		return lhs OP rhs ;                                         \
	}                                                               \
} ;
RCPP_OP(less,<)
RCPP_OP(greater,>)
RCPP_OP(less_or_equal,<=)
RCPP_OP(greater_or_equal,>=)
RCPP_OP(equal,==)
RCPP_OP(not_equal,!=)
#undef RCPP_OP


} // sugar
} // Rcpp

#endif
