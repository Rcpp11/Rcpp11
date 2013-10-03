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
    class Language : 
        RCPP_POLICIES(Language), 
        public DottedPairProxyPolicy<Language>, 
        public DottedPairImpl<Language>
    {
    public:
        using Proxy = DottedPairProxy ;
        using const_Proxy = const_DottedPairProxy ;
        
        Language(){}
        
        RCPP_GENERATE_CTOR_ASSIGN(Language) 
	
        /**
         * Attempts to convert the SEXP to a call
         *
         * @throw not_compatible if the SEXP could not be converted
         * to a call using as.call
         */
        Language(SEXP lang){
            set__( r_cast<LANGSXP>(lang) ) ;
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
        explicit Language( const std::string& symbol ){
            set__( Rf_lang1( Rf_install(symbol.c_str()) ) ) ;
        }

        /**
         * Creates a call using the given symbol as the function name
         *
         * @param symbol symbol name to call
         *
         * Language( Symbol("rnorm") ) makes a SEXP similar to this: 
         * > call( "rnorm" )
         */
        explicit Language( const Symbol& symbol ){
            set__( Rf_lang1( symbol ) );    
        }

        /**
         * Creates a call to the function
         * 
         * @param function function to call
         */
        explicit Language( const Function& function) ;
        
        /**
         * Creates a call to the given symbol using variable number of 
         * arguments
         *
         * @param symbol symbol
         * @param ...Args variable length argument list. The type of each 
         *        argument must be wrappable, meaning there need to be 
         *        a wrap function that takes this type as its parameter
         * 
         * For example, Language( "rnorm", 10, 0.0 ) 
         * will create the same call as 
         * > call( "rnorm", 10L, 0.0 )
         *
         * 10 is wrapped as an integer vector using wrap( const& int )
         * 0.0 is wrapped as a numeric vector using wrap( const& double )
         * ...
         */
        template<typename... Args> 
        Language( const std::string& symbol, const Args&... args) {
            set__( pairlist( Rf_install( symbol.c_str() ), args...) ) ;
        }
        template<typename... Args> 
        Language( const Function& function, const Args&... args) {
            set__( pairlist( function, args...) ) ;
        }
        
        /**
         * sets the symbol of the call
         */
        void setSymbol( const std::string& symbol);

        /**
         * sets the symbol of the call
         */
        void setSymbol( const Symbol& symbol ) ;

        /**
         * sets the function
         */
        void setFunction( const Function& function) ;

        /**
         * eval this call in the global environment
         */
        SEXP eval() ;

        /**
         * eval this call in the requested environment
         */
        SEXP eval(SEXP env) ;

        SEXP fast_eval() ;
        SEXP fast_eval(SEXP env ) ;
        
        inline void update(SEXP x){
            SET_TYPEOF( x, LANGSXP ) ;
            SET_TAG( x, R_NilValue ) ;
        }
    };
    
} // namespace Rcpp

#endif
