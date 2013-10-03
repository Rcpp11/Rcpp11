// api.cpp:  Rcpp api
//
// Copyright (C) 2012 - 2013  Dirk Eddelbuettel and Romain Francois
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
  
#include <Rcpp.h>

#include "internal.h" 

// for R_ObjectTable
#include <R_ext/Callbacks.h>
#include <R_ext/PrtUtil.h>

#define RCPP_USE_NEW_PRESERVE_RELEASE 0

// {{{ Rcpp api classes
namespace Rcpp {
         
    // {{{ SexpStack
    static SEXP RCPP_PROTECTION_STACK = R_NilValue ;
    static SEXP* RCPP_PROTECTION_STACK_PTR = 0 ;
    static bool RCPP_PROTECTION_STACK_READY = false ;
    
    #define GET_TOP() TRUELENGTH(RCPP_PROTECTION_STACK)
    #define SET_TOP(TOP) SET_TRUELENGTH(RCPP_PROTECTION_STACK, TOP)
    
    inline void init_ProtectionStack(){
        if(!RCPP_PROTECTION_STACK_READY){
            RCPP_PROTECTION_STACK = get_Rcpp_protection_stack() ;
            RCPP_PROTECTION_STACK_PTR = get_vector_ptr(RCPP_PROTECTION_STACK) ;
            RCPP_PROTECTION_STACK_READY = true ;
        }
    }
    
    SEXP Rcpp_PreserveObject(SEXP x){ 
#if RCPP_USE_NEW_PRESERVE_RELEASE
        if( x != R_NilValue ){
            init_ProtectionStack();
            int top = GET_TOP() ;
            RCPP_DEBUG( "Rcpp_PreserveObject( <%p>), top = %d", x, top )
            top++ ; 
            // RCPP_PROTECTION_STACK_PTR[top] = x ;
            set_vector_elt( RCPP_PROTECTION_STACK, top, x ) ;
            SET_TOP(top) ;
        }
        #if RCPP_DEBUG_LEVEL > 1 
        Rcpp_Stack_Debug() ;
        #endif
#else
        if( x != R_NilValue ) {
            R_PreserveObject(x); 
        }
#endif
        return x ;
    }
    void Rcpp_ReleaseObject(SEXP x){
#if RCPP_USE_NEW_PRESERVE_RELEASE
        if( x != R_NilValue ){
            init_ProtectionStack();
            
            int top = GET_TOP();
            RCPP_DEBUG( "Rcpp_ReleaseObject( <%p>),  top = %d )", x, top )
        
            if( x == RCPP_PROTECTION_STACK_PTR[top] ) {
                RCPP_PROTECTION_STACK_PTR[top] = R_NilValue ;
                top-- ;
                SET_TOP(top) ;
            } else {
                int i = top ;
                for( ; i>=0; i--){
                    if( x == RCPP_PROTECTION_STACK_PTR[i] ){
                        // swap position i and top
                        // perhaps should bubble down instead
                        
                        RCPP_PROTECTION_STACK_PTR[i] = RCPP_PROTECTION_STACK_PTR[top] ;
                        RCPP_PROTECTION_STACK_PTR[top] = R_NilValue ;
                        top-- ;
                
                        SET_TOP(top) ;
                        break ;
                    }
                }
                #if RCPP_DEBUG_LEVEL > 0
                if( i < 0 ) RCPP_DEBUG( "!!!! STACK ERROR, did not find SEXP <%p> (i=%d)", x, i ) ;
                #endif  
            }
            #if RCPP_DEBUG_LEVEL > 1 
            Rcpp_Stack_Debug() ;
            #endif
        }
#else
        if (x != R_NilValue) {
            R_ReleaseObject(x); 
        }
#endif
    }

    SEXP Rcpp_ReplaceObject(SEXP x, SEXP y){
        if( x == R_NilValue ){
            Rcpp_PreserveObject( y ) ;    
        } else if( y == R_NilValue ){
            Rcpp_ReleaseObject( x ) ;
        } else {
#if RCPP_USE_NEW_PRESERVE_RELEASE
            init_ProtectionStack();
            
            int top = GET_TOP(); 
            RCPP_DEBUG( "Rcpp_ReplaceObject( <%p> , <%p> ),  top = %d )", x, y, top )
            int i = top ;
            for( ; i>= 0; i--){
                if( x == RCPP_PROTECTION_STACK_PTR[i] ){
                    set_vector_elt( RCPP_PROTECTION_STACK, i, y) ;
                    break ;
                }
            }
            #if RCPP_DEBUG_LEVEL > 0
            if( i < 0 ) RCPP_DEBUG( "STACK ERROR, did not find SEXP <%p>", x ) ;
            #endif
            
            #if RCPP_DEBUG_LEVEL > 1 
            Rcpp_Stack_Debug() ;
            #endif
#else        
            // if we are setting to the same SEXP as we already have, do nothing 
            if (x != y) {
                
                // the previous SEXP was not NULL, so release it 
                Rcpp_ReleaseObject(x);
                
                // the new SEXP is not NULL, so preserve it 
                Rcpp_PreserveObject(y);
            }
#endif
        }
        return y ;
    }                                                                                          

    void Rcpp_Stack_Debug(){
        init_ProtectionStack();
        int top = GET_TOP() ;
        if( top == -1 ){
            Rprintf( "Rcpp_Stack_Debug [<<%p>>] : empty stack\n", RCPP_PROTECTION_STACK )    ;
        } else {                      
            int n = top + 1  ;
            Rprintf( "Rcpp_Stack_Debug, %d objects on stack [<<%p>>]\n", n, RCPP_PROTECTION_STACK  )    ;
            for( int i=0; i<n;i++){
                SEXP ptr = RCPP_PROTECTION_STACK_PTR[i] ;
                Rprintf( "[%4d] TYPE = %s, pointer = <%p>\n", i, sexp_to_name(TYPEOF(ptr)), ptr ) ;    
            }
        }
    }
    // }}}
    
                          

    // {{{ Rostream
    template <> inline std::streamsize Rstreambuf<true>::xsputn(const char *s, std::streamsize num ) {
        Rprintf( "%.*s", num, s ) ;
        return num ;
    }
    template <> inline std::streamsize Rstreambuf<false>::xsputn(const char *s, std::streamsize num ) {
        REprintf( "%.*s", num, s ) ; 
        return num ;
    }
    
    template <> inline int Rstreambuf<true>::overflow(int c ) {
      if (c != EOF) Rprintf( "%.1s", &c ) ;
      return c ;
    }
    template <> inline int Rstreambuf<false>::overflow(int c ) {
      if (c != EOF) REprintf( "%.1s", &c ) ;
      return c ;
    }
        
