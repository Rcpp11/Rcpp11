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

#ifndef Rcpp_api_meat_DottedPairProxy_h
#define Rcpp_api_meat_DottedPairProxy_h

namespace Rcpp{
         
    template <typename CLASS>
    DottedPairProxyPolicy<CLASS>::DottedPairProxy::DottedPairProxy( CLASS& v, int index_ ) : node(R_NilValue){
        if( index_ >= v.length() ) throw index_out_of_bounds() ;
        SEXP x = v ; /* implicit conversion */
        for( int i = 0; i<index_; i++, x = CDR(x) ) {
            x = CDR(x) ;
        }
        node = x ;
    }
     
    template <typename CLASS>
    DottedPairProxyPolicy<CLASS>::DottedPairProxy& DottedPairProxyPolicy<CLASS>::DottedPairProxy::operator=(const DottedPairProxy& rhs){
        return set(rhs) ;
    }
        
    template <typename CLASS>
    DottedPairProxyPolicy<CLASS>::DottedPairProxy& DottedPairProxyPolicy<CLASS>::operator=(SEXP rhs){
        return set(rhs) ;
    }
        
    template <typename CLASS>
    DottedPairProxyPolicy<CLASS>::DottedPairProxy DottedPairProxyPolicy<CLASS>::operator[]( int i) {
        return DottedPairProxy( static_cast<CLASS&>(*this), i ) ;
    }
    
    template <typename CLASS>
    const_DottedPairProxy operator[](int i) const {
        return const_DottedPairProxy( static_cast<const CLASS&>(*this), i ) ;
    }
    
    
}

#endif                                         
