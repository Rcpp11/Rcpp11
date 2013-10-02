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

#ifndef Rcpp_api_meat_RObjectStorage_h
#define Rcpp_api_meat_RObjectStorage_h

namespace Rcpp{ 
 
    template <typename CLASS>
    CharacterVector RObjectStorage<CLASS>::attributeNames() const {
        SEXP attrs = ATTRIB(data);
        CharacterVector v( Rf_length( attrs ) ) ; ;
        for( int i=0; attrs != R_NilValue; i++, attrs=CDR(attrs) ){
            v[i] = PRINTNAME(TAG(attrs)) ;
        }
        return v ;
    }    
    
    template <typename CLASS>
    bool RObjectStorage<CLASS>::hasAttribute( const std::string& attr) const {
        SEXP attrs = ATTRIB(data);
        while( attrs != R_NilValue ){
            if( attr == CHAR(PRINTNAME(TAG(attrs))) ){
                return true ;
            }
            attrs = CDR( attrs ) ;
        }
        return false;
    }
    
    template <typename CLASS>
    bool RObjectStorage<CLASS>::hasSlot(const std::string& name) const {
        if( !Rf_isS4(data) ) throw not_s4() ;
        return R_has_slot( data, Rf_mkString(name.c_str()) ) ;
    }
    
    
}

#endif
