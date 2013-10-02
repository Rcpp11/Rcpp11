//
// is.h:  test if an R Object can be seen as one type
//
// Copyright (C) 2013    Dirk Eddelbuettel and Romain Francois
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

#ifndef Rcpp__is__h
#define Rcpp__is__h

namespace Rcpp{
      
    namespace internal{  
        
        // simple implementation, for most default types
        template <typename T> bool is__simple( SEXP x) ;
        
        template <typename T>
        struct Is {
            inline bool test(SEXP x){
                return false ;    
            }
        } ;
        template <> struct Is<RObject> ;
        template <> struct Is<DataFrame> ;
        template <> struct Is<S4> ;
        template <> struct Is<Reference> ;
        template <> struct Is<Formula> ;
        template <> struct Is<Function> ;
        
        template <int RTYPE> struct TypeofIs{
            inline bool test(SEXP x){
                return TYPEOF(x) == RTYPE ;    
            }
        } ;
        
        template <typename T>
        struct PrimitiveIs{
            inline bool test(SEXP x){
                return Rf_length(x) == 1 && 
                    TYPEOF(x) == Rcpp::traits::r_sexptype_traits<T>::rtype ;    
            }
        };
           
        template <int RTYPE> struct Is< Vector<RTYPE> > : TypeofIs<RTYPE>{} ;
        template <int RTYPE> struct Is< Matrix<RTYPE> >  ;
        
        template <> struct Is<Environment>   : TypeofIs<ENVSXP> {} ;
        template <> struct Is<Pairlist>      : TypeofIs<LISTSXP> {} ;
        template <> struct Is<Promise>       : TypeofIs<PROMSXP> {} ;
        template <> struct Is<Symbol>        : TypeofIs<SYMSXP> {} ;
        template <> struct Is<WeakReference> : TypeofIs<WEAKREFSXP> {} ;
        template <> struct Is<Language>      : TypeofIs<LANGSXP> {} ;
        
        template <typename T> struct ModuleIs ;
        
        template <typename T>
        struct is_type{
            typedef typename std::conditional<
                Rcpp::traits::is_module_object<T>::value, 
                typename ModuleIs<T>::type, 
                typename std::conditional<
                    Rcpp::traits::is_primitive<T>::value, 
                    typename PrimitiveIs<T>::type,
                    typename Is<T>::type
                >
            >::type type ;
        } ;
        
    }
    
    /** identify if an x can be seen as the T type
     *  
     *  example:
     *     bool is_list = is<List>( x ) ;
     */
    template <typename T> bool is( SEXP x ){
        return typename internal::is_type<T>::type().test(x) ;
    }
    
} // Rcpp 

#endif
