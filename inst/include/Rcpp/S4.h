#ifndef Rcpp_S4_h
#define Rcpp_S4_h                     

namespace Rcpp{ 

    /**
     * S4 object
     */
    RCPP_API_CLASS(S4_Impl) {     
    public:
         
        S4_Impl(){}
        
        RCPP_GENERATE_CTOR_ASSIGN(S4_Impl) 
	    
        /**
         * checks that x is an S4 object and wrap it.
         *
         * @param x must be an S4 object
         */
        S4_Impl(SEXP x){
            Storage::set__(x) ;    
        }
        
        template <typename T> S4_Impl( const T& ) ;
        
        S4_Impl& operator=( SEXP other ){
            Storage::set__( other ) ;
            return *this ;        
        }
        
        /**
         * Creates an S4 object of the requested class. 
         *
         * @param klass name of the target S4 class
         * @throw not_s4 if klass does not map to a known S4 class
         */
        S4_Impl( const std::string& klass ){
            Storage::set__( R_do_new_object(R_do_MAKE_CLASS(klass.c_str())) ) ;
            if (!Rf_inherits(Storage::get__(), klass.c_str()))
                throw S4_creation_error( klass ) ;
        }
        
        S4_Impl( const char* klass ) : S4( std::string(klass) ){} 
        
        /**
         * Indicates if this object is an instance of the given S4 class
         */
        bool is( const std::string& clazz) ;
        
        inline void update(SEXP x){
            if( ! ::Rf_isS4(x) ){
                throw not_s4() ;
            }
        }
        
    } ;

} // namespace Rcpp

#endif