    template <> inline int Rstreambuf<true>::sync(){
        ::R_FlushConsole() ;
        return 0 ;
    }
    template <> inline int Rstreambuf<false>::sync(){
        ::R_FlushConsole() ;
        return 0 ;
    }
    Rostream<true>  Rcout;
    Rostream<false> Rcerr;
    // }}}
    
    // {{{ Evaluator
    SEXP Evaluator::run(SEXP expr_, SEXP env) {
        RCPP_DEBUG( "Evaluator::run( expr = <%p>, env = <%p> )", expr_, env ) 
        Scoped<SEXP> expr = expr_ ;

        reset_current_error() ; 

        Environment RCPP = Environment::Rcpp11_namespace(); 
        static SEXP tryCatchSym = NULL, evalqSym, conditionMessageSym, errorRecorderSym, errorSym ;
        if (!tryCatchSym) {
            tryCatchSym               = ::Rf_install("tryCatch");
            evalqSym                  = ::Rf_install("evalq");
            conditionMessageSym       = ::Rf_install("conditionMessage");
            errorRecorderSym          = ::Rf_install(".rcpp_error_recorder");
            errorSym                  = ::Rf_install("error");
        }
        RCPP_DEBUG( "  [Evaluator::run] RCPP = " ) 
        
        Scoped<SEXP> call = Rf_lang3( 
            tryCatchSym, 
            Rf_lang3( evalqSym, expr, env ),
            errorRecorderSym
        ) ;
        SET_TAG( CDDR(call), errorSym ) ;
        /* call the tryCatch call */
        Scoped<SEXP> res  = ::Rf_eval( call, RCPP );
        
        if( error_occured() ) {
            Scoped<SEXP> current_error        =  rcpp_get_current_error() ;
            Scoped<SEXP> conditionMessageCall = ::Rf_lang2(conditionMessageSym, current_error) ;
            Scoped<SEXP> condition_message    = ::Rf_eval(conditionMessageCall, R_GlobalEnv) ;
            std::string message(CHAR(::Rf_asChar(condition_message)));
            throw eval_error(message) ;
        }

        return res ;
    }

    SEXP Evaluator::run( SEXP expr) {
        return run(expr, R_GlobalEnv );
    }
    // }}}
    
    /* S4 */

    // }}}
  
    // {{{ Function
    Function::Function(SEXP x) {
        RCPP_DEBUG( "Function::Function(SEXP = <%p>)", x)
        switch( TYPEOF(x) ){
        case CLOSXP:
        case SPECIALSXP:
        case BUILTINSXP:
            set__(x) ;
            break; 
        default:
            throw not_compatible("cannot convert to function") ;
        }
    }
	
    Function::Function(const std::string& name) {
        SEXP nameSym = Rf_install( name.c_str() );	
        set__( Rf_findFun( nameSym, R_GlobalEnv ) ) ;
    }
	
   
    SEXP Function::environment() const {
        if( TYPEOF(get__()) != CLOSXP ) {
            throw not_a_closure() ;
        }
        return CLOENV(get__()) ;
    }
	
    SEXP Function::body() const {
        return BODY( get__() ) ;
    }

    // }}}
    
    // {{{ DottedPair
    SEXP grow( SEXP head, SEXP tail ){
        Scoped<SEXP> x = head ;
        Scoped<SEXP> res = Rf_cons( x, tail ) ;
        return res ;    
    }
    
    namespace internal{
        template <> Rcpp::String as<Rcpp::String>(SEXP x, ::Rcpp::traits::r_type_string_tag ) {
            if( ! ::Rf_isString(x) ){
                throw ::Rcpp::not_compatible( "expecting a string" ) ;
            }
            if (Rf_length(x) != 1) {
                throw ::Rcpp::not_compatible( "expecting a single value");
            }
            return STRING_ELT( x, 0 ) ;
        }
    }
    
    // }}}
    
    // {{{ Promise
    Promise::Promise(SEXP x) {
        if( TYPEOF(x) != PROMSXP )
            throw not_compatible("not a promise") ;
        set__(x) ;
    }

    int Promise::seen() const {
        return PRSEEN(get__());
    }

    SEXP Promise::value() const {
        SEXP val = PRVALUE(get__()) ; 
        if( val == R_UnboundValue ) throw unevaluated_promise() ;
        return val ;
    }
	
    bool Promise::was_evaluated() const {
        return PRVALUE(get__()) != R_UnboundValue ;
    }

    Environment Promise::environment() const {
        return Environment(PRENV(get__())) ;
    }

    ExpressionVector Promise::expression() const {
        return ExpressionVector(PRCODE(get__())) ;
    }

    // }}}
       
    // {{{ WeakReference
    WeakReference::WeakReference( SEXP x) {
        if( TYPEOF(x) != WEAKREFSXP )
            throw not_compatible( "not a weak reference" ) ;
        set__(x) ;
    }
        
    SEXP WeakReference::key() {
        return R_WeakRefKey(get__()) ;
    }
        
    SEXP WeakReference::value() {
        return R_WeakRefValue(get__());
    }
    // }}}
    
    // {{{ Symbol
    Symbol::Symbol( SEXP x ) {
        if( x != R_NilValue ){
            int type = TYPEOF(x) ;
            switch( type ){
            case SYMSXP:
                set__( x ) ;
                break; /* nothing to do */
            case CHARSXP: {
                SEXP charSym = Rf_install(CHAR(x));     
                set__( charSym ) ;
                break ;
            }
            case STRSXP: {
                /* FIXME: check that there is at least one element */
                SEXP charSym = Rf_install( CHAR(STRING_ELT(x, 0 )) ); 
                set__( charSym );
                break ;
            }
            default:
                throw not_compatible("cannot convert to symbol (SYMSXP)") ;
            }
        } 
    }
        
    Symbol::Symbol(const std::string& symbol) {
        set__(Rf_install(symbol.c_str()));
    }
        
    // }}}    
    
    // {{{ Language
    Language::Language( const Function& function){
        set__( Rf_lang1( function ) ) ;    
    }    
    
    void Language::setSymbol( const std::string& symbol){
        setSymbol( Symbol( symbol ) ) ;
    }
        
    void Language::setSymbol( const Symbol& symbol){
        SEXP data = get__() ;
        SETCAR( data, symbol ) ;
        SET_TAG(data, R_NilValue);
    }
        
    void Language::setFunction( const Function& function){
        SEXP data = get__() ;
        SETCAR( data, function );
        SET_TAG(data, R_NilValue);
    }
        
    SEXP Language::eval() {
        return eval( R_GlobalEnv ) ;
    }
        
    SEXP Language::eval( SEXP env ) {
        return internal::try_catch( get__(), env );
    }
    
