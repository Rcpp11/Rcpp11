#ifndef Rcpp__sugar__functions__functional_h
#define Rcpp__sugar__functions__functional_h

namespace Rcpp {

// functions prefixed with 'i' perform transformations in-place

template <typename T, typename Callable>
auto map(T& x, Callable f) ->
  Vector<
    traits::r_sexptype_traits<
      decltype( f(x[0]) )
    >::rtype
  > {

  typedef decltype( f(x[0]) ) RETURN_TYPE;
  static const int RTYPE = traits::r_sexptype_traits<RETURN_TYPE>::rtype;

  Vector<RTYPE> output( x.size() );
  std::transform(x.begin(), x.end(), output.begin(), f);
  return output;
}

template <typename T, typename Callable>
void imap(T& x, Callable f) {
  std::transform(x.begin(), x.end(), x.begin(), f);
}

template <int RTYPE, typename Callable>
Vector<RTYPE> filter(Vector<RTYPE> const& x, Callable f) {
  std::vector<typename traits::storage_type<RTYPE>::type> output;
  output.reserve(x.size());
  for (int i=0; i < x.size(); ++i) {
    output.emplace_back(x[i]);
  }
  output.erase(
    std::remove_if(output.begin(), output.end(), f),
    output.end()
  );
  return wrap(output);
}

} // end namespace Rcpp


#endif /* Rcpp__sugar__functions__functional_h */
