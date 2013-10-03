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

#ifndef Rcpp_Promise_h
#define Rcpp_Promise_h

namespace Rcpp{ 
    
    RCPP_API_CLASS(Promise_Impl) {     
    public:
        RCPP_GENERATE_CTOR_ASSIGN__(Promise_Impl) 
	
        Promise_Impl( SEXP x){
            if( TYPEOF(x) != PROMSXP )
                throw not_compatible("not a promise") ;
            Storage::set__(x) ;    
        }
        
        /** 
         * Return the result of the PRSEEN macro
         */
        int seen() const {
            return PRSEEN(Storage::get__());
        }
        
        /**
         * Return the result of the PRVALUE macro on the promise
         */
        SEXP value() const{
            SEXP val = PRVALUE(Storage::get__()) ; 
            if( val == R_UnboundValue ) throw unevaluated_promise() ;
            return val ;    
        }

        bool was_evaluated() const{
            return PRVALUE(Storage::get__()) != R_UnboundValue ;    
        }
        
        /**
         * The promise expression: PRCODE
         */
        ExpressionVector expression() const  ;

        /**
         * The promise environment : PRENV
         */
        Environment_Impl<StoragePolicy> environment() const ;
        void update(SEXP){}
        
    } ;

} // namespace

#endif
