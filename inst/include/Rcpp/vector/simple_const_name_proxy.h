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

#ifndef Rcpp__vector__simple_const_name_proxy_h
#define Rcpp__vector__simple_const_name_proxy_h

namespace Rcpp{
namespace internal{
	
	template <int RTYPE> class simple_const_name_proxy {
	public:
		typedef ::Rcpp::Vector<RTYPE> VECTOR ;
		typedef typename ::Rcpp::traits::storage_type<RTYPE>::type CTYPE ;
		
		simple_const_name_proxy( const VECTOR& v, const std::string& name_) :
			parent(v), name(name_){}
		simple_const_name_proxy( const simple_const_name_proxy& other ) : 
			parent(other.parent), name(other.name){}
		~simple_const_name_proxy() {}
		
		simple_const_name_proxy& operator=( const simple_const_name_proxy& other) = delete ;
		
		operator CTYPE() const {
			 return get() ;
		}
		
		operator SEXP() const {
			return ::Rcpp::wrap(get()) ;
		}
		
	private:
		const VECTOR& parent ;
		std::string name;
		CTYPE get() const {
			return parent.at(name) ;
		}
	} ;

}
}
#endif
