#ifndef RCPP_ROUTINE_H
#define RCPP_ROUTINE_H

#if defined(COMPILING_RCPP11)

// the idea is that this file should be generated automatically
// by Rcpp::register

namespace Rcpp{
    SEXP Rcpp_eval(SEXP expr, SEXP env = R_GlobalEnv) ;
    const char* type2name(SEXP x) ;
    std::string demangle( const std::string& name) ;
    void forward_exception_to_r( const std::exception& ex ) ;
    SEXP exception_to_try_error( const std::exception& ex ) ;
    SEXP string_to_try_error( const std::string& str) ;
    SEXP stack_trace( const char *file, int line) ;
    unsigned long enterRNGScope(); 
    unsigned long exitRNGScope() ;
    SEXP get_Rcpp11_namespace() ; 
    int* get_cache( int n ) ;
}
           
SEXP rcpp_set_stack_trace(SEXP) ;
void set_vector_elt(SEXP v, int i, SEXP x); 
SEXP* get_vector_ptr(SEXP v); 
void* dataptr(SEXP x) ;
Rcpp::Module* getCurrentScope() ;
void setCurrentScope( Rcpp::Module* mod ) ;
SEXP rcpp_get_current_error() ;
int& reset_current_error() ;
int error_occured() ;
SEXP rcpp11_error_handler() ;

#else 

namespace Rcpp {
    
    inline int& reset_current_error(){
        GET_CALLABLE(reset_current_error) ;
        return fun();  
    }
    
    inline nanotime_t get_nanotime(void){
        GET_CALLABLE(get_nanotime) ;
        return fun() ; 
    }
    
    inline SEXP Rcpp_eval(SEXP expr, SEXP env = R_GlobalEnv){
        GET_CALLABLE(Rcpp_eval) ;
        return fun(expr, env) ;
    }
    
    inline const char* type2name(SEXP x){
        GET_CALLABLE(type2name) ;
        return fun(x) ;
    }
    
    inline std::string demangle( const std::string& name){
        GET_CALLABLE(demangle) ;
        return fun(name) ;
    }
    
    inline void forward_exception_to_r( const std::exception& ex ){
        GET_CALLABLE(forward_exception_to_r); 
        return fun(ex) ;
    }
    
    inline SEXP exception_to_try_error( const std::exception& ex ){
        GET_CALLABLE(exception_to_try_error);
        return fun(ex) ;
    }
    
    inline SEXP string_to_try_error( const std::string& str){
        GET_CALLABLE(string_to_try_error) ;
        return fun(str) ;
    }
    
    inline SEXP stack_trace( const char *file, int line){
        GET_CALLABLE(stack_trace) ;
        return fun(file, line) ;
    }
    
    inline unsigned long enterRNGScope(){
         GET_CALLABLE(enterRNGScope) ;
         return fun() ;
    }
    
    inline unsigned long exitRNGScope(){
         GET_CALLABLE(exitRNGScope) ;
         return fun() ;
    }
    
    inline SEXP get_Rcpp11_namespace() {
        GET_CALLABLE(get_Rcpp11_namespace) ;
        return fun();
    }
    
    inline int* get_cache( int n ){
        GET_CALLABLE(get_cache) ;
        return fun(n) ;    
    }
    
}
 
inline SEXP rcpp_get_current_error(){
    GET_CALLABLE(rcpp_get_current_error);
    return fun();
}

inline void set_vector_elt(SEXP v, int i, SEXP x){
    GET_CALLABLE(set_vector_elt) ;
    return fun(v, i, x) ;
}

inline SEXP* get_vector_ptr(SEXP v){
    GET_CALLABLE(get_vector_ptr) ;
    return fun(v) ;    
}

inline void* dataptr(SEXP x){
    GET_CALLABLE(dataptr) ;
    return fun(x) ; 
}

inline SEXP rcpp_set_stack_trace(SEXP x){
    GET_CALLABLE(rcpp_set_stack_trace) ;
    return fun(x) ;    
}

inline Rcpp::Module* getCurrentScope(){
    GET_CALLABLE(getCurrentScope) ;
    return fun();
}

inline void setCurrentScope( Rcpp::Module* mod ){
    GET_CALLABLE(setCurrentScope) ;
    return fun(mod) ;    
}

inline SEXP rcpp11_error_handler(){
    GET_CALLABLE(rcpp11_error_handler); 
    return fun(); 
}
  
inline int error_occured(){
    GET_CALLABLE(error_occured); 
    return fun(); 
}


#endif

#endif
