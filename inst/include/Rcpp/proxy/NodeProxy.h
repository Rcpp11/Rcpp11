#ifndef Rcpp_proxy_NodeProxy_h
#define Rcpp_proxy_NodeProxy_h

namespace Rcpp{
    
    template <typename NodeClass>
    class NodeProxyPolicy {
    public:
        
        class ValueProxy {
        public:
          ValueProxy( SEXP node_ ) : node(node_){}
          
          ValueProxy& operator=( const ValueProxy& rhs){
              if(this != &rhs) set( rhs.get() ) ;
              return *this ;
          }
          
          template <typename T>
          ValueProxy& operator=( const T& rhs) {
              return set( wrap(rhs) ) ;  
          }
          
          template <typename T>
          operator T() const {
              return as<T>(get());  
          }
          
        private:
          SEXP node ;
          
          inline SEXP get() const {
              return CAR(node) ; 
          }
          
          inline ValueProxy& set( SEXP x){
              SETCAR(node, x) ;
              return *this ;
          }
          
        } ;
        
        inline ValueProxy value() {
            return ValueProxy( static_cast<NodeClass&>(*this).get() ) ;  
        }
        
        inline const ValueProxy value() const {
            return ValueProxy( const_cast<NodeClass&>(static_cast<const NodeClass&>(*this)).get() ) ;  
        }
        
        
        class TagProxy {
        public:
          TagProxy( SEXP node_ ) : node(node_){}
          
          TagProxy& operator=( const TagProxy& rhs){
              if(this != &rhs) set( rhs.get() ) ;
              return *this ;
          }
          
          template <typename T>
          TagProxy& operator=( const T& rhs){
              return set( Symbol(rhs) ) ;  
          }
          
          inline operator SEXP() const {
              return get() ;  
          }
          
        private:
          SEXP node ;
          
          inline SEXP get() const {
              return TAG(node) ; 
          }
          
          inline TagProxy& set(SEXP x){
              SET_TAG(node, x) ;
              return *this ;
          }
          
        } ;
        
        inline TagProxy tag() {
            return TagProxy( static_cast<NodeClass&>(*this).get() ) ;  
        }
        
        inline const TagProxy tag() const {
            return TagProxy( const_cast<NodeClass&>(static_cast<const NodeClass&>(*this)).get() ) ;  
        }
      
    } ;
  
}

#endif
