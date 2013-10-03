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

#ifndef Rcpp_Reference_h
#define Rcpp_Reference_h                     

#include <Rcpp/S4.h>
#include <Rcpp/exceptions.h>

namespace Rcpp{ 

    template < template <class> class StoragePolicy > 
    class Reference_Impl : 
        public S4_Impl<StoragePolicy>, 
        public FieldProxyPolicy<Reference_Impl<StoragePolicy>>
    {
    public:
        using Base    = S4_Impl<StoragePolicy> ;
        using Storage = typename Base::Storage ;
        
        /**
         * checks that x is an S4 object of a reference class and wrap it.
         *
         * @param x must be an S4 object of some reference class
         */
        Reference_Impl(SEXP x) : Base(x){}
        
        template <typename T>
        Reference_Impl(const T& object ) ;
        
        Reference_Impl& operator=( SEXP other ) {
            Storage::set__( other ) ;
            return *this ;
        }
        
        /**
         * Creates an reference object of the requested class. 
         *
         * @param klass name of the target reference class
         * @throw reference_creation_error if klass does not map to a known S4 class
         */
        Reference_Impl( const std::string& klass ){
            // using callback to R as apparently R_do_new_object always makes the same environment
            SEXP newSym = Rf_install("new");
            Scoped<SEXP> call = Rf_lang2( newSym, Rf_mkString( klass.c_str() ) ) ;
            Storage::set__( Rcpp::internal::try_catch( call ) ) ;
        
        }
        Reference_Impl( const char* klass ) : Reference(std::string(klass)){};
       
    } ;

} // namespace Rcpp

#endif
