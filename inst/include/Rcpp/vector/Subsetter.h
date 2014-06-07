#ifndef Rcpp_vector_Subsetter_h_
#define Rcpp_vector_Subsetter_h_

namespace Rcpp {

    namespace traits {
        template <typename T>
        struct identity { typedef T type; };
    }

// Subset proxy that can handle y[x], y[x] = b
// y[x] == SubsetProxy(y, x), so y == LHS, x == RHS
template <
    int RTYPE, typename Storage, // y
    typename eT, typename Expr // x
>
class SubsetProxy {

    typedef Vector<RTYPE, Storage> LHS_t;
    typedef SugarVectorExpression<eT, Expr> RHS_t;

public:

    SubsetProxy(LHS_t& lhs_, const RHS_t& rhs_):
        lhs(lhs_), rhs(rhs_), lhs_n(lhs.size()), rhs_n(rhs.size())
    {
        materialize_indices(typename traits::is_materialized<Expr>::type());
    }

    SubsetProxy(const SubsetProxy& other):
        lhs(other.lhs),
        rhs(other.rhs),
        lhs_n(other.lhs_n),
        rhs_n(other.rhs_n),
        indices(other.indices),
        indices_n(other.indices_n) {}

    // Enable e.g. x[y] = z
    template <typename RHS_eT, typename RHS_Expr>
    SubsetProxy operator=(const SugarVectorExpression<RHS_eT, RHS_Expr>& other) {
        int n = other.size();
        auto it = sugar_begin(other);
        for (R_xlen_t i = 0; i < indices_n; ++i, ++it) {
            lhs[indices[i]] = *it;
        }
        return *this;
    }

    template <typename T>
    SubsetProxy& operator=(typename std::enable_if<traits::is_primitive<T>::value, T>::type other) {
        for (int i=0; i < indices_n; ++i) {
            lhs[ indices[i] ] = other;
        }
        return *this;
    }

    operator Vector<RTYPE, Storage>() const {
        return get_vec();
    }

    operator SEXP() const {
        return wrap( get_vec() );
    }

private:

    #ifndef RCPP_NO_BOUNDS_CHECK
    void check_indices(int* x, int n, int size) {
        for (int i=0; i < n; ++i) {
            if (x[i] < 0 or x[i] >= size) {
                stop("index error");
            }
        }
    }
    #else
    void check_indices(int* x, int n, int size) {}
    #endif

    // for materialized types, ie, vectors
    void materialize_indices(std::true_type) {
        return get_indices(traits::number_to_type<Expr::r_type>());
    }

    // sugar expressions
    void materialize_indices(std::false_type) {
        indices.reserve(rhs_n);
        auto it = sugar_begin(rhs);
        for (int i = 0; i < rhs_n; ++i, ++it) {
            indices.emplace_back(*it);
        }
    }

    void get_indices(traits::number_to_type<INTSXP> t) {
        indices = INTEGER(rhs);
        indices_n = rhs_n;
        check_indices(indices, rhs_n, lhs_n);
    }

    void get_indices(traits::number_to_type<REALSXP> t ) {
        indices.reserve(rhs_n);
        Vector<INTSXP, Storage> tmp =
            as< Vector<INTSXP, Storage> >(rhs);
        int* ptr = INTEGER(tmp);
        check_indices(ptr, rhs_n, lhs_n);
        for (int i=0; i < rhs_n; ++i) {
            indices.push_back( tmp[i] );
        }
        indices_n = rhs_n;
    }

    void get_indices(traits::number_to_type<STRSXP> t) {
        indices.reserve(rhs_n);
        SEXP names = Rf_getAttrib(lhs, R_NamesSymbol);
        if (Rf_isNull(names)) stop("names is null");
        for (int i=0; i < rhs_n; ++i) {
            indices.push_back( find(names, CHAR( STRING_ELT(rhs, i) )) );
        }
        indices_n = indices.size();
    }

    int find(const RHS_t& names, const char* str) {
        for (int i=0; i < lhs_n; ++i) {
            if (strcmp( CHAR( STRING_ELT( names, i) ), str) == 0) return i;
        }
        stop("no name found");
        return -1;
    }

    void get_indices(traits::number_to_type<LGLSXP> t) {
        indices.reserve(rhs_n);
        if (lhs_n != rhs_n) {
            stop("logical subsetting requires vectors of identical size");
        }
        int* ptr = LOGICAL(rhs);
        for (int i=0; i < rhs_n; ++i) {
            if (ptr[i] == NA_INTEGER) {
                stop("can't subset using a logical vector with NAs");
            }
            if (ptr[i]) {
                indices.push_back(i);
            }
        }
        indices_n = indices.size();
    }

    Vector<RTYPE, Storage> get_vec() const {
        Vector<RTYPE, Storage> output(indices_n);
        for (int i=0; i < indices_n; ++i) {
            output[i] = lhs[ indices[i] ];
        }
        SEXP names = Rf_getAttrib(lhs, R_NamesSymbol);
        if (!Rf_isNull(names)) {
            Shield<SEXP> out_names( Rf_allocVector(STRSXP, indices_n) );
            for (int i=0; i < indices_n; ++i) {
                SET_STRING_ELT(out_names, i, STRING_ELT(names, indices[i]));
            }
            Rf_setAttrib(output, R_NamesSymbol, out_names);
        }
        Rf_copyMostAttrib(lhs, output);
        return output;
    }

    LHS_t& lhs;
    const RHS_t& rhs;
    int lhs_n;
    int rhs_n;

    // we want to reuse the indices if an IntegerVector is passed in; otherwise,
    // we construct a std::vector<int> to hold the indices
    typename std::conditional<
        traits::r_sexptype_traits<eT>::rtype == INTSXP,
        typename std::conditional<
            traits::is_materialized<Expr>::type::value,
            int*,
            std::vector<int>
        >::type,
        std::vector<int>
    >::type indices;

    // because of the above, we keep track of the size
    int indices_n;

};

}

#endif
