#ifndef Rcpp_DottedPairImpl_h
#define Rcpp_DottedPairImpl_h

namespace Rcpp{

    template <typename CLASS>
    class DottedPairImpl {
    public:
        
        template <typename T>
        Node push_front( const T& object){
            CLASS& ref = get_ref() ;
            ref = grow(object, ref ) ;
            return Node(ref) ;        
        }
        
        template <typename T>
        Node push_back( const T& object) {
            CLASS& ref = get_ref() ;
            if( ref.isNULL() ){
                ref = grow( object, ref ) ;
                return Node( ref );
            } else {                                       
                SEXP x = ref ;
                /* traverse the pairlist */
                while( !Rf_isNull(CDR(x)) ){
                    x = CDR(x) ;
                }
                Shield<SEXP> tail = pairlist( object ) ; 
                SETCDR( x, tail ) ;
                return Node(tail) ;
            }    
        }
        
        template <typename T>
        Node insert( R_xlen_t index, const T& object) {
            CLASS& ref = get_ref() ;
            if( index == 0 ) {
                return push_front( object ) ;
            } else {
                if( ref.isNULL() || index > Rf_xlength(ref) ) stop("index out of bounds") ;
                
                size_t i=1;
                SEXP x = ref ;
                while( i < index ){
                    x = CDR(x) ;
                    i++; 
                }
                Shield<SEXP> tail = grow( object, CDR(x) ) ; 
                SETCDR( x, tail ) ;
                return Node(tail) ;  
            }
                
        }
        
        template <typename T>
        Node replace( R_xlen_t index, const T& object ) {
            CLASS& ref = get_ref() ;
            if( index >= ::Rf_xlength(ref) ) stop("index out of bounds") ;
              
            Shield<SEXP> x = pairlist( object );
            SEXP y = ref ;
            int i=0;
            while( i<index ){ y = CDR(y) ; i++; }
            
            SETCAR( y, CAR(x) );
            SET_TAG( y, TAG(x) ); 
            return Node(y) ;
        }
        
        inline R_xlen_t length() const { 
            return ::Rf_xlength(get_ref()) ; 
        }
        inline R_xlen_t size() const { 
            return length() ;
        }
        
        void remove( R_xlen_t index ){
            CLASS& ref = get_ref() ;
            SEXP x = ref ;
            if( index >= Rf_xlength(ref) ) stop("index out of bounds") ;
            if( index == 0 ){
                ref = CDR(x) ;
            } else{
                size_t i=1;
                while( i<index ){ x = CDR(x) ; i++; }
                SETCDR( x, CDDR(x) ) ;
            }
    
        }
        
    private:
        CLASS& get_ref(){
            return static_cast<CLASS&>(*this) ;
        }
        
        const CLASS& get_ref() const {
            return static_cast<const CLASS&>(*this) ;
        }
    } ;
    
}

#endif
