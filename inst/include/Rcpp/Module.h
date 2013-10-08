//
// Module.h:  Rcpp modules
//
// Copyright (C) 2010 - 2012 Dirk Eddelbuettel and Romain Francois
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

#ifndef Rcpp_Module_h
#define Rcpp_Module_h
   
namespace Rcpp{
    namespace internal{
        
        template <typename FROM, typename TO>
        std::string get_converter_name(const char* from, const char* to){
            std::string method_name( ".___converter___" ) ;
            typedef typename Rcpp::traits::r_type_traits< typename Rcpp::traits::remove_const_and_reference<FROM>::type >::r_category FROM_CATEGORY ;
            if( std::is_same< FROM_CATEGORY, ::Rcpp::traits::r_type_module_object_tag >::value ){
                method_name += "Rcpp_" ;    
            }
            method_name += from ;
            method_name += "___" ;
            typedef typename Rcpp::traits::r_type_traits< typename Rcpp::traits::remove_const_and_reference<TO>::type >::r_category TO_CATEGORY ;
            if( std::is_same< TO_CATEGORY, ::Rcpp::traits::r_type_module_object_tag >::value ){
                method_name += "Rcpp_" ;    
            }
            method_name += to ;
            
            return method_name ;
        }
        
        
    }
       
    class class_Base ;
    
    template <bool unused>
    class CppClass_Impl ;
    using CppClass = CppClass_Impl<true> ;
    
    template <bool unused>
    class CppObject_Impl ;
    using CppObject = CppObject_Impl<true> ;
    
    template <bool unused>
    class Module_Impl ; 
    using Module = Module_Impl<true> ;
    
    class CppFunction ;
    
    typedef XPtr<Module> XP_Module ; 
    typedef XPtr<class_Base> XP_Class ; 
    typedef XPtr<CppFunction> XP_Function ; 

}

#include <Rcpp/module/get_return_type.h>
#include <Rcpp/module/get_signature.h>
#include <Rcpp/module/FunctionInvoker.h>
#include <Rcpp/module/ConstructorInvoker.h>
#include <Rcpp/module/FactoryInvoker.h>
#include <Rcpp/module/MethodInvoker.h>

#include <Rcpp/module/class_Base.h>
#include <Rcpp/module/debug_method.h>
#include <Rcpp/module/debug_function.h>
#include <Rcpp/module/CppFunction.h>
#include <Rcpp/module/debug_constructor.h>
#include <Rcpp/module/Module.h>

Rcpp::Module* getCurrentScope__impl() ;
inline Rcpp::Module* getCurrentScope(){
    GET_CALLABLE(getCurrentScope__impl)
}

void setCurrentScope__impl( Rcpp::Module* ) ;
void setCurrentScope( Rcpp::Module* mod ){
    VOID_GET_CALLABLE(setCurrentScope__impl, mod )    
}


namespace Rcpp{
        
    template <typename Class>
    class CppMethod {
    public:
        typedef Rcpp::XPtr<Class> XP ;   
        
        CppMethod() {}
        virtual SEXP operator()(Class* object, SEXP* args) { return R_NilValue ; }
        virtual ~CppMethod(){}
        virtual int nargs(){ return 0 ; }
        virtual bool is_void(){ return false ; }
        virtual bool is_const(){ return false ; }
        virtual void signature(std::string& s, const char* name ){ s = name ; }
    } ;
    
    template <typename Class, typename Parent>
    class CppInheritedMethod : public CppMethod<Class> {
    public:
        typedef Rcpp::XPtr<Class> XP ;
        typedef CppMethod<Parent> ParentMethod ;
        
        CppInheritedMethod( ParentMethod* parent_method_pointer_ ) : 
            parent_method_pointer(parent_method_pointer_) 
        {}
        
        SEXP operator()( Class* object, SEXP* args){
			return (*parent_method_pointer)( (Parent*)object, args ) ;  
		}
		inline int nargs(){ return parent_method_pointer->nargs() ; }
		inline bool is_void(){ return parent_method_pointer->is_void() ; }
		inline bool is_const(){ return parent_method_pointer->is_const() ; }
		inline void signature(std::string& s, const char* name){ return parent_method_pointer->signature(s, name) ; }
		
    private:
        ParentMethod* parent_method_pointer ;
    } ;

#include <Rcpp/module/Constructor.h>
#include <Rcpp/module/Factory.h>

#include <Rcpp/module/yes.h>

    typedef bool (*ValidConstructor)(SEXP*,int) ;
    typedef bool (*ValidMethod)(SEXP*,int) ;

    template <typename Class>
    class SignedConstructor {
    public:
    
        SignedConstructor( 
                          Constructor_Base<Class>* ctor_, 
                          ValidConstructor valid_, 
                          const char* doc
                           ) : ctor(ctor_), valid(valid_), docstring(doc == 0 ? "" : doc){}
    
        Constructor_Base<Class>* ctor ;
        ValidConstructor valid ;
        std::string docstring ;
    
