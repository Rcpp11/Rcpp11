#ifndef Rcpp_api_meat_export_h
#define Rcpp_api_meat_export_h

namespace Rcpp{ 
    
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
