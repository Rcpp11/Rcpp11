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
            set(x) ;    
        }
        
        template <typename T> 
        S4_Impl( const T& object ) : S4_Impl( wrap(object) ){}
        
        S4_Impl& operator=( SEXP other ){
            set(other);
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
        bool is( const std::string& clazz) {
            SEXP cl = Rf_getAttrib( Storage::get__(), R_ClassSymbol ) ; 
            if(cl == R_NilValue) return false ;
            
            // simple test for exact match
            if( ! clazz.compare( CHAR(STRING_ELT(cl, 0)) ) ) return true ;
                    
            SEXP containsSym = Rf_install("contains");
            Shield<SEXP> contains = R_do_slot(R_getClassDef(CHAR(Rf_asChar(cl))),containsSym); 
            SEXP res = Rf_getAttrib(contains,R_NamesSymbol );
            if(res == R_NilValue) return false ;
            
            return std::any_of( 
                VECTOR_PTR(res), VECTOR_PTR(res) + LENGTH(res), 
                [&](SEXP s){ return clazz == CHAR(s) ; } 
            ) ;
                    
        }
        
    private:
        
        inline void set(SEXP x){
           if( ! ::Rf_isS4(x) ){
               throw not_s4() ;
           } 
           Storage::set__(x) ;
        }
        
    } ;

} // namespace Rcpp

#endif
