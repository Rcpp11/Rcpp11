//
// DottedPair.h:   DottedPair meat
//
// Copyright (C) 2012 - 2013    Dirk Eddelbuettel and Romain Francois
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
                    
#ifndef Rcpp_api_meat_DottedPair_h
#define Rcpp_api_meat_DottedPair_h

namespace Rcpp{ 

    template <typename CLASS>
    template <typename T>
    void DottedPairImpl<CLASS>::push_front( const T& object){
       set__( grow(object, CLASS::get__() ) ) ;
    }

    template <typename CLASS>
    template <typename T>
    void DottedPairImpl<CLASS>::push_back( const T& object){
        if( CLASS::isNULL() ){
            CLASS::set__( grow( object, CLASS::get__() ) ) ;
        } else {
            SEXP x = CLASS::get__() ;
            /* traverse the pairlist */
            while( !Rf_isNull(CDR(x)) ){
                x = CDR(x) ;
            }
            SEXP tail = PROTECT( pairlist( object ) ); 
            SETCDR( x, tail ) ;
            UNPROTECT(1) ;
        }
	}

    template <typename CLASS>
    template <typename T>
	void DottedPairImpl<CLASS>::insert( const size_t& index, const T& object) {
		if( index == 0 ) {
			push_front( object ) ;
		} else {
			if( CLASS::isNULL( ) ) throw index_out_of_bounds() ;
			
			if( static_cast<R_len_t>(index) > ::Rf_length(CLASS::get__()) ) throw index_out_of_bounds() ;
			
			size_t i=1;
			SEXP x = CLASS::get__() ;
			while( i < index ){
				x = CDR(x) ;
				i++; 
			}
			SEXP tail = PROTECT( grow( object, CDR(x) ) ) ; 
			SETCDR( x, tail ) ;
			UNPROTECT(1) ;
		}
	}
	
	template <typename CLASS>
    template <typename T>
	void DottedPairImpl<CLASS>::replace( const int& index, const T& object ) {
	    if( static_cast<R_len_t>(index) >= ::Rf_length(CLASS::get__()) ) throw index_out_of_bounds() ;
		
        /* pretend we do a pairlist so that we get Named to work for us */
        SEXP x = PROTECT(pairlist( object ));
        SEXP y = CLASS::get__() ;
        int i=0;
        while( i<index ){ y = CDR(y) ; i++; }
        
        SETCAR( y, CAR(x) );
        SET_TAG( y, TAG(x) );
        UNPROTECT(1) ;
	}

	
} // namespace Rcpp

#endif
