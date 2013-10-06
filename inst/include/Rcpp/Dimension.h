//
// Dimension.h:  dimensions
//
// Copyright (C) 2010 - 2012 Dirk Eddelbuettel and Romain Francois
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

#ifndef Rcpp_Dimension_h
#define Rcpp_Dimension_h

#define R_NO_REMAP
#include <Rinternals.h>
#include <vector>
 
namespace Rcpp{ 

    class Dimension {
    public:
	    typedef std::vector<int>::reference reference ;
	    typedef std::vector<int>::const_reference const_reference ;
	    
	    Dimension(SEXP dims) ;
	    inline Dimension(const size_t& n1) : dims(1){
            dims[0] = n1 ;
        }
	    inline Dimension(const size_t& n1, const size_t& n2) : dims(2){
            dims[0] = n1 ;
            dims[1] = n2 ;
        }
	    inline Dimension(const size_t& n1, const size_t& n2, const size_t& n3) : dims(3){
            dims[0] = n1 ;
            dims[1] = n2 ;
            dims[2] = n3 ;
        }
	    operator SEXP() const ;
	    
	    inline int size() const {
	        return static_cast<int>( dims.size() ) ;
	    }
	    inline int prod() const {
	        return std::accumulate( dims.begin(), dims.end(), 1, std::multiplies<int>() ) ;    
	    }
	    
	    inline reference operator[](int i){
	        return dims.at(i) ;
	    }
	    inline const_reference operator[](int i) const{
	        return dims.at(i) ;    
	    }
	    
    private:
        std::vector<int> dims;
    };

}
#endif
