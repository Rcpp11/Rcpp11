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

#ifndef Rcpp__vector__simple_name_proxy_h
#define Rcpp__vector__simple_name_proxy_h

namespace Rcpp{
namespace internal{
	
	template <int RTYPE> class simple_name_proxy {
	public:
		typedef ::Rcpp::Vector<RTYPE> VECTOR ;
		typedef typename ::Rcpp::traits::storage_type<RTYPE>::type CTYPE ;
		simple_name_proxy( VECTOR& v, const std::string& name_) :
			parent(v), name(name_){}
		simple_name_proxy( const simple_name_proxy& other ) : 
			parent(other.parent), name(other.name){}
		~simple_name_proxy() {}
		
		simple_name_proxy& operator=( CTYPE rhs ){
			set( rhs ) ;
			return *this ;
		}
		simple_name_proxy& operator=( const simple_name_proxy& other){
			set( other.get() ) ;
			return *this ;
		}
		simple_name_proxy& operator=( const Na_Proxy& /* other */ ){
		    set( Rcpp::traits::get_na<RTYPE>() );
		    return *this ;
		}
		
		template <typename T>
		simple_name_proxy& operator=( const T& rhs ){
			set( caster<T,CTYPE>(rhs) ) ;
			return *this ;
		}
		
		operator CTYPE() const {
			 return get() ;
		}
		
		operator SEXP() const {
			return ::Rcpp::wrap(get()) ;
		}
		
	private:
		VECTOR& parent ;
		std::string name;
		void set( CTYPE rhs ){
			int index = 0 ;
			try{
				index = parent.offset(name) ;
				parent[ index ] = rhs ;
			} catch( const index_out_of_bounds& /* ex */ ){
				parent.push_back( rhs, name ); 
			}
		}
		CTYPE get() const {
			return parent.at(name) ;
		}
	} ;

}
}
#endif
