// Copyright (C) 2010 - 2012  Dirk Eddelbuettel and Romain Francois
// Copyright (C) 2013  Romain Francois
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

#ifndef Rcpp_Function_h
#define Rcpp_Function_h

namespace Rcpp{ 

    template < template <class> class StoragePolicy, bool fast > class Function_Impl : 
        public StoragePolicy<Function_Impl<StoragePolicy, fast>>,      
        public SlotProxyPolicy<Function_Impl<StoragePolicy, fast>>,    
        public AttributeProxyPolicy<Function_Impl<StoragePolicy, fast>>
    {
    public:

        RCPP_GENERATE_CTOR_ASSIGN(Function_Impl) 
	
        /**
         * Attempts to convert the SEXP to a pair list
         *
         * @throw not_compatible if the SEXP could not be converted
         * to a pair list using as.pairlist
         */
        Function_Impl(SEXP lang = R_NilValue) ;
        
        /**
         * Finds a function, searching from the global environment
         *
         * @param name name of the function
         */
        Function_Impl(const std::string& name) ;
       
        /**
         * calls the function with the specified arguments
         *
         * @param ...Args variable length argument list. The type of each 
         *        argument must be wrappable, meaning there need to be 
         *        a wrap function that takes this type as its parameter
         *
         */
        template<typename... Args> 
        SEXP operator()( const Args&... args) const ;
        
        /**
         * Returns the environment of this function
         */
        SEXP environment() const ;
        
        /**
         * Returns the body of the function
         */
        SEXP body() const ;
        void update(SEXP){}
    };

} // namespace Rcpp

#endif
