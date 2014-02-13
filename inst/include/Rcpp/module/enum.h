#ifndef RCPP_MODULE_ENUM_H
#define RCPP_MODULE_ENUM_H

namespace Rcpp {
  
    template <typename Enum, typename Parent>
    class enum_ {
        public:
            typedef enum_<Enum,Parent> self ;
            
            enum_( const char* name_ ) : 
                name(name_), values(), parent_typeinfo_name( typeid(Parent).name() ){ 
                } 
            ~enum_(){
                Rcpp::Module* module = Module::getCurrent() ;
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

}
#endif
