#ifndef Rcpp__Matrix_Dimnames_h
#define Rcpp__Matrix_Dimnames_h

namespace Rcpp {

    template <typename Data>
    class RowNamesProxy {
    public:
        
        RowNamesProxy( Data& data_ ) : data(data_){}
        
        inline RowNamesProxy& operator=( const CharacterVector& names ){
            Language call( "rownames<-", data, names ) ;
            data = call.eval() ;
            return *this ;    
        }
        
        inline RowNamesProxy& operator=( std::initializer_list<const char*> names ){
            return this->operator=( CharacterVector(names) ) ;    
        }
        
        inline operator CharacterVector() const {
            Language call( "rownames", data ) ;
            return call.eval() ;
        }
        
    private:
        Data& data ;
    } ;
    
    template <typename Data>
    class ColNamesProxy {
    public:
        
        ColNamesProxy( Data& data_ ) : data(data_){}
        
        inline ColNamesProxy& operator=( const CharacterVector& names ){
            Language call( "colnames<-", data, names ) ;
            data = call.eval() ;
            return *this ;    
        }
        
        inline ColNamesProxy& operator=( std::initializer_list<const char*> names ){
            return this->operator=( CharacterVector(names) ) ;    
        }
        
        inline operator CharacterVector() const {
            Language call( "colnames", data ) ;
            return call.eval() ;
        }
        
    private:
        Data& data ;
    } ;
    
    
    template <int RTYPE, typename Storage>
    inline RowNamesProxy<Matrix<RTYPE, Storage>> rownames( const Matrix<RTYPE, Storage>& m ){
        return RowNamesProxy<Matrix<RTYPE, Storage>>(const_cast<Matrix<RTYPE,Storage>&>(m)) ;    
    }
    
    template <int RTYPE, typename Storage>
    inline ColNamesProxy<Matrix<RTYPE, Storage>> colnames( const Matrix<RTYPE, Storage>& m ){
        return ColNamesProxy<Matrix<RTYPE, Storage>>(const_cast<Matrix<RTYPE,Storage>&>(m)) ;    
    }
    
    template <typename Storage>
    inline RowNamesProxy<DataFrame_Impl<Storage>> rownames( const DataFrame_Impl<Storage>& df ){
        return RowNamesProxy<DataFrame_Impl<Storage>>( const_cast<DataFrame_Impl<Storage>&>(df) ) ;    
    }
    
}

#endif
