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

#ifndef Rcpp__Array__h
#define Rcpp__Array__h

namespace Rcpp{
    
    template <int N, int RTYPE>
    class Array {
    public:
        using Vec = Vector<RTYPE>;
        using Proxy = typename Vec::Proxy; 
        using const_Proxy = typename Vec::Proxy; 
        
        template <
            typename... Args, 
            typename = typename std::enable_if< ValidIndexArgs<N,Args...>() >::type 
        >
        Array( Args... args ) : 
            index({ static_cast<size_t>(args)... }), 
            data(index.prod())
        {
            data.attr("dim") = index ;    
        }
    
        template < 
            typename... Args, 
            typename = typename std::enable_if< ValidIndexArgs<N,Args...>() >::type
        >
        Proxy operator()( Args&&... args){
            return data[ index( std::forward<Args>(args)... ) ];    
        }
        
        template < 
            typename... Args, 
            typename = typename std::enable_if< ValidIndexArgs<N,Args...>() >::type
        >
        const_Proxy operator()( Args... args) const {
            return data[ index.get_index( args... ) ];    
        }
        
        inline operator SEXP() const { return data ; }
        inline operator SEXP(){ return data ; }
        
    private:
        Index<N> index ;
        Vector<RTYPE> data ;
    } ;
    
    
    template <int N> using NumericArray   = Array<N, REALSXP> ;
    template <int N> using DoubleArray    = Array<N, REALSXP> ;
    template <int N> using IntegerArray   = Array<N, INTSXP> ;
    template <int N> using StringArray    = Array<N, STRSXP> ;
    template <int N> using CharacterArray = Array<N, STRSXP> ;
    template <int N> using LogicalArray   = Array<N, LGLSXP> ;
    template <int N> using RawArray       = Array<N, RAWSXP> ;
    template <int N> using ComplexArray   = Array<N, CPLXSXP> ;
    
} // Rcpp 

#endif