        inline int nargs(){ return ctor->nargs() ; }
        inline void signature(std::string& buffer, const std::string& class_name){ 
            ctor->signature(buffer, class_name) ;
        }
    } ;
    
    template <typename Class>
    class SignedFactory {
    public:
    
        SignedFactory( 
                          Factory_Base<Class>* fact_, 
                          ValidConstructor valid_, 
                          const char* doc
                           ) : fact(fact_), valid(valid_), docstring(doc == 0 ? "" : doc){}
    
        Factory_Base<Class>* fact ;
        ValidConstructor valid ;
        std::string docstring ;
    
        inline int nargs(){ return fact->nargs() ; }
        inline void signature(std::string& buffer, const std::string& class_name){ 
            fact->signature(buffer, class_name) ;
        }
    } ;


    template <typename Class>
    class SignedMethod {
    public:
        typedef CppMethod<Class> METHOD ;
        SignedMethod( METHOD* m, ValidMethod valid_, const char* doc ) : method(m), valid(valid_), docstring(doc == 0 ? "" : doc) {}
    
        METHOD* method ;
        ValidMethod valid ;
        std::string docstring ;
    
        inline int nargs(){ return method->nargs() ; }
        inline bool is_void(){ return method->is_void() ; }
        inline bool is_const(){ return method->is_const() ; }
        inline void signature(std::string& s, const char* name){ 
            method->signature(s, name);
        }

    } ;

    template <typename Class>
    class S4_CppConstructor : public Rcpp::Reference {
    public:  
        typedef XPtr<class_Base> XP_Class ;
        
        S4_CppConstructor( SignedConstructor<Class>* m, const XP_Class& class_xp, const std::string& class_name, std::string& buffer ) : Reference( "C++Constructor" ){
            RCPP_DEBUG( "S4_CppConstructor( SignedConstructor<Class>* m, SEXP class_xp, const std::string& class_name, std::string& buffer" ) ;
            field( "pointer" )       = Rcpp::XPtr< SignedConstructor<Class> >( m, false ) ;
            field( "class_pointer" ) = class_xp ;
            field( "nargs" )         = m->nargs() ;
            m->signature( buffer, class_name ) ;
            field( "signature" )     = buffer ;
            field( "docstring" )     = m->docstring ;
        }
        
        S4_CppConstructor( const S4_CppConstructor& other) : Reference( other.get__() ) {}
        S4_CppConstructor& operator=( const S4_CppConstructor& other){
            set__( other.get__() ); 
            return *this ;
        }              
    } ;

    template <typename Class>
    class S4_CppOverloadedMethods : public Rcpp::Reference {
    public:    
        typedef Rcpp::XPtr<class_Base> XP_Class ;
        typedef SignedMethod<Class> signed_method_class ;
        typedef std::vector<signed_method_class*> vec_signed_method ;
        
        // FIXME: is class_xp protected ?
        S4_CppOverloadedMethods( vec_signed_method* m, const XP_Class& class_xp, const char* name, std::string& buffer ) : Reference( "C++OverloadedMethods" ){
            RCPP_DEBUG( "S4_CppOverloadedMethods( vec_signed_method* m, const XP_Class& class_xp = <%p>, const char* name = %s, std::string& buffer )", name, class_xp.get__() )
            #if RCPP_DEBUG_LEVEL > 0
                Rf_PrintValue( class_xp ) ;
            #endif
            
            int n = m->size() ;
            Rcpp::LogicalVector voidness(n), constness(n) ;
            Rcpp::CharacterVector docstrings(n), signatures(n) ;
            Rcpp::IntegerVector nargs(n) ;
            signed_method_class* met ;
            for( int i=0; i<n; i++){ 
                met = m->at(i) ;
                nargs[i] = met->nargs() ;
                voidness[i] = met->is_void() ;
                constness[i] = met->is_const() ;
                docstrings[i] = met->docstring ;
                met->signature(buffer, name) ;
                signatures[i] = buffer ;
            }
        
            field( "pointer" )       = Rcpp::XPtr< vec_signed_method >( m, false ) ;
            field( "class_pointer" ) = class_xp ;
            field( "size" )          = n ;
            field( "void" )          = voidness ;
            field( "const" )         = constness ;
            field( "docstrings" )    = docstrings ;
            field( "signatures" )    = signatures ;
            field( "nargs" )         = nargs ;
            
        }
        S4_CppOverloadedMethods( const S4_CppOverloadedMethods& other){ 
            set__( other.get__() ) ;
        }
        S4_CppOverloadedMethods& operator=( const S4_CppOverloadedMethods& other){ 
            set__( other.get__() ) ;
            return *this ;
        }
    } ;

    #include <Rcpp/module/property_invoke.h>
    
    #include <Rcpp/module/CppMethod.h>
    
    template <typename Class>
    class CppFinalizer{ 
    public:
        CppFinalizer(){} ;
        virtual void run(Class* ){} ;
    } ;

    template <typename Class>
    class FunctionFinalizer : public CppFinalizer<Class> {
    public:
        typedef void (*Pointer)(Class*) ;
        FunctionFinalizer( Pointer p ) : finalizer(p){} ;
    
