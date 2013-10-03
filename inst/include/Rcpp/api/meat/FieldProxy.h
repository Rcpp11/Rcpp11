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

#ifndef Rcpp_api_meat_FieldProxy_h
#define Rcpp_api_meat_FieldProxy_h

namespace Rcpp{

    template <typename CLASS>
    typename FieldProxyPolicy<CLASS>::FieldProxy& FieldProxyPolicy<CLASS>::FieldProxy::operator=( const FieldProxy& rhs ){
        set( rhs.get() ) ;
        return *this ;    
    }
    
    template <typename CLASS>
    SEXP FieldProxyPolicy<CLASS>::FieldProxy::get() const {
        SEXP call = PROTECT( Rf_lang3( 
            R_DollarSymbol, 
            parent, 
            Rf_ScalarString(field_name)
        ) ) ;
        UNPROTECT(1) ;
        return Rcpp::internal::try_catch( call ) ;    
    }
    
    template <typename CLASS>
    void FieldProxyPolicy<CLASS>::FieldProxy::set( SEXP x) {
        PROTECT(x);
        SEXP dollarGetsSym = Rf_install( "$<-");
        SEXP name = PROTECT( Rf_ScalarString( field_name ) ) ;
        SEXP call = PROTECT( Rf_lang4( 
            dollarGetsSym,
            parent, 
            name , 
            x
            ) ) ;
        parent = Rf_eval( call, R_GlobalEnv ) ; 
        UNPROTECT(3) ;
    }

    template <typename CLASS>
    typename FieldProxyPolicy<CLASS>::FieldProxy FieldProxyPolicy<CLASS>::field(const std::string& name) {
        return FieldProxy( static_cast<CLASS&>(*this) , name ) ;
    }
 
    template <typename CLASS>
    template <typename T> 
    typename FieldProxyPolicy<CLASS>::FieldProxy& FieldProxyPolicy<CLASS>::FieldProxy::operator=( const T& rhs ){
        set( wrap( rhs ) ) ;
        return *this ;
    }
    
    template <typename CLASS>
    template <typename T>
    FieldProxyPolicy<CLASS>::FieldProxy::operator T() const {
        return as<T>(get()) ;    
    }

    
    
    template <typename CLASS>
    FieldProxyPolicy<CLASS>::const_FieldProxy::const_FieldProxy( const CLASS& v, const std::string& name) 
        : parent(v), field_name(Rf_mkChar(name.c_str())){}

    template <typename CLASS>
    SEXP FieldProxyPolicy<CLASS>::const_FieldProxy::get() const {
        SEXP call = PROTECT( Rf_lang3( 
            R_DollarSymbol, 
            parent, 
            Rf_ScalarString(field_name) 
        ) ) ;
        UNPROTECT(1) ;
        return Rcpp::internal::try_catch( call ) ;    
    }
    
    template <typename CLASS>
    typename FieldProxyPolicy<CLASS>::const_FieldProxy FieldProxyPolicy<CLASS>::field(const std::string& name) const {
        SEXP x = static_cast<const CLASS&>(*this) ;
        if( !Rf_isS4(x) ) throw not_s4() ;
        return const_FieldProxy( static_cast<const CLASS&>(*this) , name ) ;
    }

    
}
#endif
