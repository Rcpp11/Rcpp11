#ifndef Rcpp__sugar__sum_h
#define Rcpp__sugar__sum_h

namespace Rcpp{
    namespace sugar{
    
    template <typename T>
    inline T get_zero(){
        return static_cast<T>(0) ;
    }
    template <>
    inline Rcomplex get_zero<Rcomplex>(){
        Rcomplex cx = {0.0,0.0};
        return cx ;
    }
    
        
    template <int RTYPE, bool HAS_NA, typename T>
    class Sum : public Lazy< typename Rcpp::traits::storage_type<RTYPE>::type , Sum<RTYPE,HAS_NA,T> > {
    public:
        typedef typename Rcpp::VectorBase<RTYPE,HAS_NA,T> VEC_TYPE ;
        typedef typename Rcpp::traits::storage_type<RTYPE>::type STORAGE ;
        
        Sum( const VEC_TYPE& object_ ) : object(object_){}
    
        STORAGE get() const {
            STORAGE result = get_zero<STORAGE>() ;
            int n = object.size() ;
            STORAGE current ;
            auto it = sugar_begin(object) ;
            for( int i=0; i<n; i++, ++it){
                current = *it ;
                if( current == NA ) 
                    return NA ;
                result += current ;
            }
            return result ;
        }         
    private:
        const VEC_TYPE& object ;
    } ;
    
    // RTYPE = REALSXP
    template <bool HAS_NA, typename T>
    class Sum<REALSXP,HAS_NA,T> : public Lazy< double , Sum<REALSXP,HAS_NA,T> > {
    public:
        typedef typename Rcpp::VectorBase<REALSXP,HAS_NA,T> VEC_TYPE ;
        
        Sum( const VEC_TYPE& object_ ) : object(object_){}
    
        double get() const {
            return std::accumulate( sugar_begin(object), sugar_end(object), 0.0 ) ;
        }         
    private:
        const VEC_TYPE& object ;
    } ;
    
    
    template <int RTYPE, typename T>
    class Sum<RTYPE,false,T> : public Lazy< typename Rcpp::traits::storage_type<RTYPE>::type , Sum<RTYPE,false,T> > {
    public:
        typedef typename Rcpp::VectorBase<RTYPE,false,T> VEC_TYPE ;
        typedef typename Rcpp::traits::storage_type<RTYPE>::type STORAGE ;
        
        Sum( const VEC_TYPE& object_ ) : object(object_){}
    
        STORAGE get() const {
            return std::accumulate( sugar_begin(object), sugar_end(object), get_zero<STORAGE>() ) ;
        }         
    private:
        const VEC_TYPE& object ;
    } ;
    
    } // sugar
    
    template <bool NA, typename T>
    inline sugar::Sum<CPLXSXP,NA,T> sum( const VectorBase<CPLXSXP,NA,T>& t){
        return sugar::Sum<CPLXSXP,NA,T>( t ) ;
    }
    
    template <bool NA, typename T>
    inline sugar::Sum<INTSXP,NA,T> sum( const VectorBase<INTSXP,NA,T>& t){
        return sugar::Sum<INTSXP,NA,T>( t ) ;
    }
    
    template <bool NA, typename T>
    inline sugar::Sum<REALSXP,NA,T> sum( const VectorBase<REALSXP,NA,T>& t){
        return sugar::Sum<REALSXP,NA,T>( t ) ;
    }
    
    template <bool NA, typename T>
    inline sugar::Sum<LGLSXP,NA,T> sum( const VectorBase<LGLSXP,NA,T>& t){
        return sugar::Sum<LGLSXP,NA,T>( t ) ;
    }

} // Rcpp
#endif

