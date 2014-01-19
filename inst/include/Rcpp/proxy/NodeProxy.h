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
      
    } ;
  
}

#endif
