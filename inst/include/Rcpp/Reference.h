#ifndef Rcpp_Reference_h
#define Rcpp_Reference_h                     

#include <Rcpp/S4.h>
#include <Rcpp/exceptions.h>

namespace Rcpp{ 

    template < template <class> class StoragePolicy > 
    class Reference_Impl : 
        public S4_Impl<StoragePolicy>, 
        public FieldProxyPolicy<Reference_Impl<StoragePolicy>>
    {
    public:
        typedef S4_Impl<StoragePolicy> Base ;
        typedef typename Base::Storage Storage ;
        
        /**
         * checks that x is an S4 object of a reference class and wrap it.
         *
         * @param x must be an S4 object of some reference class
         */
        Reference_Impl(SEXP x) : Base(x){}
        
        template <typename T>
        Reference_Impl(const T& object ) : Reference(wrap(object)){}
        
        Reference_Impl& operator=( SEXP other ) {
            Storage::set__( other ) ;
            return *this ;
        }
        
        /**
         * Creates an reference object of the requested class. 
         *
         * @param klass name of the target reference class
         * @throw reference_creation_error if klass does not map to a known S4 class
         */
        Reference_Impl( const std::string& klass ){
            // using callback to R as apparently R_do_new_object always makes the same environment
            SEXP newSym = Rf_install("new");
            Shield<SEXP> call = Rf_lang2( newSym, Rf_mkString( klass.c_str() ) ) ;
            Storage::set__( Rcpp_eval( call ) ) ;
        
        }
        Reference_Impl( const char* klass ) : Reference(std::string(klass)){}
       
    } ;

} // namespace Rcpp

#endif
