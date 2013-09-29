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

#ifndef Rcpp__internal__const_Proxy_Iterator__h
#define Rcpp__internal__const_Proxy_Iterator__h

namespace Rcpp{
namespace internal{

template <typename PROXY>
class const_Proxy_Iterator {
public:
		typedef PROXY& reference ;
		typedef PROXY* pointer ;
		typedef int difference_type ;
		typedef PROXY value_type;
		typedef std::random_access_iterator_tag iterator_category ;
		
		const_Proxy_Iterator( ): proxy(){} ;
		const_Proxy_Iterator( const const_Proxy_Iterator& other) : proxy( other.proxy){}
		const_Proxy_Iterator( const PROXY& proxy_ ) : proxy( proxy_ ){} ;
		
		const_Proxy_Iterator& operator=( const const_Proxy_Iterator& other ){
			proxy.import( other.proxy ) ;
			return *this ;
		}
		
		inline const_Proxy_Iterator& operator++(){
			proxy.move(1) ;
			return *this ;
		}
		inline const_Proxy_Iterator operator++(int){
			const_Proxy_Iterator orig(*this) ;
			++(*this) ;
			return orig ;
		}
		
		inline const_Proxy_Iterator& operator--(){
			proxy.move(-1) ;
			return *this ;
		}
		inline const_Proxy_Iterator operator--(int){
			const_Proxy_Iterator orig(*this) ;
			--(*this) ;
			return orig ;
		}
		                    
		inline const_Proxy_Iterator operator+(difference_type n) const {
			return const_Proxy_Iterator( PROXY(*proxy.parent, proxy.index + n) ) ;
		}
		inline const_Proxy_Iterator operator-(difference_type n) const {
			return const_Proxy_Iterator( PROXY(*proxy.parent, proxy.index - n) ) ;
		}
		
		inline const_Proxy_Iterator& operator+=(difference_type n) {
			proxy.move( n ) ;
			return *this ;
		}
		inline const_Proxy_Iterator& operator-=(difference_type n) {
			proxy.move( -n ) ;
			return *this ;
		}

		inline reference operator*() {
			return proxy ;
		}
		inline pointer operator->(){
			return &proxy ;
		}
		
		inline bool operator==( const const_Proxy_Iterator& y) const {
			return ( this->proxy.index == y.proxy.index ) && ( this->proxy.parent == y.proxy.parent );
		}
		inline bool operator!=( const const_Proxy_Iterator& y) const {
			return ( this->proxy.index != y.proxy.index ) || ( this->proxy.parent != y.proxy.parent );
		}
		inline bool operator<( const const_Proxy_Iterator& other ) const {
			return proxy.index < other.proxy.index ;
		}
		inline bool operator>( const const_Proxy_Iterator& other ) const {
			return proxy.index > other.proxy.index ;
		}
		inline bool operator<=( const const_Proxy_Iterator& other ) const {
			return proxy.index <= other.proxy.index ;
		}
		inline bool operator>=( const const_Proxy_Iterator& other ) const {
			return proxy.index >= other.proxy.index ;
		}
		
		inline difference_type operator-(const const_Proxy_Iterator& other) const {
			return proxy.index - other.proxy.index ;
		}

		inline int index() const { return proxy.index ; }

		inline PROXY operator[](int i){ return PROXY(*proxy.parent, proxy.index + i) ; } 
		
private:
	PROXY proxy ;
} ;

}
}

#endif

