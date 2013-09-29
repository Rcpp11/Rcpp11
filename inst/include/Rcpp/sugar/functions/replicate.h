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

#ifndef Rcpp__sugar__replicate_h
#define Rcpp__sugar__replicate_h

namespace Rcpp{
namespace sugar{

    template <typename OUT, typename CallType >
    class Replicate : public Rcpp::VectorBase< Rcpp::traits::r_sexptype_traits<OUT>::rtype , true, Replicate<OUT,CallType> > {
    public:
        Replicate( size_t n_, const CallType& call_ ): n(n_), call(call_) {}
        
        inline OUT operator[]( int i ) const {
            return call ;
        }
        inline int size() const { return n ; }
        
    private:
        size_t n ;
        const CallType& call ; 
    } ;


} // sugar

template <typename OUT, typename CallType>
inline sugar::Replicate<OUT, CallType> 
replicate( size_t n, const CallType& call){
    return sugar::Replicate<OUT, CallType>( n, call ) ;    
}



} // Rcpp
#endif

