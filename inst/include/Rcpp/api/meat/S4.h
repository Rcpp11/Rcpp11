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

#ifndef Rcpp_api_meat_S4_h
#define Rcpp_api_meat_S4_h

namespace Rcpp{

    template < template <class> class StoragePolicy>
    template <typename T>
    S4_Impl<StoragePolicy>::S4_Impl( const T& object ) : S4(wrap(object)){}
       
    template < template <class> class StoragePolicy>
    bool S4_Impl<StoragePolicy>::is( const std::string& clazz ) {
        CharacterVector cl = static_cast<AttributePolicy&>(*this).attr("class");
                
        // simple test for exact match
        if( ! clazz.compare( cl[0] ) ) return true ;
                
        try{
            SEXP containsSym = Rf_install("contains");
            CharacterVector res( Rf_getAttrib(
                R_do_slot(R_getClassDef(CHAR(Rf_asChar(as<SEXP>(cl)))),containsSym),
                R_NamesSymbol
            ));
            return std::any_of( 
                res.begin(), res.end(), 
                [&](String s){ return s == clazz.c_str() ; } 
            ) ;
        } catch( ... ){
            // we catch eval_error and also not_compatible when 
            // contains is NULL
        }
        return false ;
    }
    
    
}
#endif
