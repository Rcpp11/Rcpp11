#ifndef Rcpp_Module_method_h
#define Rcpp_Module_method_h

    template <typename OUT, typename... Args>
    self& method( const char* name_, OUT (Class::*fun)(Args...), const char* docstring = 0, ValidMethod valid = &yes ){
        typedef OUT (Class::*MemberFunctionType)(Args...)  ;
        if( is_debugging )
            AddMethod( name_, new Debug_CppMethod_Impl<Class,MemberFunctionType, false,OUT,Args...>( fun, name_ ), valid, docstring) ;
        else 
            AddMethod( name_, new CppMethod_Impl<Class,MemberFunctionType, false,OUT,Args...>( fun ), valid, docstring) ;
        return *this ;
    }
    
    template <typename OUT, typename... Args>
    self& method( const char* name_, OUT (Class::*fun)(Args...) const, const char* docstring = 0, ValidMethod valid = &yes ){
        typedef OUT (Class::*MemberFunctionType)(Args...) const  ;
        if( is_debugging ) 
            AddMethod( name_, new Debug_CppMethod_Impl<Class,MemberFunctionType,true,OUT,Args...>( fun, name_ ), valid, docstring ) ;
        else
            AddMethod( name_, new CppMethod_Impl<Class,MemberFunctionType,true,OUT,Args...>(fun), valid, docstring ) ;
        return *this ;
    }
    
    template <typename OUT, typename... Args>
    self& nonconst_method( const char* name_, OUT (Class::*fun)(Args...), const char* docstring = 0, ValidMethod valid = &yes ){
        typedef OUT (Class::*MemberFunctionType)(Args...)  ;
        if(is_debugging)
            AddMethod( name_, new Debug_CppMethod_Impl<Class,MemberFunctionType,false,OUT,Args...>( fun, name_ ) , valid, docstring ) ;
        else 
            AddMethod( name_, new CppMethod_Impl<Class,MemberFunctionType,false,OUT,Args...>( fun ) , valid, docstring ) ;
        return *this ;
    }
    template <typename OUT, typename... Args>
    self& const_method( const char* name_, OUT (Class::*fun)(Args...) const, const char* docstring = 0, ValidMethod valid = &yes ){
        typedef OUT (Class::*MemberFunctionType)(Args...) const ;
        if( is_debugging )
            AddMethod( name_, new Debug_CppMethod_Impl<Class,MemberFunctionType,true,OUT,Args...>( fun, name_), valid, docstring ) ;
        else
            AddMethod( name_, new CppMethod_Impl<Class,MemberFunctionType,true,OUT,Args...>( fun ), valid, docstring ) ;    
        return *this ;
    }
	
    	template <typename OUT, typename... Args>
	self& method( const char* name_, OUT (*fun)(Class*, Args...), const char* docstring = 0, ValidMethod valid = &yes ){
        typedef OUT (*MemberFunctionType)(Class*, Args...) ;
        if( is_debugging )
            AddMethod( name_, new Debug_CppMethod_Impl<Class,MemberFunctionType,false,OUT,Args...>( fun, name_ ), valid, docstring ) ;    
        else 
            AddMethod( name_, new CppMethod_Impl<Class,MemberFunctionType,false,OUT,Args...>( fun ), valid, docstring ) ;
        return *this ;
	}

#endif
