#define COMPILING_RCPP11

#include <Rcpp.h>
#include "internal.h"

typedef Rcpp::XPtr<Rcpp::Module> XP_Module ; 
typedef Rcpp::XPtr<Rcpp::class_Base> XP_Class ; 
typedef Rcpp::XPtr<Rcpp::CppFunction> XP_Function ; 

RCPP_FUN_1(SEXP, as_character_externalptr, SEXP xp){
    char buffer[20] ;
    snprintf( buffer, 20, "%p", (void*)EXTPTR_PTR(xp) ) ;
    return Rcpp::wrap( (const char*)buffer ) ;
}
RCPP_FUN_1( bool, Class__has_default_constructor, XP_Class cl ){
    return cl->has_default_constructor() ;
}
RCPP_FUN_2( SEXP, Module__get_function, XP_Module module, std::string fun ){
    return module->get_function( fun ) ;
}
RCPP_FUN_2( bool, Class__has_method, XP_Class cl, std::string m){
	return cl->has_method(m) ;
}
RCPP_FUN_2( bool, Class__has_property, XP_Class cl, std::string m){
	return cl->has_property(m) ;
}
RCPP_FUN_1( std::string, Class__name, XP_Class cl){
	return cl->name ;
}
RCPP_FUN_2( bool, Module__has_function, XP_Module module, std::string met ){
	return module->has_function( met ) ;
}
RCPP_FUN_2( bool, Module__has_class, XP_Module module, std::string cl ){
	return module->has_class( cl ) ;
}
RCPP_FUN_2( Rcpp::CppClass, Module__get_class, XP_Module module, std::string cl ){
	return module->get_class( cl ) ;
}
RCPP_FUN_1( bool, CppObject__needs_init, SEXP xp ){
	return EXTPTR_PTR(xp) == 0 ;
}
RCPP_FUN_1( Rcpp::CharacterVector, CppClass__methods, XP_Class cl){
	return cl->method_names() ;
}
RCPP_FUN_1( Rcpp::CharacterVector, CppClass__properties, XP_Class cl){
	return cl->property_names() ;
}
RCPP_FUN_1( Rcpp::List, CppClass__property_classes, XP_Class cl){
	return cl->property_classes() ;
}

RCPP_FUN_1( Rcpp::IntegerVector, CppClass__methods_arity, XP_Class cl){
	return cl->methods_arity() ;
}
RCPP_FUN_1( Rcpp::LogicalVector, CppClass__methods_voidness, XP_Class cl){
	return cl->methods_voidness() ;
}

RCPP_FUN_2( bool, CppClass__property_is_readonly, XP_Class cl, std::string p){
	return cl->property_is_readonly(p) ;
}
RCPP_FUN_2( std::string, CppClass__property_class, XP_Class cl, std::string p){
	return cl->property_class(p) ;
}

RCPP_FUN_1( Rcpp::IntegerVector, Module__functions_arity, XP_Module module ){
	return module->	functions_arity() ;
}
RCPP_FUN_1( Rcpp::CharacterVector, Module__functions_names, XP_Module module ){
	return module->	functions_names() ;
}
RCPP_FUN_1( std::string, Module__name, XP_Module module ){
	return module->name;
}
RCPP_FUN_1( Rcpp::List, Module__classes_info, XP_Module module ){
	return module->classes_info() ;
}
RCPP_FUN_1( Rcpp::CharacterVector, Module__complete, XP_Module module ){
	return module->complete() ;
}
RCPP_FUN_1( Rcpp::CharacterVector, CppClass__complete, XP_Class cl){
	return cl->complete(); 
}
RCPP_FUN_3(SEXP, CppField__get, XP_Class cl, SEXP field_xp, SEXP obj){
	return cl->getProperty( field_xp, obj ) ;
}
RCPP_FUN_4(SEXP, CppField__set, XP_Class cl, SEXP field_xp, SEXP obj, SEXP value){
	cl->setProperty( field_xp, obj, value ) ;
	return R_NilValue ;
}
RCPP_FUN_2(SEXP, CppObject__finalize, XP_Class cl, SEXP obj){
	cl->run_finalizer( obj ) ;
	return R_NilValue ;
}

