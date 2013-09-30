// Copyright (C) 2013    Romain Francois
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

#ifndef Rcpp__Demangler__h
#define Rcpp__Demangler__h

namespace Rcpp{

    template <typename T>
    struct Demangler {
        static std::string get(){ return demangle( typeid(T).name() ) ; }
    } ;
    #define DEMANGLE_ECHO(__TYPE__)                                 \
    template <>                                                     \
    struct Demangler<__TYPE__>{                                     \
        static std::string get(){ return std::string(#__TYPE__) ; } \
    } ;
    
    #define DEMANGLE_CONTAINER_1(__CONTAINER__)    \
    template <typename T>                          \
    struct Demangler< __CONTAINER__<T> >{          \
        static std::string get(){                  \
            std::string res( #__CONTAINER__ ) ;    \
            res += "<" ;                           \
            res += Demangler<T>::get() ;           \
            res += ">" ;                           \
            return res;                            \
        }                                          \
    } ;                                            
    
    #define DEMANGLE_CONTAINER_2(__CONTAINER__)    \
    template <typename KEY, typename VALUE>        \
    struct Demangler< __CONTAINER__<KEY,VALUE> >{  \
        static std::string get(){                  \
            std::string res( #__CONTAINER__ ) ;    \
            res += "<" ;                           \
            res += Demangler<KEY>::get() ;         \
            res += "," ;                           \
            res += Demangler<VALUE>::get() ;       \
            res += ">" ;                           \
            return res;                            \
        }                                          \
    } ;                                            
    
    #define DEMANGLE_CONTAINER_ADAPTOR_1(__CONTAINER__)    \
    template <typename T, typename Container>              \
    struct Demangler< __CONTAINER__<T,Container> >{        \
        static std::string get(){                          \
            std::string res( #__CONTAINER__ ) ;            \
            res += "<" ;                              \
            res += Demangler<T>::get() ;                   \
            res += "," ;                      \
            res += Demangler<Container>::get() ;           \
            res += ">" ;                                   \
            return res;                                    \
        }                                                  \
    } ;                                            
    
    DEMANGLE_ECHO(std::string)  
    
    DEMANGLE_CONTAINER_1(std::vector)
    DEMANGLE_CONTAINER_1(std::list)
    DEMANGLE_CONTAINER_1(std::forward_list)
    DEMANGLE_CONTAINER_1(std::set)
    DEMANGLE_CONTAINER_1(std::deque)
    DEMANGLE_CONTAINER_1(std::unordered_set)
    
    DEMANGLE_CONTAINER_2(std::map)
    DEMANGLE_CONTAINER_2(std::unordered_map)
         
    DEMANGLE_CONTAINER_ADAPTOR_1(std::queue)
    DEMANGLE_CONTAINER_ADAPTOR_1(std::priority_queue)
    DEMANGLE_CONTAINER_ADAPTOR_1(std::stack)
    
} // Rcpp 

#endif
