#ifndef Rcpp_Module_property_invoke_h
#define Rcpp_Module_property_invoke_h

template <typename Class, typename GetterType>
inline SEXP property_invoke_getter__impl( GetterType& getter, Class* object, std::true_type){
    return wrap( (object->*getter)() ) ;
}

template <typename Class, typename GetterType>
inline SEXP property_invoke_getter__is_member_object( GetterType& getter, Class* object, std::false_type){
    return wrap( (*getter)(object) ) ;
}
template <typename Class, typename GetterType>
inline SEXP property_invoke_getter__is_member_object( GetterType& getter, Class* object, std::true_type){
    return wrap( object->*getter ) ;
}

template <typename Class, typename GetterType>
inline SEXP property_invoke_getter__impl( GetterType& getter, Class* object, std::false_type){
    return property_invoke_getter__is_member_object<Class,GetterType>( getter, object, typename std::is_member_object_pointer<GetterType>::type() );
}

template <typename Class, typename PROP, typename GetterType>
inline SEXP property_invoke_getter( GetterType& getter, Class* object, std::string& /* prop_name */, std::false_type /* debug = false */ ){
    return property_invoke_getter__impl<Class,GetterType>( getter, object, typename std::is_member_function_pointer<GetterType>::type() );
}
template <typename Class, typename PROP, typename GetterType>
inline SEXP property_invoke_getter( GetterType& getter, Class* object, std::string& prop_name , std::true_type /* debug = false */ ){
    std::string log( "   " ) ;
    log += DEMANGLE(PROP) ;
    log += " " ;
    log += DEMANGLE(Class) ;
    log += "::" ;
    log += prop_name ;
    log += " getter" ; 
    Rprintf( "    %70s   [object = <%p>] ...", log.c_str(), object ) ;
    SEXP res = property_invoke_getter__impl<Class,GetterType>( getter, object, typename std::is_member_function_pointer<GetterType>::type() );
    Rprintf( "\n" );
    return res ;
}


template <typename Class, typename PROP, typename SetterType>
inline void property_invoke_setter__impl( SetterType& setter, Class* object, SEXP value, std::true_type){
    typename traits::input_parameter<PROP>::type x(value) ; 
    (object->*setter)(x) ;
}
template <typename Class, typename PROP, typename SetterType>
inline void property_invoke_setter__impl__is_member_object( SetterType& setter, Class* object, SEXP value, std::false_type){
    typename traits::input_parameter<PROP>::type x(value) ; 
    (*setter)(object, x) ;
}
template <typename Class, typename PROP, typename SetterType>
inline void property_invoke_setter__impl__is_member_object( SetterType& setter, Class* object, SEXP value, std::true_type){
    typename traits::input_parameter<PROP>::type x(value) ; 
    object->*setter = x ;
}

template <typename Class, typename PROP, typename SetterType>
inline void property_invoke_setter__impl__isnull( SetterType& setter, Class* object, SEXP value, std::false_type){
    property_invoke_setter__impl__is_member_object<Class,PROP,SetterType>( setter, object, value, typename std::is_member_object_pointer<SetterType>::type() );
}
template <typename Class, typename PROP, typename SetterType>
inline void property_invoke_setter__impl__isnull( SetterType& setter, Class* object, SEXP value, std::true_type){
    throw std::range_error("property is read only") ;
}
template <typename Class, typename PROP, typename SetterType>
inline void property_invoke_setter__impl( SetterType& setter, Class* object, SEXP value, std::false_type){
    property_invoke_setter__impl__isnull<Class,PROP,SetterType>( setter, object, value, typename std::is_same<SetterType, decltype(nullptr)>::type() ) ;
}

template <typename Class, typename PROP, typename SetterType>
inline void property_invoke_setter( SetterType& setter, Class* object, SEXP value, std::string& /* prop_name */, std::false_type /* debug = false */ ){
    property_invoke_setter__impl<Class,PROP,SetterType>( setter, object, value, typename std::is_member_function_pointer<SetterType>::type() );
}

template <typename Class, typename PROP, typename SetterType>
inline void property_invoke_setter( SetterType& setter, Class* object, SEXP value, std::string& prop_name, std::true_type /* debug = true */ ){
    std::string log( "   " ) ;
    log += DEMANGLE(PROP) ;
    log += " " ;
    log += DEMANGLE(Class) ;
    log += ":: " ;
    log += prop_name ;
    log += " setter" ; 
    Rprintf( "    %70s   [object = <%p>] ...", log.c_str(), object ) ;
    property_invoke_setter__impl<Class,PROP,SetterType>( setter, object, value, typename std::is_member_function_pointer<SetterType>::type() );
    Rprintf( "\n" ) ;
}


#endif