    SEXP Language::fast_eval(){
        return Rf_eval( get__(), R_GlobalEnv ) ;    
    }
    SEXP Language::fast_eval(SEXP env ){
        return Rf_eval( get__(), env ) ;
    }
    // }}}
    
    // {{{ Dimension
    Dimension::Dimension() : dims(){}
        
    Dimension::Dimension(SEXP x): dims(){
        dims = as< std::vector<int> >(x) ;
    }
        
    Dimension::Dimension( const Dimension& other ) : dims(){
        dims = other.dims ; /* copy */
    }
        
    Dimension& Dimension::operator=(const Dimension& other){
        dims = other.dims ; /* copy */
        return *this ;
    }
        
    Dimension::Dimension(const size_t& n1) : dims(1){
        dims[0] = n1 ;
    }
        
    Dimension::Dimension(const size_t& n1, const size_t& n2) : dims(2){
        dims[0] = n1 ;
        dims[1] = n2 ;
    }
        
    Dimension::Dimension(const size_t& n1, const size_t& n2, const size_t& n3) : dims(3){
        dims[0] = n1 ;
        dims[1] = n2 ;
        dims[2] = n3 ;
    }
        
    Dimension::operator SEXP() const {
        return wrap( dims.begin(), dims.end() ) ;
    }
        
    int Dimension::size() const {
        return static_cast<int>( dims.size() ) ;
    }
        
    int Dimension::prod() const {
        return std::accumulate( dims.begin(), dims.end(), 1, std::multiplies<int>() ) ;
    }
        
    Dimension::reference Dimension::operator[](int i) {
        if( i < 0 || i>=static_cast<int>(dims.size()) ) throw std::range_error("index out of bounds") ;
        return dims.at(i) ;
    }

    Dimension::const_reference Dimension::operator[](int i) const {
        if( i < 0 || i>=static_cast<int>(dims.size()) ) throw std::range_error("index out of bounds") ;
        return dims.at(i) ;
    }    
    // }}}
    
    // {{{ Formula
    Formula::Formula() : Language(){}
        
    Formula::Formula(SEXP x) : Language(){
        switch( TYPEOF( x ) ){
        case LANGSXP:
            if( ::Rf_inherits( x, "formula") ){
                set__( x );
            } else{
                set__( internal::convert_using_rfunction( x, "as.formula") ) ;
            }
            break;
        case EXPRSXP:
        case VECSXP:
            /* lists or expression, try the first one */
            if( ::Rf_length(x) > 0 ){
                SEXP y = VECTOR_ELT( x, 0 ) ;
                if( ::Rf_inherits( y, "formula" ) ){
                    set__( y ) ;  
                } else{
                    SEXP z = internal::convert_using_rfunction( y, "as.formula") ;
                    set__( z ) ;
                }
            } else{
                throw not_compatible( "cannot create formula from empty list or expression" ) ; 
            }
            break;
        default:
            set__( internal::convert_using_rfunction( x, "as.formula") ) ;
        }
    }
        
    Formula::Formula( const std::string& code) : 
        Language( internal::convert_using_rfunction( ::Rf_mkString(code.c_str()), "as.formula") ) 
    {}
        
    // }}}
    
    // {{{ S4
    S4& S4::operator=( SEXP other ) {
        set__( other ) ;
        return *this ;
    }
        
    S4::S4( const std::string& klass ) {
        set__( R_do_new_object(R_do_MAKE_CLASS(klass.c_str())) ) ;
        if (!Rf_inherits(get__(), klass.c_str()))
            throw S4_creation_error( klass ) ;
    }
    S4::S4( const char* klass ) : S4( std::string(klass) ) {} ;
        
    bool S4::is( const std::string& clazz ) {
        CharacterVector cl = attr("class");
                
        // simple test for exact match
        if( ! clazz.compare( cl[0] ) ) return true ;
                
        try{
            SEXP containsSym = ::Rf_install("contains");
            CharacterVector res(::Rf_getAttrib(
                                    ::R_do_slot(::R_getClassDef(CHAR(::Rf_asChar(as<SEXP>(cl)))),
                                                containsSym),
                                    R_NamesSymbol));

            // 
            // mimic the R call: 
            // names( slot( getClassDef( cl ), "contains" ) )
            // 
            // SEXP slotSym = Rf_install( "slot" ), // cannot cause gc() once in symbol table
            //     getClassDefSym = Rf_install( "getClassDef" );
            // CharacterVector res = internal::try_catch(Rf_lang2(R_NamesSymbol,
            //                                                    Rf_lang3(slotSym,
            //                                                             Rf_lang2( getClassDefSym, cl ), 
            //                                                             Rf_mkString( "contains" )))) ;
            return any( res.begin(), res.end(), clazz.c_str() ) ;
        } catch( ... ){
            // we catch eval_error and also not_compatible when 
            // contains is NULL
        }
        return false ;
                
    }
        
    // }}}
    
    // {{{ Reference 
    Reference::Reference() : S4(){}
    
    Reference::Reference(SEXP x) : S4(){
        set__(x) ;
    }
    
    Reference& Reference::operator=( SEXP other ) {
        set__( other ) ;
        return *this ;
    }
    
    Reference::Reference( const std::string& klass ) : S4(){
        // using callback to R as apparently R_do_new_object always makes the same environment
        SEXP newSym = Rf_install("new");
        Scoped<SEXP> call = Rf_lang2( newSym, Rf_mkString( klass.c_str() ) ) ;
        set__( Rcpp::internal::try_catch( call ) ) ;
    }
    Reference::Reference( const char* klass ) : Reference(std::string(klass)){}
    
    // }}}
 
    // {{{ Environment
    Environment::Environment(SEXP x) {
        set__(x) ;
        RCPP_DEBUG( "Environment::Environment( SEXP = %p)", x ) ;
        if( ! Rf_isEnvironment(x) ) {
            /* not an environment, but maybe convertible to one using as.environment, try that */
            SEXP res ;
            try {
                SEXP asEnvironmentSym = Rf_install("as.environment"); 
                res = Evaluator::run( Rf_lang2(asEnvironmentSym, x ) ) ;
            } catch( const eval_error& ex){
                throw not_compatible( "cannot convert to environment"  ) ; 
            }
            set__( res ) ;
        }
    }

    Environment::Environment( const std::string& name){
        set__(R_EmptyEnv) ;
        /* similar to matchEnvir@envir.c */
        if( name == ".GlobalEnv" ) {
            set__( R_GlobalEnv ) ;
        } else if( name == "package:base" ){
            set__( R_BaseEnv ) ;
        } else{
            SEXP res = R_NilValue ;
            try{
                SEXP asEnvironmentSym = Rf_install("as.environment"); 
                res = Evaluator::run(Rf_lang2( asEnvironmentSym, Rf_mkString(name.c_str()) ) ) ;
            } catch( const eval_error& ex){
                throw no_such_env(name) ;
            }
            set__( res ) ;
        }
    }
    
