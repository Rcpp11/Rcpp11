#ifndef Rcpp_DottedPairImpl_h
#define Rcpp_DottedPairImpl_h

namespace Rcpp{

    template <typename CLASS>
    class DottedPairImpl {
    public:
        
        template <typename T>
        Node push_front( const T& object){
            CLASS& ref = get_ref() ;
            ref.set__( grow(object, ref.get__() ) ) ;
            return Node(ref.get__()) ;        
        }
        
        template <typename T>
        Node push_back( const T& object) {
            CLASS& ref = get_ref() ;
            if( ref.isNULL() ){
                ref.set__( grow( object, ref.get__() ) ) ;
                return Node( ref.get__() );
            } else {                                       
                SEXP x = ref.get__() ;
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
        Node insert( const size_t& index, const T& object) {
            CLASS& ref = get_ref() ;
            if( index == 0 ) {
                return push_front( object ) ;
            } else {
                if( ref.isNULL( ) ) throw index_out_of_bounds() ;
                
                if( static_cast<R_len_t>(index) > ::Rf_length(ref.get__()) ) throw index_out_of_bounds() ;
                
                size_t i=1;
                SEXP x = ref.get__() ;
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
        Node replace( const int& index, const T& object ) {
            CLASS& ref = get_ref() ;
            if( static_cast<R_len_t>(index) >= ::Rf_length(ref.get__()) ) throw index_out_of_bounds() ;
              
            Shield<SEXP> x = pairlist( object );
            SEXP y = ref.get__() ;
            int i=0;
            while( i<index ){ y = CDR(y) ; i++; }
            
            SETCAR( y, CAR(x) );
            SET_TAG( y, TAG(x) ); 
            return Node(y) ;
        }
        
        inline R_len_t length() const { 
            return ::Rf_length(get_ref().get__()) ; 
        }
        inline R_len_t size() const { 
            return length() ;
        }
        
        void remove( const size_t& index ){
            CLASS& ref = static_cast<CLASS&>(*this) ;
            if( static_cast<R_len_t>(index) >= Rf_length(ref.get__()) ) throw index_out_of_bounds() ;
            if( index == 0 ){
                ref.set__( CDR( ref.get__() ) ) ;
            } else{
                SEXP x = ref.get__() ;
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
