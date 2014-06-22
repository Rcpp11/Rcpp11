#ifndef Rcpp_S4_h
#define Rcpp_S4_h                     

namespace Rcpp{ 

    /**
     * S4 object
     */
    template <typename Storage>
    class S4_Impl {     
        RCPP_API_IMPL(S4_Impl) 
        
        inline void set(SEXP x){
           if( ! ::Rf_isS4(x) ){
               stop("not an S4 object");
           } 
           data = x ;
        }
        
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
            if (!inherits(data, klass))
                stop("error creating S4 object of class: %s", klass) ;
        }
    } ;

} // namespace Rcpp

#endif
