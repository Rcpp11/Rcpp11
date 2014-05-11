#ifndef Rcpp_S4_h
#define Rcpp_S4_h                     

namespace Rcpp{ 

    /**
     * S4 object
     */
    RCPP_API_CLASS(S4_Impl) {     
        RCPP_API_IMPL(S4_Impl) 
        
        inline void set(SEXP x){
           if( ! ::Rf_isS4(x) ){
               throw not_s4() ;
           } 
           data = x ;
        }
        
        /**
         * Creates an S4 object of the requested class. 
         *
         * @param klass name of the target S4 class
         * @throw not_s4 if klass does not map to a known S4 class
         */
        S4_Impl( const std::string& klass ) : 
            data( R_do_new_object(R_do_MAKE_CLASS(klass.c_str())) )
        {
            check(klass.c_str());
        }
        
        S4_Impl( const char* klass ) : 
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
