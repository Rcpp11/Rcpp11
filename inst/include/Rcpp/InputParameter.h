//
// InputParameter.h:  
//
// Copyright (C) 2013    Dirk Eddelbuettel and Romain Francois
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

#ifndef Rcpp__InputParameter__h
#define Rcpp__InputParameter__h

namespace Rcpp { 
    
    // default implementation used for pass by value and modules objects
    // as<> is called on the conversion operator
    template <typename T>
    class InputParameter {
    public:
        typedef T type ;
        InputParameter(SEXP x_) : x(x_){}
        InputParameter() : x(R_NilValue){}
        
        void set(SEXP x_){ x = x_ ; }
        inline operator T() { return as<T>(x) ; }
        inline T get() { return as<T>(x) ; }
        
        SEXP x ;
    } ;
    
    // same for const
    template <typename T>
    class ConstInputParameter {
    public:
        typedef const T const_nonref ;
        ConstInputParameter(SEXP x_) : x(x_) {}
        
        inline void set(SEXP x_){ x = x_; }
        inline operator const_nonref() { return get() ; }
        inline const_nonref get() { return as<T>(x) ; }
        
        SEXP x ;
    } ;
    
    
    // impl for references. It holds an object at the constructor and then 
    // returns a reference in the reference operator
    template <typename T>
    class ReferenceInputParameter {
    public:
        typedef T& reference ;
        ReferenceInputParameter() : x(R_NilValue), obj(){}
        ReferenceInputParameter(SEXP x_) : x(x_), obj( as<T>(x_) ) {}
        
        void set(SEXP x_){ x = x_ ; obj = as<T>(x); }
        inline operator reference() { return get() ; }
        inline reference get(){ return obj; } 
    
        SEXP x ;
        T obj ; 
    } ;

    // same for const references
    template <typename T>
    class ConstReferenceInputParameter {
    public:
        typedef const T& const_reference ;
        ConstReferenceInputParameter(SEXP x_) : x(x_), obj( as<T>(x_) ){}
        ConstReferenceInputParameter(): x(R_NilValue),obj(){}
        inline operator const_reference() { return obj ; }
        void set(SEXP x_){ x = x_ ; obj = as<T>(x); }
        
    private:
        SEXP x ;
        T obj ;
    } ;
    
    namespace traits{
        template <typename T>
        struct input_parameter {
            typedef typename Rcpp::InputParameter<T> type ;
        } ;
        template <typename T>
        struct input_parameter<T&> {
            typedef typename Rcpp::ReferenceInputParameter<T> type ;
        } ;
        template <typename T>
        struct input_parameter<const T> {
            typedef typename Rcpp::ConstInputParameter<T> type ;
        } ;
        template <typename T>
        struct input_parameter<const T&> {
            typedef typename Rcpp::ConstReferenceInputParameter<T> type ;
        } ;
    }    
    
}

#endif
