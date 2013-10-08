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

#ifndef Rcpp__vector__string_const_name_proxy_h
#define Rcpp__vector__string_const_name_proxy_h

namespace Rcpp{
namespace internal{
	
	template <int RTYPE>
	class string_const_name_proxy{
	public:
		typedef typename ::Rcpp::Vector<RTYPE> VECTOR ;
		
		string_const_name_proxy( const VECTOR& v, const std::string& name_) :
			parent(v), name(name_){}
		string_const_name_proxy( const string_const_name_proxy& other ) : 
			parent(other.parent), name(other.name){}
		~string_const_name_proxy(){}
		
		string_const_name_proxy& operator=( const string_const_name_proxy& other) = delete ;
		
		operator char* (){
			 return get() ;
		}
		
		operator SEXP(){
			return ::Rf_mkString(get()) ;
		}
		
	private:
		VECTOR& parent ;
		std::string name;
		
		char* get(){
			return parent.at(name) ;
		}
		
	} ;

}
}
#endif
