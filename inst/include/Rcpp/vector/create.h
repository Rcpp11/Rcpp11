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

#ifndef Rcpp__vector_create_h
#define Rcpp__vector_create_h

namespace Rcpp{
    
template <int RTYPE, typename... Args>
class Create {
    typedef typename traits::r_vector_element_converter<RTYPE>::type converter_type ;
    typedef Vector<RTYPE> Vec ;
    
    public:
        Create( Args... args ) : data( (int)sizeof...(Args) ) {
            set_value( traits::number_to_type<sizeof...(Args)>(), 0, args...) ;
        }
        operator Vec(){ return data ; }
        
    private:
        template <typename T, typename... Pack>
        inline void set_value( traits::number_to_type<sizeof...(Pack) + 1>, int i, const T& obj, const Pack&... pack ){
            data[i] = converter_type::get(obj) ;
            set_value( typename traits::number_to_type< sizeof...(Pack) >() , i+1, pack... ) ;
        }
        
        inline void set_value( traits::number_to_type<0>, int i ){}
        
        Vec data ;
} ;  

template <int RTYPE, typename... Args>
class CreateWithNames {
    typedef typename traits::r_vector_element_converter<RTYPE>::type converter_type ;
    typedef Vector<RTYPE> Vec ;
    
    public:
        CreateWithNames( Args... args ) : 
            data( (int)sizeof...(Args)), 
            names( (int)sizeof...(Args))
        {
            if( sizeof...(Args) ){
                set_value( traits::number_to_type<sizeof...(Args)>(), 0, args...) ;
            }
            data.names() = names ;
        }
        
        operator Vec(){ return data ; }
        
    private:
        template <typename T, typename... Pack>
        inline void set_value( traits::number_to_type<sizeof...(Pack) + 1>, int i, const T& obj, const Pack&... pack ){
            data[i] = converter_type::get(obj) ;
            names[i] = Rf_mkChar( internal::get_object_name(obj) ) ;
            set_value( typename traits::number_to_type< sizeof...(Pack) >() , i+1, pack... ) ;
        }
        
        inline void set_value( traits::number_to_type<0>, int i){}
        
        
        Vec data ;
        CharacterVector names ;
} ;  

template <int RTYPE, typename... Args>
struct create_type {
    typedef typename std::conditional<
        traits::has_names<Args...>::type::value, 
        CreateWithNames<RTYPE, Args...>,
        Create<RTYPE, Args...>
    >::type type ;
} ;

}
#endif