    Environment::Environment(int pos) {
        set__( R_GlobalEnv) ;
        SEXP res ;
        try{
            SEXP asEnvironmentSym = Rf_install("as.environment"); 
            res =  Evaluator::run( Rf_lang2( asEnvironmentSym, Rf_ScalarInteger(pos) ) ) ;
        } catch( const eval_error& ex){
            throw no_such_env(pos) ;
        }
        set__( res ) ;
    }
    
    SEXP Environment::ls( bool all = true) const {
        if( is_user_database() ){
            R_ObjectTable *tb = (R_ObjectTable*)
                R_ExternalPtrAddr(HASHTAB(get__()));
            return tb->objects(tb) ;
        } else{
            Rboolean get_all = all ? TRUE : FALSE ;
            return R_lsInternal( get__(), get_all ) ;
        }
        return R_NilValue ;
    }
    
    SEXP Environment::get( const std::string& name) const {
        SEXP nameSym = Rf_install(name.c_str());        
        SEXP res = Rf_findVarInFrame( get__(), nameSym ) ;
        
        if( res == R_UnboundValue ) return R_NilValue ;
        
        /* We need to evaluate if it is a promise */
        if( TYPEOF(res) == PROMSXP){
            res = Rf_eval( res, get__() ) ;
        }
        return res ;
    }
    
    SEXP Environment::find( const std::string& name) const {
        SEXP nameSym = Rf_install(name.c_str());        
        SEXP res = Rf_findVar( nameSym, get__() ) ;
        
        if( res == R_UnboundValue ) throw binding_not_found(name) ;
        
        /* We need to evaluate if it is a promise */
        if( TYPEOF(res) == PROMSXP){
            res = Rf_eval( res, get__() ) ;
        }
        return res ;
    }
    
    bool Environment::exists( const std::string& name) const{
        SEXP nameSym = Rf_install(name.c_str());        
        SEXP res = Rf_findVarInFrame( get__(), nameSym  ) ;
        return res != R_UnboundValue ;
    }
    
    bool Environment::assign( const std::string& name, SEXP x = R_NilValue) const {
        if( exists( name) && bindingIsLocked(name) ) throw binding_is_locked(name) ;
        SEXP nameSym = Rf_install(name.c_str());        
        Rf_defineVar( nameSym, x, get__() );
        return true ;
    }
    
    bool Environment::remove( const std::string& name) {
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
                    Rf_lang4(removeSym, Rf_mkString(name.c_str()), get__(), Rf_ScalarLogical( FALSE )) 
                 );
                Rf_eval( call, R_GlobalEnv ) ;
            }
        } else{
            throw no_such_binding(name) ;
        }
        return true;
    }
    
    bool Environment::isLocked() const{
        return R_EnvironmentIsLocked(get__());
    }
    
    bool Environment::bindingIsActive(const std::string& name) const {
        if( !exists( name) ) throw no_such_binding(name) ;
        SEXP nameSym = Rf_install(name.c_str());        
        return R_BindingIsActive(nameSym, get__()) ;
    }
    
    bool Environment::bindingIsLocked(const std::string& name) const {
        if( !exists( name) ) throw no_such_binding(name) ;
        SEXP nameSym = Rf_install(name.c_str());        
        return R_BindingIsLocked(nameSym, get__()) ;
    }
    
    void Environment::lock( bool bindings = false ) {
        R_LockEnvironment( get__(), bindings ? TRUE: FALSE ) ;
    }
    
    void Environment::lockBinding(const std::string& name) {
        if( !exists( name) ) throw no_such_binding(name) ;
        SEXP nameSym = Rf_install(name.c_str());        
        R_LockBinding( nameSym, get__() ); 
    }
    
    void Environment::unlockBinding(const std::string& name) {
        if( !exists( name) ) throw no_such_binding(name) ;
        SEXP nameSym = Rf_install(name.c_str());        
        R_unLockBinding( nameSym, get__() );
    }
    
    bool Environment::is_user_database() const {
        return OBJECT(get__()) && Rf_inherits(get__(), "UserDefinedDatabase") ;
    }
    
    /* static */
    
    Environment Environment::global_env() {
        return Environment(R_GlobalEnv) ;
    }
    
    Environment Environment::empty_env() {
        return Environment(R_EmptyEnv) ;
    }
    
    Environment Environment::base_env() {
        return Environment(R_BaseEnv) ;
    }
    
    Environment Environment::base_namespace() {
        return Environment(R_BaseNamespace) ;
    }
    
    Environment Environment::namespace_env(const std::string& package) {
        
        SEXP env = R_NilValue ;
        try{
            SEXP getNamespaceSym = Rf_install("getNamespace");
            env = Evaluator::run( Rf_lang2(getNamespaceSym, Rf_mkString(package.c_str()) ) ) ;
        } catch( const eval_error& ex){
            throw no_such_namespace( package  ) ; 
        }
        return Environment( env ) ;
    }
    
    Environment Environment::parent() const {
        return Environment( ENCLOS(get__()) ) ; 
    }
    
    Environment::Binding::Binding( Environment& env_, const std::string& name_): 
        env(env_), name(name_){}
    
    bool Environment::Binding::active() const{
        return env.bindingIsActive( name ) ; 
    }
    
    bool Environment::Binding::exists() const{
        return env.exists( name ) ; 
    }
    
    bool Environment::Binding::locked() const{
        return env.bindingIsLocked( name ) ; 
    }
    
    void Environment::Binding::lock() {
        env.lockBinding( name ) ;
    }
    
    void Environment::Binding::unlock() {
        env.unlockBinding( name ) ;
    }
    
    Environment::Binding& Environment::Binding::operator=( SEXP rhs ){
        env.assign( name, rhs ) ;
        return *this ;
    }
    
    Environment::Binding& Environment::Binding::operator=( const Binding& rhs){
        env.assign( name, rhs.env.get(rhs.name) ) ;
        return *this ;
    }

    const Environment::Binding Environment::operator[]( const std::string& name) const{
        return Binding( const_cast<Environment&>(*this), name );
    }
    
    Environment::Binding Environment::operator[]( const std::string& name) {
        return Binding( *this, name ) ;
    }
    
    Environment Environment::Rcpp11_namespace() {
        return Rcpp::internal::get_Rcpp11_namespace() ;
    }
    
    Environment Environment::new_child(bool hashed) {
        SEXP newEnvSym = Rf_install("new.env");
        return Environment( Evaluator::run(Rf_lang3( newEnvSym, Rf_ScalarLogical(hashed), get__() )) );
    }
    // }}}    
    
    // {{{ DataFrame
    namespace internal{
        inline SEXP empty_data_frame(){
            SEXP dataFrameSym = ::Rf_install( "data.frame"); // cannot be gc()ed once in symbol table
            return ::Rf_eval( ::Rf_lang1( dataFrameSym ), R_GlobalEnv ) ;       
        }
    }
             
    DataFrame::DataFrame(): List( internal::empty_data_frame() ){}
    DataFrame::DataFrame(SEXP x) {
        set_sexp(x) ;
    }  
    DataFrame::DataFrame( const DataFrame& other): List(other.get__()) {}
    
    DataFrame& DataFrame::operator=( DataFrame& other) {
        set__( other.get__() ) ;
        return *this ;
    }
            
    DataFrame& DataFrame::operator=( SEXP x) {
        set__(x) ;
        return *this ;
    }
    DataFrame::~DataFrame(){}     
    void DataFrame::set_sexp(SEXP x) {
        if( ::Rf_inherits( x, "data.frame" )){
            set__( x ) ;
        } else{
            SEXP y = internal::convert_using_rfunction( x, "as.data.frame" ) ;
            set__( y ) ;
            x = y ;
        }
    } 
    int DataFrame::nrows() const { return Rf_length( VECTOR_ELT(get__(), 0) ); }
        
    DataFrame DataFrame::from_list( Rcpp::List obj ){
        bool use_default_strings_as_factors = true ;
        bool strings_as_factors = true ;
        int strings_as_factors_index = -1 ;
        int n = obj.size() ;
        CharacterVector names = obj.attr( "names" ) ;
        if( !names.isNULL() ){
            for( int i=0; i<n; i++){
                if( names[i] == "stringsAsFactors" ){
                    strings_as_factors_index = i ;
                    use_default_strings_as_factors = false ;        
                    if( !as<bool>(obj[i]) ) strings_as_factors = false ;
                    break ;         
                }
            }
        }
        if( use_default_strings_as_factors ) 
            return DataFrame(obj) ;
        SEXP as_df_symb = Rf_install("as.data.frame");
        SEXP strings_as_factors_symb = Rf_install("stringsAsFactors");
        
        obj.erase(strings_as_factors_index) ;
        names.erase(strings_as_factors_index) ;
        obj.attr( "names") = names ;
        Scoped<SEXP> call  = Rf_lang3(as_df_symb, obj, wrap( strings_as_factors ) ) ;
        SET_TAG( CDDR(call),  strings_as_factors_symb ) ;   
        Scoped<SEXP> res = Evaluator::run( call ) ; 
        DataFrame out( res ) ;
        return out ;
    }
    
    // }}}
    
} // namespace Rcpp
// }}}

