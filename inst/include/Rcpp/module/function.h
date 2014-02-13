#ifndef Rcpp_Module_function_h
#define Rcpp_Module_function_h

template <typename OUT, typename... Args>                                                                   
void function( const char* name_,  OUT (*fun)(Args...), const char* docstring = 0){
    Rcpp::Module* scope = Module::getCurrent();
    if( scope ){
        scope->Add( name_, new CppFunction_Impl<OUT, Args...>( fun, docstring ) ) ;
    }
}

template <typename OUT, typename... Args>                                                                   
void function( const char* name_,  OUT (*fun)(Args...), Rcpp::List formals, const char* docstring = 0){
    Rcpp::Module* scope = Module::getCurrent();
    if( scope ){
        scope->Add( name_, new CppFunction_WithFormals_Impl<OUT, Args...>( fun, formals, docstring ) ) ;
    }
}

template <typename OUT, typename... Args>                                                                   
void debug_function( const char* name_,  OUT (*fun)(Args...), const char* docstring = 0){
    Rcpp::Module* scope = Module::getCurrent();
    if( scope ){
        scope->Add( name_, new Debug_CppFunction_Impl<OUT, Args...>( fun, name_, docstring ) ) ;
    }
}

template <typename OUT, typename... Args>                                                                   
void debug_function( const char* name_,  OUT (*fun)(Args...), Rcpp::List formals, const char* docstring = 0){
    Rcpp::Module* scope = Module::getCurrent();
    if( scope ){
        scope->Add( name_, new Debug_CppFunction_WithFormals_Impl<OUT, Args...>( fun, name_, formals, docstring ) ) ;
    }
}


#endif
