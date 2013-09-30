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

#ifndef Rcpp__vector__generic_const_name_proxy_h
#define Rcpp__vector__generic_const_name_proxy_h

namespace Rcpp{
namespace internal{
		
	template <int RTYPE> class generic_const_name_proxy {
	public:
		typedef ::Rcpp::Vector<RTYPE> VECTOR ;
		generic_const_name_proxy( const VECTOR& v, const std::string& name_) :
			parent(v), name(name_){
				RCPP_DEBUG( "generic_const_name_proxy( VECTOR& = %p, const string& = %s)", v.asSexp(), name_.c_str() );
		} ;
		generic_const_name_proxy( const generic_const_name_proxy& other ) : 
			parent(other.parent), name(other.name){} ;
		~generic_const_name_proxy(){} ;
		
		generic_const_name_proxy& operator=( const generic_const_name_proxy& other) = delete ;
		
		operator SEXP() const {
			 return get() ;
		}
		
		template <typename T>
		operator T() const {
			return ::Rcpp::as<T>( get() ) ;
		}
		
		operator bool() const{
		    return ::Rcpp::as<bool>(get()); 
		}
		
	private:
		const VECTOR& parent ;
		std::string name;
		
		SEXP get() const {
			return parent[ parent.offset(name) ];
		}
		
	} ;
}
}
#endif