// {{{ Rcomplex support
Rcomplex operator*( const Rcomplex& lhs, const Rcomplex& rhs){          
    Rcomplex y ;
    y.r = lhs.r * rhs.r - lhs.i * rhs.i ;
    y.i = lhs.r * rhs.i + rhs.r * lhs.i ;
    return y ;
}
Rcomplex operator+( const Rcomplex& lhs, const Rcomplex& rhs){
    Rcomplex y ;
    y.r = lhs.r + rhs.r ;
    y.i = lhs.i + rhs.i ;
    return y ;
}

Rcomplex operator-( const Rcomplex& lhs, const Rcomplex& rhs){
    Rcomplex y ;
    y.r = lhs.r - rhs.r ;
    y.i = lhs.i - rhs.i ;
    return y ;
}
   
Rcomplex operator/( const Rcomplex& a, const Rcomplex& b){

	Rcomplex c ;
    double ratio, den;
    double abr, abi;

    if( (abr = b.r) < 0)
	abr = - abr;
    if( (abi = b.i) < 0)
	abi = - abi;
    if( abr <= abi ) {
	ratio = b.r / b.i ;
	den = b.i * (1 + ratio*ratio);
	c.r = (a.r*ratio + a.i) / den;
	c.i = (a.i*ratio - a.r) / den;
    }
    else {
	ratio = b.i / b.r ;
	den = b.r * (1 + ratio*ratio);
	c.r = (a.r + a.i*ratio) / den;
	c.i = (a.i - a.r*ratio) / den;
    }
    return c ;
}
bool operator==( const Rcomplex& a, const Rcomplex& b){
    return a.r == b.r && a.i == b.i ;    
}
// }}}

// {{{ demangling
#include <cxxabi.h>

std::string demangle( const std::string& name ){
    std::string real_class ;
    int status =-1 ;
    char *dem = 0;
    dem = abi::__cxa_demangle(name.c_str(), 0, 0, &status);
    if( status == 0 ){
        real_class = dem ;
        free(dem);
    } else {
        real_class = name ;
    }
    return real_class ;
}
// }}}

// {{{ utilities
SEXP rcpp_capabilities(){
	Rcpp::Scoped<SEXP> cap   = Rf_allocVector( LGLSXP, 8) ;
	Rcpp::Scoped<SEXP> names = Rf_allocVector( STRSXP, 8 ) ;

    LOGICAL(cap)[0] = TRUE ;
    LOGICAL(cap)[1] = TRUE ;
    LOGICAL(cap)[2] = TRUE ;
    LOGICAL(cap)[3] = TRUE ;
    LOGICAL(cap)[4] = TRUE ;
    LOGICAL(cap)[5] = TRUE ;
    LOGICAL(cap)[6] = TRUE ;
    LOGICAL(cap)[7] = TRUE ;

	SET_STRING_ELT(names, 0, Rf_mkChar("variadic templates") ) ;
	SET_STRING_ELT(names, 1, Rf_mkChar("initializer lists") ) ;
	SET_STRING_ELT(names, 2, Rf_mkChar("exception handling") ) ;
	SET_STRING_ELT(names, 3, Rf_mkChar("tr1 unordered maps") ) ;
	SET_STRING_ELT(names, 4, Rf_mkChar("tr1 unordered sets") ) ;
	SET_STRING_ELT(names, 5, Rf_mkChar("Rcpp modules") ) ;
	SET_STRING_ELT(names, 6, Rf_mkChar("demangling") ) ;
	SET_STRING_ELT(names, 7, Rf_mkChar("long long") ) ;
	Rf_setAttrib( cap, R_NamesSymbol, names ) ;
	return cap ;
}

