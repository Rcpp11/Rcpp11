#ifndef Rcpp__traits__comparator_type__h
#define Rcpp__traits__comparator_type__h

namespace Rcpp{
namespace traits{
   
class StringCompare {
public:
    inline bool operator()( SEXP x, SEXP y) const {
        return strcmp( char_nocheck(x), char_nocheck(y) ) < 0 ; 
    }
} ;
	
template <int RTYPE> struct comparator_type {
	typedef std::less< typename storage_type<RTYPE>::type > type ;	
} ;
template <> struct comparator_type<STRSXP>{
	typedef StringCompare type ;
} ;
   

}
}     

#endif

