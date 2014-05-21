#ifndef Rcpp__vector_concat_h
#define Rcpp__vector_concat_h

namespace Rcpp{
    
    template <typename T>
    inline int get_size_one( const T&, std::true_type, std::true_type ){
        return 1 ;
    }

    template <typename T>
    inline int get_size_one( const T&, std::true_type, std::false_type ){
        return 1 ;
    }

    template <typename T>
    inline int get_size_one( const T& obj, std::false_type, std::true_type ){
        return Rf_length(obj);
    }

    template <typename T>
    inline int get_size_one( const T& obj, std::false_type, std::false_type ){
        return obj.size();
    }

    template <typename First>
    int get_size( const First& first){
        return get_size_one<First>(first, typename traits::is_primitive<First>::type(), typename std::is_same<First, SEXP>::type() ) ;
    }

    template <typename First, typename... Rest>
    int get_size( const First& first, Rest... rest ){
        return get_size_one<First>(first, typename traits::is_primitive<First>::type(), typename std::is_same<First, SEXP>::type() ) + get_size(rest...) ;
    }

    template <int RTYPE, typename... Args>
    Vector<RTYPE> concatenate(Args... args) {
        static_assert( traits::all_compatible<RTYPE,Args...>::type::value, "incompatible parameters" ) ;

        int n = get_size(args...) ;
        Vector<RTYPE> out(n) ;
        int i = 0 ;
        if (sizeof...(args)) {
            do_concatenate(out, i, args...);
        }

        return out ;
    }
    
    template <typename T, typename Current, typename... Rest>
    void do_concatenate_one( T& x, int& idx, const Current& curr, std::false_type, std::false_type ){
        int n = curr.size();
        for (int i=0; i < n; ++i, idx++) {
            x[idx] = curr[i];
        }
    }

    template <typename T, typename Current, typename... Rest>
    void do_concatenate_one( T& x, int& idx, const Current& curr, std::false_type, std::true_type ){
        int n = Rf_length(curr);
        T Tcurr = as<T>(curr);
        for (int i=0; i < n; ++i, idx++) {
            x[idx] = Tcurr[i];
        }
    }

    template <typename T, typename Current, typename... Rest>
    void do_concatenate_one( T& x, int& idx, const Current& curr, std::true_type, std::false_type ){
        x[idx++]=curr ;
    }

    template <typename T, typename Current, typename... Rest>
    void do_concatenate_one( T& x, int& idx, const Current& curr, std::true_type, std::true_type ){
        x[idx++]=curr ;
    }

    template <typename T, typename Current, typename... Rest>
    void do_concatenate(T& x, int& idx, const Current& curr, Rest... rest) {
        do_concatenate_one(x, idx, curr, typename traits::is_primitive<Current>::type(), typename std::is_same<Current, SEXP>::type() );
        do_concatenate(x, idx, rest...);
    }

    template <typename T, typename Current>
    void do_concatenate(T& x, int& idx, const Current& curr){
        do_concatenate_one(x, idx, curr, typename traits::is_primitive<Current>::type(), typename std::is_same<Current, SEXP>::type() );
    }

}

#endif
