#ifndef Rcpp_Module_Factory_h
#define Rcpp_Module_Factory_h
   
template <typename Class>
class Factory_Base {
public:
    virtual Class* get_new( SEXP* args, int nargs ) = 0 ;
    virtual int nargs() = 0 ;
    virtual void signature(std::string& s, const std::string& class_name) = 0 ;
} ;

template <typename Class, typename... Args>
class Factory_Impl : public Factory_Base<Class>{
    public: 
        typedef Class* (*Fun)(Args...) ;  
        
        Factory_Impl( Fun fun_ ) : fun(fun_){}
        virtual Class* get_new( SEXP* args, int /* nargs */ ){
            return FactoryInvoker<Class,Args...>( fun, args).invoke() ;
        }
        virtual int nargs(){ return sizeof...(Args) ; }
        virtual void signature(std::string& s, const std::string& class_name ){
            ctor_signature<Args...>(s, class_name) ;
        }
    private:
        Fun fun ;
} ;        

template <typename Class, typename... Args>
class Debug_Factory_Impl : public Factory_Base<Class>{
    public: 
        typedef Class* (*Fun)(Args...) ;  
        
        Debug_Factory_Impl( Fun fun_ ) : fun(fun_){}
        virtual Class* get_new( SEXP* args, int /* nargs */ ){
            debug_constructor<Class,Debug_Factory_Impl,Args...>(*this) ;  
            Class *obj = FactoryInvoker<Class,Args...>( fun, args).invoke() ;
            Rprintf( "  object = <%p>\n", obj ) ;
            return obj ;
        }
        virtual int nargs(){ return sizeof...(Args) ; }
        virtual void signature(std::string& s, const std::string& class_name ){
            ctor_signature<Args...>(s, class_name) ;
        }
    private:
        Fun fun ;
} ;        

#endif
