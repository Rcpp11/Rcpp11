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

#ifndef Rcpp__sugar__transform_h
#define Rcpp__sugar__transform_h

namespace Rcpp{
namespace sugar{

    template <int RTYPE, bool needs_cast, typename storage_type, typename value_type, typename result_type, typename InputIterator, typename Func >
    class Transform : public Rcpp::VectorBase< RTYPE, true, Transform<RTYPE,needs_cast, storage_type, value_type, result_type, InputIterator, Func> > {
    public:
        Transform( InputIterator begin, Func func_, size_t n_ ): n(n_), it(begin), func(func_) {}
        
        inline storage_type operator[]( int i ) const {
            return func( *(it + i) ) ;
        }
        inline int size() const { return n ; }
        
    private:
        size_t n ;
        InputIterator it ;
        Func func ;
    } ;

    template <int RTYPE, typename storage_type, typename value_type, typename result_type, typename InputIterator, typename Func >
    class Transform<RTYPE,true,storage_type,value_type,result_type,InputIterator,Func> : public Rcpp::VectorBase< RTYPE, true, Transform<RTYPE, true, storage_type, value_type, result_type, InputIterator, Func> > {
    public:
        Transform( InputIterator begin, Func func_, size_t n_ ): n(n_), it(begin), func(func_) {}
        
        inline storage_type operator[]( int i ) const {
            return Rcpp::internal::caster<result_type,storage_type>( func( *(it + i) ) ) ;
        }
        inline int size() const { return n ; }
        
    private:
        size_t n ;
        InputIterator it ;
        Func func ;
    } ;

     
    template <typename InputIterator, typename Func>
    struct import_transform_type {
        typedef typename std::iterator_traits<InputIterator>::value_type value_type ;
        typedef typename std::result_of<Func(value_type)>::type result_type ;
        
        const static int RTYPE = Rcpp::traits::r_sexptype_traits<result_type>::rtype ;
        typedef typename Rcpp::traits::storage_type<RTYPE>::type storage_type ; 
        typedef typename std::is_same<result_type, storage_type>::type needs_cast_type ;
                
        typedef Transform<RTYPE,!needs_cast_type::value,storage_type,value_type, result_type, InputIterator, Func> type ;
    } ;
    
} // sugar

template <typename InputIterator, typename Func>
inline typename sugar::import_transform_type<InputIterator,Func>::type 
transform( InputIterator begin, InputIterator end, Func func ){
    return typename sugar::import_transform_type<InputIterator,Func>::type( begin, func, std::distance(begin, end) ) ;    
}



} // Rcpp
#endif

