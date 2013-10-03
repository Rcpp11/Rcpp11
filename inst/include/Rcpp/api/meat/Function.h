// Copyright (C) 2013    Romain Francois
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

#ifndef Rcpp_api_meat_Function_h
#define Rcpp_api_meat_Function_h

namespace Rcpp{ 

    template < template <class> class StoragePolicy>
    template<typename... Args> 
    SEXP Function_Impl<StoragePolicy>::operator()( const Args&... args) const {
        RCPP_DEBUG( "Function::operator(...) nargs = %d", sizeof...(args)  )
        typedef typename std::tuple<Args...> Tuple ;
        RCPP_DEBUG( "tuple = %s", DEMANGLE(Tuple) )
        Language call( Storage::get__() , args... );
        return call.eval() ;
    }
        
	
    template < template <class> class StoragePolicy>
    Function_Impl<StoragePolicy>::Function_Impl(SEXP x) {
        RCPP_DEBUG( "Function::Function(SEXP = <%p>)", x)
        switch( TYPEOF(x) ){
        case CLOSXP:
        case SPECIALSXP:
        case BUILTINSXP:
            Storage::set__(x) ;
            break; 
        default:
            throw not_compatible("cannot convert to function") ;
        }
    }
	
    template < template <class> class StoragePolicy>
    Function_Impl<StoragePolicy>::Function_Impl(const std::string& name) {
        SEXP nameSym = Rf_install( name.c_str() );	
        Storage::set__( Rf_findFun( nameSym, R_GlobalEnv ) ) ;
    }
	
    template < template <class> class StoragePolicy>
    SEXP Function_Impl<StoragePolicy>::environment() const {
        if( TYPEOF(Storage::get__()) != CLOSXP ) {
            throw not_a_closure() ;
        }
        return CLOENV(Storage::get__()) ;
    }
	
    template < template <class> class StoragePolicy>
    SEXP Function_Impl<StoragePolicy>::body() const {
        return BODY( Storage::get__() ) ;
    }

    
} // namespace Rcpp

#endif
