// Copyright (C) 2013 Romain Francois
//
// This file is part of Rcpp11.
//
// Rcpp11 is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// Rcpp11 is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Rcpp11.  If not, see <http://www.gnu.org/licenses/>.

#ifndef RCPP_ATTRIBUTES_COLLAPSE_H
#define RCPP_ATTRIBUTES_COLLAPSE_H

namespace Rcpp{
    
    template <typename T>
    struct Identity{
        inline const T& operator()( const T& obj ) const { return obj ; } 
    } ;
    template <typename T, typename Fun>
    class Collapser {
    public:
        
        Collapser( const T& data_, Fun fun_, const char* sep_ = "," ) : 
            data(data_), fun(fun_), sep(sep_){}
        
        template <typename T2, typename Fun2 >
        friend std::ostream& operator<<( std::ostream& os, const Collapser<T2, Fun2>& x );
        
    private:
        
        void print( std::ostream& os) const {
            size_t n = data.size() ;
            if( n ){
                size_t i=0 ;
                for( ; i<n-1; i++){
                    os << fun( data[i] );
                    os << sep ;
                }
                os << fun( data[i] ) ;
            }
        }
        const T& data ;
        Fun fun ;
        std::string sep ;
        
    } ;
    
    template <typename T, typename Fun>
    std::ostream& operator<<( std::ostream& os, const Collapser<T,Fun>& x ){
        x.print(os) ;
        return os ;
    }
     
    template <typename T, typename Fun>
    inline Collapser<T,Fun> collapse( const T& data, Fun fun){
        return Collapser<T,Fun>( data, fun ) ;
    }
    
    template <typename T>
    inline Collapser<T,Identity<typename T::value_type>> collapse( const T& data ){
        return collapse( data, Identity<typename T::value_type>() );     
    }
    
    template <typename T>
    inline Collapser<T,Identity<typename T::value_type>> lines( const T& data ){
        return Collapser<T,Identity<typename T::value_type>>( data, Identity<typename T::value_type>(), "\n" );     
    }
    
}

#endif
