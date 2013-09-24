//
// rep_each.h:  rep_each
//
// Copyright (C) 2010 - 2011 Dirk Eddelbuettel and Romain Francois
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

#ifndef Rcpp__sugar__rep_each_h
#define Rcpp__sugar__rep_each_h

namespace Rcpp{
namespace sugar{

template <int RTYPE, bool NA, typename T>
class Rep_each : public Rcpp::VectorBase< RTYPE ,NA, Rep_each<RTYPE,NA,T> > {
public:
	typedef typename Rcpp::VectorBase<RTYPE,NA,T> VEC_TYPE ;
	typedef typename Rcpp::traits::storage_type<RTYPE>::type STORAGE ;

	Rep_each( const VEC_TYPE& object_, int times_ ) : 
		object(object_), times(times_), n(object.size()) {}

	inline STORAGE operator[]( int i ) const {
		return object[ i / times ] ;
	}
	inline int size() const { return n * times ; }

private:
	const VEC_TYPE& object ;
	int times; 
	int n ;
} ;

} // sugar

template <int RTYPE, bool NA, typename T>
inline sugar::Rep_each<RTYPE,NA,T> rep_each( const VectorBase<RTYPE,NA,T>& t, int times ){
	return sugar::Rep_each<RTYPE,NA,T>( t, times ) ;
}


} // Rcpp
#endif