        virtual void run(Class* object){ 
            finalizer( object ) ;
        }
    
    private:
        Pointer finalizer ;    
    } ;

    #include <Rcpp/module/CppProperty.h>

    template <typename Class>
    class S4_field : public Rcpp::Reference {
    public:   
        typedef XPtr<class_Base> XP_Class ;
        S4_field( CppProperty<Class>* p, const XP_Class& class_xp ) : Reference( "C++Field" ){
            RCPP_DEBUG( "S4_field( CppProperty<Class>* p, const XP_Class& class_xp )" )
            field( "read_only" )     = p->is_readonly() ;
            field( "cpp_class" )     = p->get_class();
            field( "pointer" )       = Rcpp::XPtr< CppProperty<Class> >( p, false ) ;
            field( "class_pointer" ) = class_xp ;
            field( "docstring" )     = p->docstring ;
        }
        S4_field( const S4_field& other) : Reference(other.get__()) {}
        S4_field& operator=(const S4_field& other){
            set__(other.get__());
            return *this ;
        }
    } ;

#include <Rcpp/module/class.h>

    template <typename Enum, typename Parent>
    class enum_ {
        public:
            typedef enum_<Enum,Parent> self ;
            
            enum_( const char* name_ ) : 
                name(name_), values(), parent_typeinfo_name( typeid(Parent).name() ){ 
                } 
            ~enum_(){
                Rcpp::Module* module = getCurrentScope() ;
                module->add_enum( parent_typeinfo_name, name, values ) ;
            }
            
            self& value( const char* name_, Enum value_ ){
                values.insert( PAIR( name_, static_cast<int>( value_ ) ) ) ;
                return *this ;
            }
                
        private:
            
            std::string name ;
            typedef std::map< std::string, int > MAP ;
            typedef MAP::value_type PAIR ;
            MAP values ;
            std::string parent_typeinfo_name ;
            
    } ;
    
    // function factories
    #include <Rcpp/module/function.h>

    template <typename FROM, typename TO>
    void converter( const char* from, const char* to, TO (*fun)(FROM), const char* docstring = 0 ){
        std::string fun_name = internal::get_converter_name<FROM,TO>( from, to ) ;
        function( fun_name.c_str(), fun, docstring ) ;
    }  
       
    template <bool unused>
    class CppClass_Impl : public S4{
    public:
        typedef Rcpp::XPtr<Rcpp::Module> XP ;
        CppClass_Impl( SEXP x) : S4(x){};
        CppClass_Impl( Module_Impl<unused>* p, class_Base* cl, std::string& buffer ) : S4("C++Class") {
            XP_Class clxp( cl, false, R_NilValue, R_NilValue ) ;
            slot( "module"  ) = XP( p, false ) ;
            slot( "pointer" ) = clxp ;
            
            buffer = "Rcpp_" ;
            buffer += cl->name ;
            slot( ".Data" ) = buffer ;
            
            slot( "fields" )      = cl->fields( clxp ) ;
            
            slot( "methods" )     = cl->getMethods( clxp, buffer ) ;
            slot( "constructors") = cl->getConstructors( clxp, buffer ) ;
            slot( "docstring"   ) = cl->docstring ;
            slot( "typeid" )      = cl->get_typeinfo_name() ;
            slot( "enums"  )      = cl->enums ;
            slot( "parents" )     = cl->parents ;
        }
    } ;

    template <bool unused>
    class CppObject_Impl : public S4{
    public:
        typedef XPtr<Rcpp::Module> XP ;
        CppObject_Impl( Module_Impl<unused>* p, class_Base* clazz, SEXP xp ) : S4("C++Object") {
            slot( "module" )   = XP( p, false ) ;
            slot( "cppclass" ) = XPtr<class_Base>( clazz, false ) ;
            slot( "pointer" )  = xp ;
	    }
    } ;

    template <bool unused>
    CppClass_Impl<unused> Module_Impl<unused>::get_class( const std::string& cl ){
		BEGIN_RCPP
			CLASS_MAP::iterator it = classes.find(cl) ;
			if( it == classes.end() ) throw std::range_error( "no such class" ) ;
			std::string buffer ;
			return CppClass_Impl<unused>( this, it->second, buffer ) ;
		END_RCPP
	}
	
}

#define RCPP_MODULE(name)                                               \
    void _rcpp_module_##name##_init() ;                                 \
    static Rcpp::Module _rcpp_module_##name( # name ) ;                 \
    extern "C" SEXP _rcpp_module_boot_##name(){                         \
        ::setCurrentScope( & _rcpp_module_##name ) ;                    \
        _rcpp_module_##name##_init( ) ;                                 \
        Rcpp::XPtr<Rcpp::Module> mod_xp(& _rcpp_module_##name , false); \
        ::setCurrentScope( 0 ) ;                                        \
        return mod_xp ;                                                 \
    }                                                                   \
    void _rcpp_module_##name##_init()

#endif

