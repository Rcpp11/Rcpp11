#ifndef Rcpp_api_meat_export_h
#define Rcpp_api_meat_export_h

namespace Rcpp{ 
namespace internal{
        
    template <typename InputIterator, typename value_type>
    void export_range__dispatch( SEXP x, InputIterator first, ::Rcpp::traits::r_type_generic_tag ) {
        R_len_t n = ::Rf_length(x) ;
        for( R_len_t i=0; i<n; i++, ++first ){
            *first = ::Rcpp::as<value_type>( VECTOR_ELT(x, i) ) ;
        }
    }
                
    
} // namespace internal

    namespace traits{
        
        template < template <class, class> class ContainerTemplate, typename T > class ContainerExporter {
        public:
            typedef ContainerTemplate<T, std::allocator<T> > Container ;
            const static int RTYPE = Rcpp::traits::r_sexptype_traits<T>::rtype ;
            
            ContainerExporter( SEXP x ) : object(x){}
            ~ContainerExporter(){}
            
            Container get(){
                if( TYPEOF(object) == RTYPE ){
                   T* start = Rcpp::internal::r_vector_start<RTYPE>(object) ;
                   return Container( start, start + Rf_length(object) ) ;
                }
                Container vec( ::Rf_length(object) );
                ::Rcpp::internal::export_range( object, vec.begin() ) ;
                return vec ;
            }
        
        private:
        		SEXP object ;
        } ;
        template < template<class,class> class Container > struct container_exporter< Container, int >{
            typedef ContainerExporter< Container, int > type ;     
        } ;
        template < template<class,class> class Container > struct container_exporter< Container, double >{
            typedef ContainerExporter< Container, double > type ;
        } ;
        
    }
} // namespace Rcpp

#endif
