#ifndef Rcpp_Reference_h
#define Rcpp_Reference_h                     

namespace Rcpp{ 

    RCPP_API_CLASS(Reference_Impl), 
        public FieldProxyPolicy<Reference_Impl<Storage>>
    {
        RCPP_API_IMPL(Reference_Impl)    
    
        inline void set(SEXP x){
           if( ! ::Rf_isS4(x) ){
               throw not_s4() ;
           } 
           data = x ;
        }
        
        /**
         * Creates an reference object of the requested class. 
         *
         * @param klass name of the target reference class
         * @throw reference_creation_error if klass does not map to a known S4 class
         */
        Reference_Impl( const std::string& klass ) : 
            data( R_do_new_object(R_do_MAKE_CLASS(klass.c_str())) )
        {
            check(klass) ;    
        }
        Reference_Impl( const char* klass ) : 
            data( R_do_new_object(R_do_MAKE_CLASS(klass)) )
        {
            check(klass) ;    
        }

        bool is( const std::string& clazz) {
            return derives_from( Rf_getAttrib(data, R_ClassSymbol), clazz );
        }
        
    private:
        void check(const char* klass ){
            if (!Rf_inherits(data, klass))
                throw S4_creation_error( klass ) ;    
        }
            
    } ;

} // namespace Rcpp

#endif
