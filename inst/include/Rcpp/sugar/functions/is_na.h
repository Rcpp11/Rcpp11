//
// is_na.h:  is_na
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

#ifndef Rcpp__sugar__is_na_h
#define Rcpp__sugar__is_na_h

namespace Rcpp{
namespace sugar{

template <int RTYPE, bool NA, typename VEC_TYPE>
class IsNa : public ::Rcpp::VectorBase< LGLSXP, false, IsNa<RTYPE,NA,VEC_TYPE> > {
public:
	typedef typename traits::storage_type<RTYPE>::type STORAGE ;
	typedef Rcpp::VectorBase<RTYPE,NA,VEC_TYPE> BASE ;
	
	IsNa( const BASE& obj_) : obj(obj_){}
	
	inline int operator[]( int i ) const {
		return ::Rcpp::traits::is_na<RTYPE>( obj[i] ) ;
	}
	
	inline int size() const { return obj.size() ; }
	         
private:
	const BASE& obj ;
	
} ;
      
// specialization for the case where we already know
// the result (FALSE) because it is embedded in the type
// (the second template parameter of VectorBase)
template <int RTYPE, typename VEC_TYPE>
class IsNa<RTYPE,false,VEC_TYPE> : public ::Rcpp::VectorBase< LGLSXP, false, IsNa<RTYPE,false,VEC_TYPE> > {
public:
	typedef typename traits::storage_type<RTYPE>::type STORAGE ;
	typedef Rcpp::VectorBase<RTYPE,false,VEC_TYPE> BASE ;
	
	IsNa( const BASE& obj_) : obj(obj_){}
	
	inline int operator[]( int i ) const {
		return FALSE ;
	}
	
	inline int size() const { return obj.size() ; }
	
private:
	const BASE& obj ;
	
} ;

template <typename T>
class IsNa_Vector_is_na : public Rcpp::VectorBase<LGLSXP, false, IsNa_Vector_is_na<T> >{
   public:
       IsNa_Vector_is_na( const T& x) : ref(x){}
       
       inline int operator[]( int i) const {
           return ref[i].is_na() ;
       }
       
       inline int size() const { return ref.size() ; } 
       
   private:
        const T& ref ;       
} ;

} // sugar

template <int RTYPE, bool NA, typename T>
inline sugar::IsNa<RTYPE,NA,T> is_na( const Rcpp::VectorBase<RTYPE,NA,T>& t){
	return sugar::IsNa<RTYPE,NA,T>( t ) ;
}

} // Rcpp
#endif

