// named_object.h:  named SEXP
//
// Copyright (C) 2010 - 2013 Dirk Eddelbuettel and Romain Francois
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
   
#ifndef Rcpp__traits__named_object__h
#define Rcpp__traits__named_object__h

namespace Rcpp{
class Argument ;

namespace traits{

template <typename T> struct needs_protection : std::false_type{} ;
template <> struct needs_protection<SEXP> : std::true_type{} ;	

template <typename T> 
class named_object {
	public:
	    typedef T object_type ;
		named_object( const std::string& name_, const T& o_) : 
			name(name_), object(o_){}
		const std::string& name ;
		const T& object ;
} ;
template <> 
class named_object<SEXP> {
public:
    typedef SEXP object_type ;
		
	named_object( const std::string& name_, const SEXP& o_):
		name(name_), object(o_)
	{
		R_PreserveObject(object) ;	
	}
	
	named_object( const named_object<SEXP>& other ) : 
		name(other.name), object(other.object)
	{
		R_PreserveObject(object) ;	
	}
	~named_object(){
		R_ReleaseObject(object) ;	
	}
	const std::string& name ;
	SEXP object ;
} ;


template <typename T> struct is_named : public std::false_type{} ;
template <typename T> struct is_named< named_object<T> >   : public std::true_type {} ;
template <> struct is_named< Rcpp::Argument >   : public std::true_type {} ;

} // namespace traits
} // namespace Rcpp

#endif 
