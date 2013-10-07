// Copyright (C) 2010 - 2013 Dirk Eddelbuettel and Romain Francois
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

#ifndef Rcpp__DataFrame_h
#define Rcpp__DataFrame_h

namespace Rcpp{
        
    template < template <class> class StoragePolicy>
    class DataFrame_Impl : public Vector_Impl<VECSXP, StoragePolicy> {
    public:    
        using Storage = typename Vector_Impl<VECSXP, StoragePolicy>::Storage ;
        DataFrame_Impl() ;
        DataFrame_Impl(SEXP x) ;
        DataFrame_Impl( const DataFrame_Impl& other) ;
                
        template <typename T> DataFrame_Impl( const T& obj) ; 
                
        DataFrame_Impl& operator=( DataFrame_Impl& other) ;
        DataFrame_Impl& operator=( SEXP x)  ;
                
        ~DataFrame_Impl() ;

        int nrows() const ;
        
        template <typename... Args>
        static DataFrame_Impl create(const Args&... args){
            return from_list( List::create( args...) ) ;
        }

    private:
        void set_sexp(SEXP x) ;
        static DataFrame_Impl from_list( Rcpp::List ) ;
        
    } ;
        
}

#endif
