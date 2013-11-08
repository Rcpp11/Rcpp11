// Copyright (C) 2010 - 2011 Dirk Eddelbuettel and Romain Francois
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

#ifndef Rcpp_Language_h
#define Rcpp_Language_h

namespace Rcpp{ 

    /** 
     * C++ wrapper around calls (LANGSXP SEXP)
     *
     * This represents calls that can be evaluated
     */
    RCPP_API_CLASS(Language_Impl)
        , public DottedPairProxyPolicy<Language_Impl<StoragePolicy>>, 
        public DottedPairImpl<Language_Impl<StoragePolicy>>
    {
    public:
        using Proxy = typename DottedPairProxyPolicy<Language_Impl<StoragePolicy>>::DottedPairProxy ;
        using const_Proxy = typename DottedPairProxyPolicy<Language_Impl<StoragePolicy>>::const_DottedPairProxy ;
        
        RCPP_GENERATE_CTOR_ASSIGN(Language_Impl) 
	
        Language_Impl(){}
        
        
        /**
         * Attempts to convert the SEXP to a call
         *
         * @throw not_compatible if the SEXP could not be converted
         * to a call using as.call
         */
        Language_Impl(SEXP lang){
            Storage::set__( r_cast<LANGSXP>(lang) ) ;
        }
        
        /**
         * Creates a call using the given symbol as the function name
         *
         * @param symbol symbol name to call
         *
         * Language( "rnorm" ) makes a SEXP similar to this (expressed in R)
         * > as.call( as.list( as.name( "rnorm") ) )
         * > call( "rnorm" )
         */
        explicit Language_Impl( const std::string& symbol ){
            Storage::set__( Rf_lang1( Rf_install(symbol.c_str()) ) ) ;
        }

        /**
         * Creates a call using the given symbol as the function name
         *
         * @param symbol symbol name to call
         *
         * Language( Symbol("rnorm") ) makes a SEXP similar to this: 
         * > call( "rnorm" )
         */
        explicit Language_Impl( const Symbol& symbol ){
            Storage::set__( Rf_lang1( symbol ) );    
        }

        /**
         * Creates a call to the function
         * 
         * @param function function to call
         */
        explicit Language_Impl( const Function& function) ;
        
        template<typename... Args> 
        Language_Impl( const std::string& symbol, const Args&... args) {
            Storage::set__( pairlist( Rf_install( symbol.c_str() ), args...) ) ;
        }
        template<typename... Args> 
        Language_Impl( const Function& function, const Args&... args) {
            Storage::set__( pairlist( function, args...) ) ;
        }
        
        /**
         * sets the symbol of the call
         */
        void setSymbol( const std::string& symbol){
            setSymbol( Symbol( symbol ) ) ;    
        }

        /**
         * sets the symbol of the call
         */
        void setSymbol( const Symbol& symbol ){
            SEXP data = Storage::get__() ;
            SETCAR( data, symbol ) ;
            SET_TAG(data, R_NilValue);  
        }

        /**
         * sets the function
         */
        void setFunction( const Function& function) ;

        /**
         * eval this call in the global environment
         */
        SEXP eval() const {
            return eval( R_GlobalEnv ) ;    
        }

        /**
         * eval this call in the requested environment
         */
        SEXP eval(SEXP env) const {
            return Rcpp_eval( Storage::get__(), env ) ;
        }

        SEXP fast_eval() const {
            return Rf_eval( Storage::get__(), R_GlobalEnv ) ;    
        }
        SEXP fast_eval(SEXP env ) const {
            return Rf_eval( Storage::get__(), env ) ;    
        }
        
        inline void update(SEXP x){
            SET_TYPEOF( x, LANGSXP ) ;
            SET_TAG( x, R_NilValue ) ;
        }
    };
    
} // namespace Rcpp

#endif
