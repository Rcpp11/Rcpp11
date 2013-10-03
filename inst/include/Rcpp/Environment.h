// Copyright (C) 2009 - 2012    Dirk Eddelbuettel and Romain Francois
// Copyright (C) 2013 Romain Francois
//
// This file is part of Rcpp11.
//
// Rcpp11 is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// Rcpp11 is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Rcpp11.  If not, see <http://www.gnu.org/licenses/>.

#ifndef Rcpp_Environment_h
#define Rcpp_Environment_h

namespace Rcpp{ 

    RCPP_API_CLASS(Environment_Impl) {
    public:
    
        RCPP_GENERATE_CTOR_ASSIGN__(Environment_Impl) 
	
        /**
         * proxy class to allow read and write access to a binding in
         * an environment
         */
        class Binding {
        public: 
            /**
             * Creates  a binding
             * 
             * @param env environment in which the binding is
             * @param name name of the binding
             */
            Binding( Environment_Impl& env_, const std::string& name_) :
                env(env_), name(name_){}
            
            /**
             * Is the binding an active binding
             */
            bool active() const {
                return env.bindingIsActive( name ) ;    
            }
            
            /**
             * Is the binding locked
             */
            bool locked() const {
                return env.bindingIsLocked( name ) ;
            }
            
            /**
             * Is the binding defined
             */
            bool exists() const {
                return env.exists( name ) ;
            }
            
            /**
             * lock the binding
             */
            void lock( ) {
                env.lockBinding( name ) ;
            }
            
            /**
             * unlock the binding
             */
            void unlock() {
                env.unlockBinding( name ) ;
            }
            
            
            /* lvalue uses */
            
            /**
             * Assigning another binding to this has the effect of 
             * assigning the rhs to the environment. 
             *
             * For example :
             * Environment e = ... // get an environment somehow
             * Environment f = ... // get an environment somehow
             * e["x"] = f["y"] ;
             *
             * after this, the variable x in the environment e will
             * contain the same variable as "y" in the environment "f"
             */
            Binding& operator=(const Binding& rhs){
                env.assign( name, rhs.env.get(rhs.name) ) ;
                return *this ;
            }
            
            /**
             * Assign the rhs to the binding
             *
             * For example: 
             * Environment e= ... ; // get some environment
             * e["foo"] = SclalarInteger( 10 ) ;
             * 
             * after this e will contain the variable "foo" with the value 
             * 10L
             */
            Binding& operator=(SEXP rhs){
                env.assign( name, rhs ) ;
                return *this ;        
            }
            
            /**
             * templated assignement. The rhs if first wrapped using one
             * of the forms of "wrap" and then the wrapped value is
             * assigned to the binding
             *
             * For example: 
             * Environment e = ... ;
             * e[ "foo" ] = 10 ;
             * e[ "bar"] = "foobar" ;
             * 
             * vector<int> v; v.push_back(10); v.push_back(20 );
             * e[ "foo" ] = v ;
             * 
             * with GCC4.4 :
             * e["bla" ] = { 1,2,3};
             */
            template <typename WRAPPABLE> Binding& operator=(const WRAPPABLE& rhs) ;
            
            /* rvalue */
            /**
             * Retrieves the value of the binding as a T object
             *
             * The requirement on the T type is that as<T> makes sense
             * which can either mean that a specialization exists
             * or that T has a T(SEXP) constructor
             */
            template <typename T> operator T() const ;
            
            
        private:
            /**
             * Reference to the environment if the binding
             */
            Environment_Impl& env ;
            
            /**
             * name of the binding
             */
            std::string name ;
        } ;
    
        /**
         * Creates a binding for a variable in this environment
         *
         * The Binding class is a proxy class, so depending on how the result
         * of this operator call is used, the variable is either retrieved 
         * or modified. See the Binding class for details
         */
        const Binding operator[]( const std::string& name) const {
            return Binding( const_cast<Environment_Impl&>(*this), name );
        }
    
        /**
         * Same as above, but for a non-const Environment
         */
        Binding operator[](const std::string& name) {
            return Binding( *this, name ) ;
        }
    
        friend class Binding ;
    
        Environment_Impl(){
            Storage::set__(R_GlobalEnv) ;
        } ;

        /**
         * wraps the given environment
         *
         * if the SEXP is not an environment, and exception is thrown
         */
        Environment_Impl(SEXP x) ;
        
        /**
         * Gets the environment associated with the given name
         *
         * @param name name of the environment, e.g "package:Rcpp11"
         */
        Environment_Impl( const std::string& name ) ;
    
        /**
         * Gets the environment in the given position of the search path
         * 
         * @param pos (1-based) position of the environment, e.g pos=1 gives the
         *        global environment
         */
        Environment_Impl( int pos ) ;
    
        /**
         * The list of objects in the environment
         * 
         * the same as calling this from R: 
         * > ls( envir = this, all = all )
         *
         * @param all same meaning as in ?ls
         */ 
        SEXP ls(bool all) const{
            if( is_user_database() ){
                R_ObjectTable *tb = (R_ObjectTable*)
                    R_ExternalPtrAddr(HASHTAB(Storage::get__()));
                return tb->objects(tb) ;
            } else{
                Rboolean get_all = all ? TRUE : FALSE ;
                return R_lsInternal( Storage::get__(), get_all ) ;
            }
            return R_NilValue ;
        
        }
    
        /**
         * Get an object from the environment
         *
         * @param name name of the object
         *
         * @return a SEXP (possibly R_NilValue)
         */
        SEXP get(const std::string& name) const {
            SEXP nameSym = Rf_install(name.c_str());        
            SEXP res = Rf_findVarInFrame( Storage::get__(), nameSym ) ;
            
            if( res == R_UnboundValue ) return R_NilValue ;
            
            /* We need to evaluate if it is a promise */
            if( TYPEOF(res) == PROMSXP){
                res = Rf_eval( res, Storage::get__() ) ;
            }
            return res ;
        }
    
        /**
         * Get an object from the environment or one of its
         * parents
         *
         * @param name name of the object
         *
         */
        SEXP find( const std::string& name) const {
            SEXP nameSym = Rf_install(name.c_str());        
            SEXP res = Rf_findVar( nameSym, Storage::get__() ) ;
            
            if( res == R_UnboundValue ) throw binding_not_found(name) ;
            
            /* We need to evaluate if it is a promise */
            if( TYPEOF(res) == PROMSXP){
                res = Rf_eval( res, Storage::get__() ) ;
            }
            return res ;
        }
    
        /**
         * Indicates if an object called name exists in the 
         * environment
         *
         * @param name name of the object
         *
         * @return true if the object exists in the environment
         */
        bool exists( const std::string& name ) const {
            SEXP nameSym = Rf_install(name.c_str());        
            SEXP res = Rf_findVarInFrame( Storage::get__(), nameSym  ) ;
            return res != R_UnboundValue ;
        }
    
        /**
         * Attempts to assign x to name in this environment
         *
         * @param name name of the object to assign
         * @param x object to assign
         *
         * @return true if the assign was successfull
         * see ?bindingIsLocked
         *
         * @throw binding_is_locked if the binding is locked
         */
        bool assign( const std::string& name, SEXP x ) const{
            if( exists( name) && bindingIsLocked(name) ) throw binding_is_locked(name) ;
            SEXP nameSym = Rf_install(name.c_str());        
            Rf_defineVar( nameSym, x, Storage::get__() );
            return true ;
        }
    
        /**
         * wrap and assign. If there is a wrap method taking an object 
         * of WRAPPABLE type, then it is wrapped and the corresponding SEXP
         * is assigned in the environment
         *
         * @param name name of the object to assign
         * @param x wrappable object. anything that has a wrap( WRAPPABLE ) is fine
         */
        template <typename WRAPPABLE>
        bool assign( const std::string& name, const WRAPPABLE& x) const ;
    
        /**
         * @return true if this environment is locked
         * see ?environmentIsLocked for details of what this means
         */
        bool isLocked() const {
            return R_EnvironmentIsLocked(Storage::get__());
        }
    
        /**
         * remove an object from this environment
         */
        bool remove( const std::string& name ){
            if( exists(name) ){
                if( bindingIsLocked(name) ){
                    throw binding_is_locked(name) ;
                } else{
                    /* unless we want to copy all of do_remove, 
                       we have to go back to R to do this operation */
                    SEXP internalSym = Rf_install( ".Internal" );
                    SEXP removeSym = Rf_install( "remove" );
                    Scoped<SEXP> call = Rf_lang2(
                        internalSym, 
                        Rf_lang4(removeSym, Rf_mkString(name.c_str()), Storage::get__(), Rf_ScalarLogical( FALSE )) 
                     );
                    Rf_eval( call, R_GlobalEnv ) ;
                }
            } else{
                throw no_such_binding(name) ;
            }
            return true;
        
        }
    
        /**
         * locks this environment. See ?lockEnvironment
         *
         * @param bindings also lock the bindings of this environment ?
         */
        void lock(bool bindings = false){
            R_LockEnvironment( Storage::get__(), bindings ? TRUE: FALSE ) ;
        }
    
        /**
         * Locks the given binding in the environment. 
         * see ?bindingIsLocked
         *
         * @throw no_such_binding if there is no such binding in this environment
         */
        void lockBinding(const std::string& name){
            if( !exists( name) ) throw no_such_binding(name) ;
            SEXP nameSym = Rf_install(name.c_str());        
            R_LockBinding( nameSym, Storage::get__() ); 
        }
    
        /**
         * unlocks the given binding
         * see ?bindingIsLocked
         *
         * @throw no_such_binding if there is no such binding in this environment
         */
        void unlockBinding(const std::string& name){
            if( !exists( name) ) throw no_such_binding(name) ;
            SEXP nameSym = Rf_install(name.c_str());        
            R_unLockBinding( nameSym, Storage::get__() );
        }
    
        /**
         * @param name name of a potential binding
         *
         * @return true if the binding is locked in this environment
         * see ?bindingIsLocked
         *
         * @throw no_such_binding if there is no such binding in this environment
         */
        bool bindingIsLocked(const std::string& name) const {
            if( !exists( name) ) throw no_such_binding(name) ;
            SEXP nameSym = Rf_install(name.c_str());        
            return R_BindingIsLocked(nameSym, Storage::get__()) ;
        }
    
        /**
         *
         * @param name name of a binding
         * 
         * @return true if the binding is active in this environment
         * see ?bindingIsActive
         *
         * @throw no_such_binding if there is no such binding in this environment
         */
        bool bindingIsActive(const std::string& name) const {
            if( !exists( name) ) throw no_such_binding(name) ;
            SEXP nameSym = Rf_install(name.c_str());        
            return R_BindingIsActive(nameSym, Storage::get__()) ;
        }
    
        /** 
         * Indicates if this is a user defined database.
         */
        bool is_user_database() const{
            return OBJECT(Storage::get__()) && Rf_inherits(Storage::get__(), "UserDefinedDatabase") ;
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
         * @return the Rcpp namespace
         */
        static Environment_Impl Rcpp11_namespace(){
            return internal::get_Rcpp11_namespace() ;
        }
    
        /**
         * @param name the name of the package of which we want the namespace
         *
         * @return the namespace of the package
         *
         * @throw no_such_namespace 
         */
        static Environment_Impl namespace_env(const std::string& ) ;
    
        /**
         * The parent environment of this environment
         */
        Environment_Impl parent() const {
            return Environment( ENCLOS(Storage::get__()) ) ;
        }
    
        /**
         * creates a new environment whose this is the parent
         */
        Environment_Impl new_child(bool hashed) ;
        
        void update(SEXP){}
    };

} // namespace Rcpp

#endif