const char * sexp_to_name(int sexp_type) {
    switch (sexp_type) {
    case NILSXP:	return "NILSXP";
    case SYMSXP:	return "SYMSXP";
    case RAWSXP:	return "RAWSXP";
    case LISTSXP:	return "LISTSXP";
    case CLOSXP:	return "CLOSXP";
    case ENVSXP:	return "ENVSXP";
    case PROMSXP:	return "PROMSXP";
    case LANGSXP:	return "LANGSXP";
    case SPECIALSXP:	return "SPECIALSXP";
    case BUILTINSXP:	return "BUILTINSXP";
    case CHARSXP:	return "CHARSXP";
    case LGLSXP:	return "LGLSXP";
    case INTSXP:	return "INTSXP";
    case REALSXP:	return "REALSXP";
    case CPLXSXP:	return "CPLXSXP";
    case STRSXP:	return "STRSXP";
    case DOTSXP:	return "DOTSXP";
    case ANYSXP:	return "ANYSXP";
    case VECSXP:	return "VECSXP";
    case EXPRSXP:	return "EXPRSXP";
    case BCODESXP:	return "BCODESXP";
    case EXTPTRSXP:	return "EXTPTRSXP";
    case WEAKREFSXP:	return "WEAKREFSXP";
    case S4SXP:		return "S4SXP";
    default:
	return "<unknown>";
    }
}

namespace Rcpp{
namespace internal{

	template<> int* r_vector_start<INTSXP>(SEXP x){ 
	    RCPP_DEBUG( "r_vector_start<INTSXP>( SEXP = %p )", x )
	    return INTEGER(x) ; 
	}
	template<> int* r_vector_start<LGLSXP>(SEXP x){ 
	    RCPP_DEBUG( "r_vector_start<LGLSXP>( SEXP = %p )", x )
	    return LOGICAL(x) ;
	}
	template<> double* r_vector_start<REALSXP>(SEXP x){ 
	    RCPP_DEBUG( "r_vector_start<REALSXP>( SEXP = %p )", x )
	    return REAL(x) ;
	}
	template<> Rbyte* r_vector_start<RAWSXP>(SEXP x){ 
	    RCPP_DEBUG( "r_vector_start<RAWSXP>( SEXP = %p )", x )
	    return RAW(x) ;
	}
	template<> Rcomplex* r_vector_start<CPLXSXP>(SEXP x){ 
	    RCPP_DEBUG( "r_vector_start<CPLXSXP>( SEXP = %p )", x )
	    return COMPLEX(x) ;
	}
	
	template<> void r_init_vector<VECSXP>(SEXP x){}
	template<> void r_init_vector<EXPRSXP>(SEXP x){}
	template<> void r_init_vector<STRSXP>(SEXP x){}

	template<> Rcomplex get_zero<CPLXSXP,Rcomplex>(){
		Rcomplex x ;
		x.r = 0.0 ;
		x.i = 0.0 ;
		return x ;
	}

	template<> Rcomplex caster<std::complex<double>, Rcomplex>( std::complex<double> from){
		Rcomplex cx ;
		cx.r = from.real() ; 
		cx.i = from.imag() ;
		return cx ;
	}
	template<> Rcomplex caster<std::complex<float>, Rcomplex>( std::complex<float> from){
		Rcomplex cx ;
		cx.r = static_cast<double>( from.real() ); 
		cx.i = static_cast<double>( from.imag() );
		return cx ;
	}

	template<> std::complex<double> caster<Rcomplex,std::complex<double> >( Rcomplex from){
		return std::complex<double>(from.r, from.i ) ;
	}
	template<> std::complex<float> caster<Rcomplex,std::complex<float> >( Rcomplex from){
		return std::complex<float>(static_cast<float>(from.r), static_cast<float>(from.i) ) ;
	}
	template<> SEXP caster<String,SEXP>( String from){
		return from.get_sexp() ;
	}
	

	SEXP convert_using_rfunction(SEXP x, const char* const fun) {
        SEXP res = R_NilValue ;
        try{
            SEXP funSym = Rf_install(fun);
            res = Evaluator::run( Rf_lang2( funSym, x ) ) ;
        } catch( eval_error& e){
            throw ::Rcpp::not_compatible( std::string("could not convert using R function : ") + fun  ) ;
        }
        return res;
    }
    
    SEXP try_catch( SEXP expr, SEXP env ) {
        RCPP_DEBUG( "try_catch( expr = <%p>, env = <%p> )", expr, env )
        return Evaluator::run(expr, env) ;
    }
    SEXP try_catch( SEXP expr ) {
        RCPP_DEBUG( "try_catch( expr = <%p> )", expr )
        return Evaluator::run(expr) ;
    }
    
    SEXP eval_methods<EXPRSXP>::eval(){
        SEXP xp = ( static_cast<ExpressionVector&>(*this) ).get__() ;
        SEXP evalSym = Rf_install( "eval" );
        return try_catch( Rf_lang2( evalSym, xp ) ) ;
    }
    
    SEXP eval_methods<EXPRSXP>::eval( SEXP env ){
        SEXP xp = ( static_cast<ExpressionVector&>(*this) ).get__() ;
        SEXP evalSym = Rf_install( "eval" );
        return try_catch( Rf_lang3( evalSym, xp, env ) ) ;
    }
	
} // internal
} // Rcpp

SEXP as_character_externalptr(SEXP xp){
	char buffer[20] ;
	snprintf( buffer, 20, "%p", (void*)EXTPTR_PTR(xp) ) ;
	return Rcpp::wrap( (const char*)buffer ) ;
}

SEXP exception_to_try_error( const std::exception& ex ){
    return string_to_try_error(ex.what());
}

SEXP string_to_try_error( const std::string& str){

    using namespace Rcpp;
	
    // form simple error condition based on a string
    Scoped<SEXP> simpleErrorExpr = ::Rf_lang2(::Rf_install("simpleError"), Rf_mkString(str.c_str()));
    Scoped<SEXP> simpleError = Rf_eval(simpleErrorExpr, R_GlobalEnv);
	
    Scoped<SEXP> tryError = Rf_mkString( str.c_str() ) ;
    Rf_setAttrib( tryError, R_ClassSymbol, Rf_mkString("try-error") ) ; 
    Rf_setAttrib( tryError, Rf_install( "condition") , simpleError ) ; 
    return tryError;
}

const char* short_file_name(const char* file){
    std::string f(file) ;
    return f.substr( f.find_last_of("/") + 1 ).c_str() ;
}

#if defined(__GNUC__)
#if defined(WIN32) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__CYGWIN__) || defined(__sun)
// Simpler version for Windows and *BSD 
SEXP stack_trace( const char* file, int line ){
    Rcpp::List trace = Rcpp::List::create( 
    	Rcpp::Named( "file"  ) = file, 
    	Rcpp::Named( "line"  ) = line, 
    	Rcpp::Named( "stack" ) = "C++ stack not available on this system" ) ;
    trace.attr("class") = "Rcpp_stack_trace" ;
    return trace ;
}
#else // ! (defined(WIN32) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__CYGWIN__) || defined(__sun)
#include <execinfo.h>
#include <cxxabi.h>

