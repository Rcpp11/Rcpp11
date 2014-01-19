#ifndef Rcpp_DottedPairMultipleNamedProxyPolicy_h
#define Rcpp_DottedPairMultipleNamedProxyPolicy_h

namespace Rcpp {
    
    template <typename CLASS>
    class DottedPairMultipleNamedProxyPolicy {
        
        class Proxy {
        public:
          
            Proxy( CLASS& obj_ ) : obj(obj_), map() {
                for( SEXP p = obj ; !Rf_isNull(p); p = CDR(p) ){
                    map[ TAG(p) ] = p ;
                }
                
            }      
          
            template <typename... Args>
            void set( Args... args){
                static_assert( traits::all_named<Args...>::type::value, "all parameters must be named" ) ;
                set__impl(args...) ;
            }
            
            
        private:
            CLASS& obj ;
            std::unordered_map<SEXP, SEXP> map ;
            
            template <typename T, typename... Args>
            void set__impl( traits::named_object<T> first, Args... args){
                set__one( first ) ;
                set__impl( args... ) ;
            }
            
            template <typename T>
            void set__impl( traits::named_object<T> first ){
                set__one( first ) ;  
            }
            
            template <typename T>
            void set__one( traits::named_object<T> first){
                SEXP tag = Rf_install( first.name.c_str() ) ;
                auto it = map.find( tag ) ;
                if( it == map.end() ){
                    map[tag] = obj.push_back(first) ;
                } else {
                    SETCDR(it->second, wrap(first.object) ) ;
                } 
            }
            
        } ;
          
      public:
        
        template <typename... Args>
        void set( Args... args){         
            Proxy( static_cast<CLASS&>(*this) ).set( args... ) ;
        }
        
    } ;
    
}

#endif
