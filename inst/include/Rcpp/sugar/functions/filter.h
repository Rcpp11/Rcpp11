#ifndef Rcpp__sugar__functions__filter_h
#define Rcpp__sugar__functions__filter_h

namespace Rcpp {

    template <int RTYPE, typename Callable>
    Vector<RTYPE> filter(Vector<RTYPE> const& x, Callable f) {
      std::vector<typename traits::storage_type<RTYPE>::type> tmp ;
      auto it = sugar_begin(x) ;
      auto end= sugar_end(x) ;
      while( it != end ){
        auto v = *it ;
        if( f(v) ) tmp.push_back(v) ;   
      }
      return wrap(tmp);
    }

} // end namespace Rcpp


#endif 