static std::string demangler_one( const char* input){
    static std::string buffer ;
    buffer = input ;
    buffer.resize( buffer.find_last_of( '+' ) - 1 ) ;
    buffer.erase(
        buffer.begin(), 
        buffer.begin() + buffer.find_last_of( ' ' ) + 1
    ) ;
    return demangle( buffer) ;
}

/* inspired from http://tombarta.wordpress.com/2008/08/01/c-stack-traces-with-gcc/  */ 
SEXP stack_trace( const char *file, int line) {
    const size_t max_depth = 100;
    size_t stack_depth;
    void *stack_addrs[max_depth];
    char **stack_strings;

    stack_depth = backtrace(stack_addrs, max_depth);
    stack_strings = backtrace_symbols(stack_addrs, stack_depth);

    std::string current_line ;
    
    Rcpp::CharacterVector res( stack_depth - 1) ;
    std::transform( 
    	   stack_strings + 1, stack_strings + stack_depth, 
    	   res.begin(), 
    	   demangler_one 
    	) ;
    free(stack_strings); // malloc()ed by backtrace_symbols
    
    Rcpp::List trace = Rcpp::List::create( 
    	Rcpp::Named( "file"  ) = file, 
    	Rcpp::Named( "line"  ) = line, 
    	Rcpp::Named( "stack" ) = res ) ;
    trace.attr("class") = "Rcpp_stack_trace" ;
    return trace ;
}
#endif 
#else /* !defined( __GNUC__ ) */
SEXP stack_trace( const char *file, int line) {
	return R_NilValue ;
}
#endif   
// }}}

// {{{ coercion

namespace Rcpp{ 
namespace internal{

template <> int r_coerce<INTSXP,INTSXP>(int from) { return from ; }
template <> int r_coerce<LGLSXP,LGLSXP>(int from) { return from ; }
template <> double r_coerce<REALSXP,REALSXP>(double from) { return from ; }
template <> Rcomplex r_coerce<CPLXSXP,CPLXSXP>(Rcomplex from) { return from ; }
template <> Rbyte r_coerce<RAWSXP,RAWSXP>(Rbyte from) { return from ; }

// -> INTSXP
template <> int r_coerce<LGLSXP,INTSXP>(int from){
	return (from==NA_LOGICAL) ? NA_INTEGER : from ;
}
template <> int r_coerce<REALSXP,INTSXP>(double from){
	if (ISNAN(from)) return NA_INTEGER;
	else if (from > INT_MAX || from <= INT_MIN ) {
		return NA_INTEGER;
	}
	return static_cast<int>(from);

}
template <> int r_coerce<CPLXSXP,INTSXP>(Rcomplex from){
	return r_coerce<REALSXP,INTSXP>(from.r) ;
}
template <> int r_coerce<RAWSXP,INTSXP>(Rbyte from){
	return static_cast<int>(from);
}

// -> REALSXP
template <> double r_coerce<LGLSXP,REALSXP>(int from){
	return from == NA_LOGICAL ? NA_REAL : static_cast<double>(from) ;
}
template <> double r_coerce<INTSXP,REALSXP>(int from){
	return from == NA_INTEGER ? NA_REAL : static_cast<double>(from) ; 
}
template <> double r_coerce<CPLXSXP,REALSXP>(Rcomplex from){
	return from.r ;
}
template <> double r_coerce<RAWSXP,REALSXP>(Rbyte from){
	return static_cast<double>(from) ;
}

// -> LGLSXP
template <> int r_coerce<REALSXP,LGLSXP>(double from){
	return ( from == NA_REAL ) ? NA_LOGICAL : (from!=0.0);
}
template <> int r_coerce<INTSXP,LGLSXP>(int from){
	return ( from == NA_INTEGER ) ? NA_LOGICAL : (from!=0);
}
template <> int r_coerce<CPLXSXP,LGLSXP>(Rcomplex from){
	if( from.r == NA_REAL ) return NA_LOGICAL ;
	if( from.r == 0.0 || from.i == 0.0 ) return FALSE ;
	return TRUE ;
}
template <> int r_coerce<RAWSXP,LGLSXP>(Rbyte from){
	if( from != static_cast<Rbyte>(0) ) return TRUE ;
	return FALSE ;
}

// -> RAWSXP
template <> Rbyte r_coerce<REALSXP,RAWSXP>(double from){
	if( from == NA_REAL) return static_cast<Rbyte>(0) ; 
	return r_coerce<INTSXP,RAWSXP>(static_cast<int>(from)) ;
}
template <> Rbyte r_coerce<INTSXP,RAWSXP>(int from){
	return (from < 0 || from > 255) ? static_cast<Rbyte>(0) : static_cast<Rbyte>(from) ;
}
template <> Rbyte r_coerce<CPLXSXP,RAWSXP>(Rcomplex from){
	return r_coerce<REALSXP,RAWSXP>(from.r) ;
}
template <> Rbyte r_coerce<LGLSXP,RAWSXP>(int from){
	return static_cast<Rbyte>(from == TRUE) ;
}

// -> CPLXSXP
template <> Rcomplex r_coerce<REALSXP,CPLXSXP>(double from){
	Rcomplex c ;
	if( from == NA_REAL ){
		c.r = NA_REAL; 
		c.i = NA_REAL;
	} else{
		c.r = from ;
		c.i = 0.0 ;
	}
	return c ;
}
template <> Rcomplex r_coerce<INTSXP,CPLXSXP>(int from){
	Rcomplex c ;
	if( from == NA_INTEGER ){
		c.r = NA_REAL; 
		c.i = NA_REAL;
	} else{
		c.r = static_cast<double>(from) ;
		c.i = 0.0 ;
	}
	return c ;
}
template <> Rcomplex r_coerce<RAWSXP,CPLXSXP>(Rbyte from){
	Rcomplex c ;
	c.r = static_cast<double>(from);
	c.i = 0.0 ;
	return c ;
}
template <> Rcomplex r_coerce<LGLSXP,CPLXSXP>(int from){
	Rcomplex c ;
	if( from == TRUE ){
		c.r = 1.0 ; c.i = 0.0 ;
	} else if( from == FALSE ){
		c.r = c.i = 0.0 ;
	} else { /* NA */
		c.r = c.i = NA_REAL;
	}
	return c ;
}

inline int integer_width( int n ){
    return n < 0 ? ( (int) ( ::log10( -n+0.5) + 2 ) ) : ( (int) ( ::log10( n+0.5) + 1 ) ) ;    
}

#define NB 1000
template <> const char* coerce_to_string<INTSXP>(int from){
    static char buffer[NB] ;
    snprintf( buffer, NB, "%*d", integer_width(from), from );
    return buffer ;
}
template <> const char* coerce_to_string<LGLSXP>(int from){
    return from == 0 ? "FALSE" : "TRUE" ;    
}
template <> const char* coerce_to_string<RAWSXP>(Rbyte from){
    static char buff[3];
    snprintf(buff, 3, "%02x", from);
    return buff ;    
}

char* get_string_buffer(){
    static char buffer[MAXELTSIZE];
    return buffer ;    
}

static const char* dropTrailing0(char *s, char cdec) {
    /* Note that  's'  is modified */
    char *p = s;
    for (p = s; *p; p++) {
	if(*p == cdec) {
	    char *replace = p++;
	    while ('0' <= *p  &&  *p <= '9')
		if(*(p++) != '0')
		    replace = p;
	    if(replace != p)
		while((*(replace++) = *(p++)))
		    ;
	    break;
	}
    }
    return s;
}

template <> const char* coerce_to_string<REALSXP>(double x){
    //int w,d,e ;
    // cf src/main/format.c in R's sources:
    //   The return values are
    //     w : the required field width
    //     d : use %w.df in fixed format, %#w.de in scientific format
    //     e : use scientific format if != 0, value is number of exp digits - 1
    //
    //   nsmall specifies the minimum number of decimal digits in fixed format:
    //   it is 0 except when called from do_format.
    //Rf_formatReal( &x, 1, &w, &d, &e, 0 ) ;
    // we are no longer allowed to use this:
    //     char* tmp = const_cast<char*>( Rf_EncodeReal(x, w, d, e, '.') );
    // so approximate it poorly as
    static char tmp[128];
    snprintf(tmp, 127, "%f", x); 
    return dropTrailing0(tmp, '.');
}

template <> const char* coerce_to_string<CPLXSXP>(Rcomplex x){
    //int wr, dr, er, wi, di, ei;
    //Rf_formatComplex(&x, 1, &wr, &dr, &er, &wi, &di, &ei, 0);
    // we are no longer allowed to use this:
    //     Rf_EncodeComplex(x, wr, dr, er, wi, di, ei, '.' );
    // so approximate it poorly as
    static char tmp1[128], tmp2[128], tmp3[256];
    //snprintf(tmp, 127, "%*.*f+%*.*fi", wr, dr, x.r, wi, di, x.i);
    //snprintf(tmp, 127, "%f+%fi", x.r, x.i); // FIXEM: barebones default formatting
    snprintf(tmp1, 127, "%f", x.r); 
    snprintf(tmp2, 127, "%f", x.i); 
    snprintf(tmp3, 255, "%s+%si", dropTrailing0(tmp1, '.'), dropTrailing0(tmp2, '.'));
    return tmp3;
}

} // internal
} // Rcpp

