#ifndef Rcpp__sugar__rep_h
#define Rcpp__sugar__rep_h

namespace Rcpp{
    namespace sugar{
    
        template <int RTYPE, bool NA, typename T>
        class Rep : 
            public SugarVectorExpression< RTYPE ,NA, Rep<RTYPE,NA,T> >, 
            public custom_sugar_vector_expression
        {
        public:
            typedef typename Rcpp::VectorBase<RTYPE,NA,T> VEC_TYPE ;
            typedef typename Rcpp::traits::storage_type<RTYPE>::type STORAGE ;
            
            Rep( const VEC_TYPE& object_, int times_ ) : 
                object(object_.get_ref()), times(times_), n(object_.size()){}
            
            inline STORAGE operator[]( int i ) const {
                return object[ i % n ] ;
            }
            inline int size() const { return times * n ; }
        
            template <typename Target>
            inline void apply( Target& target ) const {
                return apply_impl( target, typename Rcpp::traits::is_materialized<T>::type() );   
            }
            
        private:
            const T& object ;
            int times, n ;
            
            template <typename Target>
            inline void apply_impl( Target& target, std::true_type ) const {
                auto it = target.begin() ;
                for( int i=0; i<times; i++){
                    std::copy( object.begin(), object.end(), it ) ;
                    it += n ;
                }    
            }
            
            template <typename Target>
            inline void apply_impl( Target& target, std::false_type ) const {
                auto it = target.begin() ;
                auto source_it = sugar_begin(*this) ;
                
                // materialize the first time
                std::copy_n( sugar_begin(*this), n, it );
                
                // then copy
                for( int i=1; i<times; i++){
                    std::copy_n( target.begin(), n, it ) ;
                    it += n ;
                }
                
            }
            
        } ;
        
        template <typename T>
        class Rep_Single : public SugarVectorExpression< 
            Rcpp::traits::r_sexptype_traits<T>::rtype, 
            true, 
            Rep_Single<T>
        >, public custom_sugar_vector_expression {
        public:
            Rep_Single( T x_, int n_) : x(x_), n(n_){}
            
            inline T operator[]( int i ) const {
                return x;
            }
            inline int size() const { return n ; }
        
            template <typename Target>
            inline void apply( Target& target ) const {
                std::fill( target.begin(), target.end(), x ) ;    
            }
            
        private:
            T x ;
            int n ;
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

