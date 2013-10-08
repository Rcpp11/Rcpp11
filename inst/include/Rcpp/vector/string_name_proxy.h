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

#ifndef Rcpp__vector__string_name_proxy_h
#define Rcpp__vector__string_name_proxy_h

namespace Rcpp{
namespace internal{
	
	template <int RTYPE>
	class string_name_proxy{
	public:
		typedef typename ::Rcpp::Vector<RTYPE> VECTOR ;
		
		string_name_proxy( VECTOR& v, const std::string& name_) :
			parent(v), name(name_){}
		string_name_proxy( const string_name_proxy& other ) : 
			parent(other.parent), name(other.name){}
		~string_name_proxy(){}
		
		string_name_proxy& operator=( const std::string& rhs ){
			set( Rf_mkChar(rhs.c_str()) ) ;
			return *this ;
		}
		string_name_proxy& operator=( const string_name_proxy& other){
			set( Rf_mkChar( other.get() ) ) ;
			return *this ;
		}
		string_name_proxy& operator=( const Na_Proxy& /* other */){
		    set( Rcpp::traits::get_na<RTYPE>() );
		    return *this ;
		}
		
		operator char* (){
			 return get() ;
		}
		
		operator SEXP(){
			return ::Rf_mkString(get()) ;
		}
		
		inline int size(){ return strlen( get() ) ; }
		
	private:
		VECTOR& parent ;
		std::string name;
		
		void set( SEXP rhs ){
			int index = 0 ;
			try{
				index = parent.offset(name) ;
				parent[ index ] = rhs ;
			} catch( const index_out_of_bounds& /* ex */ ){
				parent.push_back( rhs, name ); 
			}
		}
		
		char* get(){
			return parent[ parent.offset(name) ];
		}
		
	} ;

}
}
#endif
