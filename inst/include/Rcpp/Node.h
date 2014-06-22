#ifndef Rcpp_Node_h
#define Rcpp_Node_h

namespace Rcpp{
      
    class Node {
    public:
        Node( SEXP data_ ) : data(data_){}    
    
        Node next() const {
            return CDR(data) ;
        }
        
        bool last() const {
            return CDR(data) == R_NilValue ;  
        }
        
        inline SEXP get() const { 
            return data; 
        }
        
        class ValueProxy : public GenericProxy<ValueProxy> {
        public:
            ValueProxy( Node& node_ ) : node(node_){}
            
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
            Node& node ;
            
            inline SEXP get() const {
                return CAR(node.get()) ; 
            }
            
            inline ValueProxy& set( SEXP x){
                SETCAR(node.get(), x) ;
                return *this ;
            }
          
        } ;
        
        inline ValueProxy value() {
            return ValueProxy(*this) ;  
        }
        
        inline const ValueProxy value() const {
            return ValueProxy(const_cast<Node&>(*this)) ;  
        }
        
        
        class TagProxy : public GenericProxy<TagProxy> {
        public:
            TagProxy( Node& node_ ) : node(node_){}
            
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
            Node& node ;
            
            inline SEXP get() const {
                return TAG(node.get()) ; 
            }
            
            inline TagProxy& set(SEXP x){
                SET_TAG(node.get(), x) ;
                return *this ;
            }
          
        } ;
        
        inline TagProxy tag() {
            return TagProxy( *this ) ;  
        }
        
        inline const TagProxy tag() const {
            return TagProxy( const_cast<Node&>(*this) ) ;  
        }
        
    private:
        SEXP data ; 
        
    } ;
  
}

#endif
