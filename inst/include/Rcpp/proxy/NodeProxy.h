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
          ValueProxy& operator=( const T& rhs) ;
          
          template <typename T>
          operator T() const ;
          
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
        
        class const_ValueProxy{
        public:
          const_ValueProxy(SEXP node_) : node(node_){}
          
          template <typename T>
          operator T() const ;
          
        private:
          SEXP node ;
          
          inline SEXP get() const {
              return CAR(node) ; 
          }
          
        } ;
        
        inline ValueProxy value() {
            return ValueProxy( static_cast<NodeClass&>(*this).get() ) ;  
        }
        
        inline const_ValueProxy value() const {
            return const_ValueProxy( static_cast<const NodeClass&>(*this).get() ) ;  
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
              SETTAG(node, x) ;
              return *this ;
          }
          
        } ;
        
        class const_TagProxy {
        public:
          const_TagProxy( SEXP node_ ) : node(node_){}
          
          inline operator SEXP() const {
              return get() ;  
          }
          
        private:
          SEXP node ;
          
          inline SEXP get() const {
              return TAG(node) ; 
          }
          
        } ;
        
        
        inline TagProxy tag() {
            return TagProxy( static_cast<NodeClass&>(*this).get() ) ;  
        }
        
        inline const_TagProxy tag() const {
            return const_TagProxy( static_cast<const NodeClass&>(*this).get() ) ;  
        }
      
    } ;
  
}

#endif