// .External functions
SEXP InternalFunction_invoke( SEXP args ){
BEGIN_RCPP
	SEXP p = CDR(args) ;
	XP_Function fun( CAR(p) ) ; p = CDR(p) ;
	UNPACK_EXTERNAL_ARGS(cargs,p)
	return fun->operator()( cargs ) ;
END_RCPP
}

SEXP Module__invoke( SEXP args){
BEGIN_RCPP
	SEXP p = CDR(args) ;
	XP_Module module( CAR(p) ) ; p = CDR(p) ;
	std::string fun = Rcpp::as<std::string>( CAR(p) ) ; p = CDR(p) ;
	
	UNPACK_EXTERNAL_ARGS(cargs,p)
	return module->invoke( fun, cargs, nargs ) ;
END_RCPP
}

SEXP class__newInstance(SEXP args){
	SEXP p = CDR(args) ;
	
	XP_Module module( CAR(p) ) ; p = CDR(p) ;
	XP_Class clazz( CAR(p) ) ; p = CDR(p);
	UNPACK_EXTERNAL_ARGS(cargs,p)
	return clazz->newInstance(cargs, nargs ) ;
}

SEXP rcpp_dummy_pointer = R_NilValue; // relies on being set in .onLoad()

#define CHECK_DUMMY_OBJ(p) if(p == rcpp_dummy_pointer) forward_exception_to_r ( Rcpp::not_initialized())

SEXP class__dummyInstance(SEXP args) {
	SEXP p;

	if(args == R_NilValue)
		return rcpp_dummy_pointer;
	p  = CDR(args);

	if(p != R_NilValue)
		rcpp_dummy_pointer = CAR(p);
	return rcpp_dummy_pointer;
}

SEXP CppMethod__invoke(SEXP args){
	SEXP p = CDR(args) ;
	
	// the external pointer to the class
	XP_Class clazz( CAR(p) ) ; p = CDR(p);
	
	// the external pointer to the method
	SEXP met = CAR(p) ; p = CDR(p) ;
	
	// the external pointer to the object
	SEXP obj = CAR(p); p = CDR(p) ;
	CHECK_DUMMY_OBJ(obj);
	
	// additional arguments, processed the same way as .Call does
	UNPACK_EXTERNAL_ARGS(cargs,p)
	
   	return clazz->invoke( met, obj, cargs, nargs ) ;
}

SEXP CppMethod__invoke_void(SEXP args){
	SEXP p = CDR(args) ;
	
	// the external pointer to the class
	XP_Class clazz( CAR(p) ) ; p = CDR(p);
	
	// the external pointer to the method
	SEXP met = CAR(p) ; p = CDR(p) ;
	
	// the external pointer to the object
	SEXP obj = CAR(p); p = CDR(p) ;
	CHECK_DUMMY_OBJ(obj);
	
	// additional arguments, processed the same way as .Call does
	UNPACK_EXTERNAL_ARGS(cargs,p)
	clazz->invoke_void( met, obj, cargs, nargs ) ;
   	return R_NilValue ;
}

SEXP CppMethod__invoke_notvoid(SEXP args){
	SEXP p = CDR(args) ;
	
	// the external pointer to the class
	XP_Class clazz( CAR(p) ) ; p = CDR(p);
	
	// the external pointer to the method
	SEXP met = CAR(p) ; p = CDR(p) ;
	
	// the external pointer to the object
	SEXP obj = CAR(p); p = CDR(p) ;
	CHECK_DUMMY_OBJ(obj);
	
	// additional arguments, processed the same way as .Call does
	UNPACK_EXTERNAL_ARGS(cargs,p)
	
   	return clazz->invoke_notvoid( met, obj, cargs, nargs ) ;
}

namespace Rcpp{
	static Module* current_scope  ;
}

// [[Rcpp::register]]
Rcpp::Module* getCurrentScope(){ 
    return Rcpp::current_scope ; 
}

// [[Rcpp::register]]
void setCurrentScope( Rcpp::Module* scope ){ 
    Rcpp::current_scope = scope ; 
}

extern "C" void R_init_Rcpp11( DllInfo* info){
	Rcpp::current_scope = 0 ;
	
	// init the cache
	init_Rcpp11_cache() ;
	
	// init routines
	init_Rcpp11_routines(info) ;
}

