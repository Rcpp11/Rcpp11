#ifndef Rcpp_Module_property_h
#define Rcpp_Module_property_h

    template <typename PROP>
    self& property( const char* name_, PROP (Class::*GetMethod)(void), const char* docstring = 0){
        if( is_debugging )
            return AddProperty( name_, new CppProperty_Read_Write<Class,PROP,decltype(GetMethod),std::nullptr_t,true>(GetMethod, nullptr, name_, docstring) ) ;
        else
            return AddProperty( name_, new CppProperty_Read_Write<Class,PROP,decltype(GetMethod),std::nullptr_t,false>(GetMethod, nullptr, name_, docstring) ) ;
    }               

    template <typename PROP>
    self& property( const char* name_, PROP (Class::*GetMethod)(void) const, const char* docstring = 0){
        if( is_debugging )
            return AddProperty( name_, new CppProperty_Read_Write<Class,PROP,decltype(GetMethod),std::nullptr_t,true>(GetMethod, nullptr, name_, docstring) ) ;
        else
            return AddProperty( name_, new CppProperty_Read_Write<Class,PROP,decltype(GetMethod),std::nullptr_t,false>(GetMethod, nullptr, name_, docstring) ) ;
    }
    
    template <typename PROP>
    self& property( const char* name_, PROP (*GetMethod)(Class*), const char* docstring = 0){
        if( is_debugging )
            return AddProperty( name_, new CppProperty_Read_Write<Class,PROP,decltype(GetMethod),std::nullptr_t,true>(GetMethod, nullptr, name_, docstring) ) ;
        else
            return AddProperty( name_, new CppProperty_Read_Write<Class,PROP,decltype(GetMethod),std::nullptr_t,false>(GetMethod, nullptr, name_, docstring) ) ;
    }
    
    
    template <typename PROP>
    self& property( const char* name_, PROP (Class::*GetMethod)(void), void (Class::*SetMethod)(PROP), const char* docstring = 0){
        if( is_debugging )
            return AddProperty( name_, new CppProperty_Read_Write<Class,PROP,decltype(GetMethod), decltype(SetMethod), true>(GetMethod, SetMethod, name_, docstring) );
        else 
            return AddProperty( name_, new CppProperty_Read_Write<Class,PROP,decltype(GetMethod), decltype(SetMethod), false>(GetMethod, SetMethod, name_, docstring) );
    }
    template <typename PROP>
    self& property( const char* name_, PROP (Class::*GetMethod)(void) const, void (Class::*SetMethod)(PROP), const char* docstring = 0){
        if( is_debugging )
            return AddProperty( name_, new CppProperty_Read_Write<Class,PROP,decltype(GetMethod), decltype(SetMethod), true>(GetMethod, SetMethod, name_, docstring) );
        else 
            return AddProperty( name_, new CppProperty_Read_Write<Class,PROP,decltype(GetMethod), decltype(SetMethod), false>(GetMethod, SetMethod, name_, docstring) );
    }
    
    template <typename PROP>
    self& property( const char* name_, PROP (Class::*GetMethod)(void), void (*SetMethod)(Class*,PROP), const char* docstring = 0 ){
        if( is_debugging )
            return AddProperty( name_, new CppProperty_Read_Write<Class,PROP,decltype(GetMethod), decltype(SetMethod), true>(GetMethod, SetMethod, name_, docstring) );
        else 
            return AddProperty( name_, new CppProperty_Read_Write<Class,PROP,decltype(GetMethod), decltype(SetMethod), false>(GetMethod, SetMethod, name_, docstring) );
    }
    template <typename PROP>
    self& property( const char* name_, PROP (Class::*GetMethod)(void) const , void (*SetMethod)(Class*,PROP), const char* docstring = 0 ){
        if( is_debugging )
            return AddProperty( name_, new CppProperty_Read_Write<Class,PROP,decltype(GetMethod), decltype(SetMethod), true>(GetMethod, SetMethod, name_, docstring) );
        else 
            return AddProperty( name_, new CppProperty_Read_Write<Class,PROP,decltype(GetMethod), decltype(SetMethod), false>(GetMethod, SetMethod, name_, docstring) );
    }
    
    
    template <typename PROP>
    self& property( const char* name_, PROP (*GetMethod)(Class*), void (Class::*SetMethod)(PROP), const char* docstring = 0 ){
        if( is_debugging )
            return AddProperty( name_, new CppProperty_Read_Write<Class,PROP,decltype(GetMethod), decltype(SetMethod), true>(GetMethod, SetMethod, name_, docstring) );
        else 
            return AddProperty( name_, new CppProperty_Read_Write<Class,PROP,decltype(GetMethod), decltype(SetMethod), false>(GetMethod, SetMethod, name_, docstring) );
    }
    
    template <typename PROP>
    self& property( const char* name_, PROP (*GetMethod)(Class*), void (*SetMethod)(Class*,PROP), const char* docstring = 0 ){
        if( is_debugging )
            return AddProperty( name_, new CppProperty_Read_Write<Class,PROP,decltype(GetMethod), decltype(SetMethod), true>(GetMethod, SetMethod, name_, docstring) );
        else 
            return AddProperty( name_, new CppProperty_Read_Write<Class,PROP,decltype(GetMethod), decltype(SetMethod), false>(GetMethod, SetMethod, name_, docstring) );
    }
	
    template <typename PROP>
    self& field( const char* name_, PROP Class::*ptr, const char* docstring = 0){
        if( is_debugging )
            return AddProperty( name_, new CppProperty_Read_Write<Class,PROP,decltype(ptr),decltype(ptr),true>(ptr, ptr, name_, docstring) ) ;
        else
            return AddProperty( name_, new CppProperty_Read_Write<Class,PROP,decltype(ptr),decltype(ptr),false>(ptr, ptr, name_, docstring) ) ;
    }
            
    template <typename PROP>
    self& field_readonly( const char* name_, PROP Class::*ptr, const char* docstring = 0 ){
        if( is_debugging )
            return AddProperty( name_, new CppProperty_Read_Write<Class,PROP,decltype(ptr),std::nullptr_t,true>(ptr, nullptr, name_, docstring) ) ;
        else
            return AddProperty( name_, new CppProperty_Read_Write<Class,PROP,decltype(ptr),std::nullptr_t,false>(ptr, nullptr, name_, docstring) ) ;
    }

	
#endif
