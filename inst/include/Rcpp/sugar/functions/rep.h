#ifndef Rcpp__sugar__rep_h
#define Rcpp__sugar__rep_h

namespace Rcpp{
    namespace sugar{
    
        template <int RTYPE, bool NA, typename T>
        class Rep : public SugarVectorExpression< RTYPE ,NA, Rep<RTYPE,NA,T> > {
        public:
            typedef typename Rcpp::VectorBase<RTYPE,NA,T> VEC_TYPE ;
            typedef typename Rcpp::traits::storage_type<RTYPE>::type STORAGE ;
            
            Rep( const VEC_TYPE& object_, int times_ ) : 
                object(object_.get_ref()), times(times_), n(object_.size()){}
            
            inline STORAGE operator[]( int i ) const {
                return object[ i % n ] ;
            }
            inline int size() const { return times * n ; }
        
            const T& object ;
            int times, n ;
            
        } ;
        
        template <typename Target, int RTYPE, bool NA, typename T>
        struct sugar_vector_expression_op<Target, Rep<RTYPE,NA,T>> {
            inline void apply(Target& target, const Rep<RTYPE,NA,T>& obj ) {
                int n= obj.n, times = obj.times ;
                auto source = obj.object ;
                auto it = target.begin() ;
                for( int i=0; i<times; i++){
                    for( int j=0; j<n; j++, ++it){
                        *it = source[j] ;
                    }
                }
            }
        } ;
        
        template <typename Target, int RTYPE, bool NA, template <class> class StoragePolicy >
        struct sugar_vector_expression_op<Target, Rep<RTYPE,NA,Vector<RTYPE,StoragePolicy> >> {
            inline void apply(Target& target, const Rep<RTYPE,NA,Vector<RTYPE,StoragePolicy> >& obj ) {
                int n= obj.n, times = obj.times ;
                auto it = target.begin() ;
                auto source = obj.object ;
                for( int i=0; i<times; i++){
                    std::copy( source.begin(), source.end(), it ) ;
                    it += n ;
                }
            }
        } ;
        
        
        template <typename T>
        class Rep_Single : public SugarVectorExpression< 
            Rcpp::traits::r_sexptype_traits<T>::rtype, 
            true, 
            Rep_Single<T>
        > {
        public:
            Rep_Single( T x_, int n_) : x(x_), n(n_){}
            
            inline T operator[]( int i ) const {
                return x;
            }
            inline int size() const { return n ; }
        
            T x ;
            int n ;
        } ;
        
        template <typename Target, typename T>
        struct sugar_vector_expression_op<Target, Rep_Single<T>> {
            inline void apply(Target& target, const Rep_Single<T>& obj ){
                std::fill( target.begin(), target.end(), obj.x ) ;    
            }
        } ;
        
    
    } // sugar

    template <int RTYPE, bool NA, typename T>
    inline sugar::Rep<RTYPE,NA,T> rep( const VectorBase<RTYPE,NA,T>& t, int n ){
        return sugar::Rep<RTYPE,NA,T>( t, n ) ;
    }
    
    inline sugar::Rep_Single<double> rep( double x, int n ){
        return sugar::Rep_Single<double>( x, n ) ;
    }
    inline sugar::Rep_Single<int> rep( int x, int n ){
        return sugar::Rep_Single<int>( x, n ) ;
    }
    inline sugar::Rep_Single<Rbyte> rep( Rbyte x, int n ){
        return sugar::Rep_Single<Rbyte>( x, n ) ;
    }
    inline sugar::Rep_Single<Rcomplex> rep( Rcomplex x, int n ){
        return sugar::Rep_Single<Rcomplex>( x, n ) ;
    }
    inline sugar::Rep_Single<bool> rep( bool x, int n ){
        return sugar::Rep_Single<bool>( x, n ) ;
    }

} // Rcpp
#endif

