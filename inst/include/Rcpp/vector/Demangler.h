// Copyright (C) 20103 Romain Francois
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

#ifndef Rcpp__vector__Demangler_h
#define Rcpp__vector__Demangler_h

namespace Rcpp{
    
    DEMANGLE_ECHO(Rcpp::DoubleVector) 
    DEMANGLE_ECHO(Rcpp::StringVector) 
    DEMANGLE_ECHO(Rcpp::IntegerVector) 
    DEMANGLE_ECHO(Rcpp::LogicalVector) 
    DEMANGLE_ECHO(Rcpp::ComplexVector) 
    DEMANGLE_ECHO(Rcpp::ExpressionVector) 
    DEMANGLE_ECHO(Rcpp::List) 
    DEMANGLE_ECHO(Rcpp::RawVector)
    
    DEMANGLE_ECHO(Rcpp::DoubleMatrix) 
    DEMANGLE_ECHO(Rcpp::StringMatrix) 
    DEMANGLE_ECHO(Rcpp::IntegerMatrix) 
    DEMANGLE_ECHO(Rcpp::LogicalMatrix) 
    DEMANGLE_ECHO(Rcpp::ComplexMatrix) 
    DEMANGLE_ECHO(Rcpp::ExpressionMatrix) 
    DEMANGLE_ECHO(Rcpp::GenericMatrix) 
    DEMANGLE_ECHO(Rcpp::RawMatrix)
    
}
#endif
