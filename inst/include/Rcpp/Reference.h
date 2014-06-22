#ifndef Rcpp_Reference_h
#define Rcpp_Reference_h                     

namespace Rcpp{ 

    template <typename Storage>
    class Reference_Impl {
        RCPP_API_IMPL(Reference_Impl)    
    
        inline void set(SEXP x){
           if( ! ::Rf_isS4(x) ){
               stop("not an S4 object");
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
        
        inline FieldProxy<Reference_Impl> operator[](const std::string& s){
            return field(*this,s) ;    
        }
        
        inline const FieldProxy<Reference_Impl> operator[](const std::string& s) const{
            return field(*this,s) ;    
        }
        
    private:
        void check(const char* klass ){
            if (!inherits(data, klass))
                stop("error creating S4 object") ;
        }
            
    } ;

} // namespace Rcpp

#endif
