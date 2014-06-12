#ifndef RCPP11_TRAITS_index_sequence_that_h
#define RCPP11_TRAITS_index_sequence_that_h

namespace Rcpp{
    namespace traits{
    
        template <typename Tuple, template <class> class Op, int INDEX, int... S>
        struct test_sequence ;
        
        template <typename Tuple, template <class> class Op, int INDEX, bool, int... S>
        struct test_sequence_impl ;
        
        template <typename Tuple, template <class> class Op, int INDEX, int... S>
        struct test_sequence_impl<Tuple, Op, INDEX, true, S...> {
            typedef typename test_sequence<Tuple, Op, INDEX-1, INDEX, S...>::type type ; 
        } ;
        
        template <typename Tuple, template <class> class Op, int INDEX, int... S>
        struct test_sequence_impl<Tuple, Op, INDEX, false, S...> {
            typedef typename test_sequence<Tuple, Op, INDEX-1, S...>::type type ; 
        } ;
        
        template <typename Tuple, template <class> class Op, int INDEX, int... S>
        struct test_sequence {
            typedef typename test_sequence_impl<Tuple, Op, INDEX, Op< typename std::tuple_element<INDEX,Tuple>::type >::value, S... >::type type ;   
        } ;
        
        template <typename Tuple, template <class> class Op, int... S>
        struct test_sequence<Tuple, Op, -1, S...> {
            typedef sequence<S...> type ;
        } ;
        
        template <template <class> class Op, typename... Args>
        struct index_sequence_that {
            typedef std::tuple<Args...> Tuple ;
            typedef typename test_sequence<Tuple, Op, std::tuple_size<Tuple>::value - 1>::type type ;     
        } ;
    
    }
}
#endif
