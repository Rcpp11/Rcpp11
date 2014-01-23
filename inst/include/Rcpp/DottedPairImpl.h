#ifndef Rcpp_DottedPairImpl_h
#define Rcpp_DottedPairImpl_h

namespace Rcpp{

    template <typename CLASS>
    class DottedPairImpl {
    public:
        
        template <typename T>
        Node push_back( const T& object) ;
        
        template <typename T>
        Node push_front( const T& object) ;
        
        template <typename T>
        Node insert( const size_t& index, const T& object) ;
        
        template <typename T>
        Node replace( const int& index, const T& object ) ;
        
        inline R_len_t length() const { 
            return ::Rf_length(static_cast<const CLASS&>(*this).get__()) ; 
        }
        inline R_len_t size() const { 
            return ::Rf_length(static_cast<const CLASS&>(*this).get__()) ;
        }
        
        void remove( const size_t& index ); 
	    
    } ;
    
}

#endif
