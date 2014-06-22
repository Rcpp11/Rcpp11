#ifndef Rcpp_Environment_h
#define Rcpp_Environment_h

namespace Rcpp{ 

    template <typename Storage>
    class Environment_Impl {
        RCPP_API_IMPL(Environment_Impl)
        
    private:
        
        inline SEXP as_environment(SEXP x){  
            if( Rf_isEnvironment(x) ) return x ;
            return Rcpp_eval( Rf_lang2( Rf_install("as.environment"), x ) );
        }
    
    public:
        
        inline void set(SEXP x){
            data = as_environment(x) ;        
        }
        
        Environment_Impl() : data(R_GlobalEnv){}
        
        Environment_Impl( const std::string& name ) {
            /* similar to matchEnvir@envir.c */
            if( name == ".GlobalEnv" ) {
                data = R_GlobalEnv ;
            } else if( name == "package:base" ){
                data = R_BaseEnv ;
            } else{
                SEXP res = R_NilValue ;
                try{
                    SEXP asEnvironmentSym = Rf_install("as.environment"); 
                    res = Rcpp_eval(Rf_lang2( asEnvironmentSym, Rf_mkString(name.c_str()) ) ) ;
                } catch( ... ){
                    stop("no such environment '%s'", name ) ;
                }
                data = res ;
            }
        }
        
        Environment_Impl( int pos ) {
            try{
                SEXP asEnvironmentSym = Rf_install("as.environment"); 
                data = Rcpp_eval( Rf_lang2( asEnvironmentSym, Rf_ScalarInteger(pos) ) ) ;
            } catch( ... ){
                stop( "no such environment '%d'", pos );
            }    
        }
    
        SEXP ls(Rboolean all) const{
            if( is_user_database() ){
                R_ObjectTable *tb = (R_ObjectTable*)R_ExternalPtrAddr(HASHTAB(data));
                return tb->objects(tb) ;
            } else{
                return R_lsInternal( data, all) ;
            }
            return R_NilValue ;
        
        }
        SEXP ls(bool all) const{
            return ls( all ? TRUE : FALSE );    
        }
    
        SEXP get(const std::string& name) const {
            SEXP res = Rf_findVarInFrame( data, Symbol(name) ) ;
            
            if( res == R_UnboundValue ) return R_NilValue ;
            
            /* We need to evaluate if it is a promise */
            if( TYPEOF(res) == PROMSXP){
                res = Rf_eval( res, data ) ;
            }
            return res ;
        }
    
        SEXP find( const std::string& name) const {
            SEXP res = Rf_findVar( Symbol(name), data ) ;
            
            if( res == R_UnboundValue ) stop("binding not found: %s", name);  
            
            /* We need to evaluate if it is a promise */
            if( TYPEOF(res) == PROMSXP){
                res = Rf_eval( res, data ) ;
            }
            return res ;
        }
    
        bool exists( const std::string& name ) const {
            SEXP res = Rf_findVarInFrame( data, Symbol(name)  ) ;
            return res != R_UnboundValue ;
        }
    
        template <typename T>
        void assign( const std::string& name, const T& x) const {
            if( exists( name) && bindingIsLocked(name) ) 
                stop("binding is locked : %s", name) ;
            Rf_defineVar( Symbol(name), wrap(x), data );
        }
    
        /**
         * @return true if this environment is locked
         * see ?environmentIsLocked for details of what this means
         */
        bool isLocked() const {
            return R_EnvironmentIsLocked(data);
        }
    
        /**
         * remove an object from this environment
         */
        bool remove( const std::string& name ){
            if( exists(name) ){
                if( bindingIsLocked(name) ){
                    stop("binding is locked: %s", name); 
                } else{
                    /* unless we want to copy all of do_remove, 
                       we have to go back to R to do this operation */
                    SEXP internalSym = Rf_install( ".Internal" );
                    SEXP removeSym = Rf_install( "remove" );
                    Shield<SEXP> call = Rf_lang2(
                        internalSym, 
                        Rf_lang4(removeSym, Rf_mkString(name.c_str()), data, R_FalseValue) 
                     );
                    Rf_eval( call, R_GlobalEnv ) ;
                }
            } else{
                stop("no such binding: %s", name) ;
            }      
            return true;
        
        }
    
        /**
         * locks this environment. See ?lockEnvironment
         *
         * @param bindings also lock the bindings of this environment ?
         */
        void lock(bool bindings = false){
            R_LockEnvironment( data, bindings ? TRUE: FALSE ) ;
        }
    
        void lockBinding(const std::string& name){
            if( !exists( name) ) stop("no such binding: %s", name) ;
            R_LockBinding( Symbol(name), data ); 
        }
    
        void unlockBinding(const std::string& name){
            if( !exists( name) ) stop("no such binding: %s", name) ;
            R_unLockBinding( Symbol(name), data );
        }
    
        bool bindingIsLocked(const std::string& name) const {
            if( !exists( name) ) stop("no such binding: %s", name) ;
            return R_BindingIsLocked(Symbol(name), data) ;
        }
    
        bool bindingIsActive(const std::string& name) const {
            if( !exists( name) ) stop("no such binding: %s", name) ;
            return R_BindingIsActive(Symbol(name), data) ;
        }
    
        /** 
         * Indicates if this is a user defined database.
         */
        bool is_user_database() const{
            return OBJECT(data) && inherits(data, "UserDefinedDatabase") ;
        }
    
        /**
         * @return the global environment. See ?globalenv
         */
        static Environment_Impl global_env(){
            return Environment(R_GlobalEnv) ;   
        }
    
        /**
         * @return The empty environment. See ?emptyenv
         */
        static Environment_Impl empty_env(){
            return Environment(R_EmptyEnv) ;
        }
    
        /**
         * @return the base environment. See ?baseenv
         */
        static Environment_Impl base_env(){
            return Environment(R_BaseEnv) ;   
        }
    
        /**
         * @return the base namespace. See ?baseenv
         */
        static Environment_Impl base_namespace(){
            return Environment(R_BaseNamespace) ;   
        }
    
        /**
         * @param name the name of the package of which we want the namespace
         *
         * @return the namespace of the package
         *
         * @throw no_such_namespace 
         */
        static Environment_Impl namespace_env(const std::string& package) {
            SEXP env = R_NilValue ;
            try{
                SEXP getNamespaceSym = Rf_install("getNamespace");
                env = Rcpp_eval( Rf_lang2(getNamespaceSym, Rf_mkString(package.c_str()) ) ) ;
            } catch( ... ){
                stop("no such namespace : '%s' ", package);
            }
            return Environment( env ) ;        
        }
    
        /**
         * The parent environment of this environment
         */
        Environment_Impl parent() const {
            return Environment( ENCLOS(data) ) ;
        }
    
        /**
         * creates a new environment whose this is the parent
         */
        Environment_Impl new_child(bool hashed) {
            SEXP newEnvSym = Rf_install("new.env");
            return Environment( Rcpp_eval(Rf_lang3( newEnvSym, Rf_ScalarLogical(hashed), data )) );    
        }
        
        Binding<Environment_Impl> operator[](const std::string& name){
            return Binding<Environment_Impl>( *this, name ) ;  
        }
        const Binding<Environment_Impl> operator[]( const std::string& name) const {
            return Binding<Environment_Impl>( const_cast<Environment_Impl&>(*this), name ) ;    
        }
    
        
    };

} // namespace Rcpp

#endif
