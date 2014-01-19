#ifndef Rcpp_Module_Constructor_h
#define Rcpp_Module_Constructor_h

template <typename Class>
class Constructor_Base {
public:
    virtual Class* get_new( SEXP*, int ) = 0 ;
    virtual int nargs() = 0 ;
    virtual void signature(std::string& s, const std::string& class_name) = 0 ;
} ;

template <typename Class, typename... Args>
class Constructor_Impl : public Constructor_Base<Class>{
public:
    virtual Class* get_new( SEXP* args, int /* nargs */ ){
        return ConstructorInvoker<Class, Args...>(args).invoke() ;
    }
    virtual int nargs(){ return sizeof...(Args) ; }
    virtual void signature(std::string& s, const std::string& class_name ){
        ctor_signature<Args...>(s, class_name) ;
    }
} ;

template <typename Class, typename... Args>
class Debug_Constructor_Impl : public Constructor_Base<Class>{
public:
    virtual Class* get_new( SEXP* args, int ){
        debug_constructor<Class,Debug_Constructor_Impl,Args...>(*this) ;  
        Class * obj = ConstructorInvoker<Class, Args...>(args).invoke() ;
        Rprintf( "  object = <%p>\n", obj ) ;
        return obj ;
    }
    virtual int nargs(){ return sizeof...(Args) ; }
    virtual void signature(std::string& s, const std::string& class_name ){
        ctor_signature<Args...>(s, class_name) ;
    }
} ;

#endif