// }}}

// {{{ r_cast support
namespace Rcpp{
    namespace internal{
        
        template<> SEXP r_true_cast<INTSXP>(SEXP x) {
            switch( TYPEOF(x) ){
            case REALSXP:
            case RAWSXP:
            case LGLSXP:
            case CPLXSXP:
                return Rf_coerceVector( x, INTSXP) ;
            default:
                throw ::Rcpp::not_compatible( "not compatible with INTSXP" ) ;
            }
            return R_NilValue ; /* -Wall */
        }

        template<> SEXP r_true_cast<REALSXP>( SEXP x) {
            switch( TYPEOF( x ) ){
            case INTSXP:
            case LGLSXP:
            case CPLXSXP:
            case RAWSXP:
                return Rf_coerceVector( x, REALSXP );
            default:
                throw ::Rcpp::not_compatible( "not compatible with REALSXP" ) ;
            }
            return R_NilValue ; /* -Wall */
        }

        template<> SEXP r_true_cast<LGLSXP>( SEXP x) {
            switch( TYPEOF( x ) ){
            case REALSXP:
            case INTSXP:
            case CPLXSXP:
            case RAWSXP:
                return Rf_coerceVector( x, LGLSXP );
            default:
                throw ::Rcpp::not_compatible( "not compatible with LGLSXP" ) ;
            }
            return R_NilValue ; /* -Wall */
        }

        template<> SEXP r_true_cast<RAWSXP>( SEXP x) {
            switch( TYPEOF( x ) ){
            case LGLSXP:
            case REALSXP:
            case INTSXP:
            case CPLXSXP:
                return Rf_coerceVector( x, RAWSXP );
            default:
                throw ::Rcpp::not_compatible( "not compatible with RAWSXP" ) ;
            }
            return R_NilValue ; /* -Wall */
        }


        template<> SEXP r_true_cast<CPLXSXP>( SEXP x) {
            switch( TYPEOF( x ) ){
            case RAWSXP:
            case LGLSXP:
            case REALSXP:
            case INTSXP:
                return Rf_coerceVector( x, CPLXSXP );
            default:
                throw ::Rcpp::not_compatible( "not compatible with CPLXSXP" ) ;
            }
            return R_NilValue ; /* -Wall */
        }

        template<> SEXP r_true_cast<STRSXP>( SEXP x) {
            switch( TYPEOF( x ) ){
            case CPLXSXP:
            case RAWSXP:
            case LGLSXP:
            case REALSXP:
            case INTSXP:
                {
                    // return Rf_coerceVector( x, STRSXP );
                    // coerceVector does not work for some reason
                    Scoped<SEXP> call = Rf_lang2( Rf_install( "as.character" ), x ) ;
                    Scoped<SEXP> res  = Rf_eval( call, R_GlobalEnv ) ;
                    return res ;
                }
            case CHARSXP:
                return Rf_ScalarString( x ) ;
            case SYMSXP:
                return Rf_ScalarString( PRINTNAME( x ) ) ; 
            default:
                throw ::Rcpp::not_compatible( "not compatible with STRSXP" ) ;
            }
            return R_NilValue ; /* -Wall */
        }

        template<> SEXP r_true_cast<VECSXP>(SEXP x) {
            return convert_using_rfunction(x, "as.list" ) ;
        }
    
        template<> SEXP r_true_cast<EXPRSXP>(SEXP x) {
            return convert_using_rfunction(x, "as.expression" ) ;
        }

        template<> SEXP r_true_cast<LISTSXP>(SEXP x) {
            switch( TYPEOF(x) ){
            case LANGSXP:
                {
                    Scoped<SEXP> y = Rf_duplicate( x ); 
                    SET_TYPEOF(y,LISTSXP) ;
                    return y ;
                }
            default:
                return convert_using_rfunction(x, "as.pairlist" ) ;
            }
        
        }

        template<> SEXP r_true_cast<LANGSXP>(SEXP x) {
            return convert_using_rfunction(x, "as.call" ) ;
        }
    }
}
// }}}

