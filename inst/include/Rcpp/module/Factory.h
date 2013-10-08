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

#ifndef Rcpp_Module_Factory_h
#define Rcpp_Module_Factory_h
   
template <typename Class>
class Factory_Base {
public:
    virtual Class* get_new( SEXP* args, int nargs ) = 0 ;
    virtual int nargs() = 0 ;
    virtual void signature(std::string& s, const std::string& class_name) = 0 ;
} ;

template <typename Class, typename... Args>
class Factory_Impl : public Factory_Base<Class>{
    public: 
        typedef Class* (*Fun)(Args...) ;  
        
        Factory_Impl( Fun fun_ ) : fun(fun_){}
        virtual Class* get_new( SEXP* args, int /* nargs */ ){
            return FactoryInvoker<Class,Args...>( fun, args).invoke() ;
        }
        virtual int nargs(){ return sizeof...(Args) ; }
        virtual void signature(std::string& s, const std::string& class_name ){
            ctor_signature<Args...>(s, class_name) ;
        }
    private:
        Fun fun ;
} ;        

template <typename Class, typename... Args>
class Debug_Factory_Impl : public Factory_Base<Class>{
    public: 
        typedef Class* (*Fun)(Args...) ;  
        
        Debug_Factory_Impl( Fun fun_ ) : fun(fun_){}
        virtual Class* get_new( SEXP* args, int /* nargs */ ){
            debug_constructor<Class,Debug_Factory_Impl,Args...>(*this) ;  
            Class *obj = FactoryInvoker<Class,Args...>( fun, args).invoke() ;
            Rprintf( "  object = <%p>\n", obj ) ;
            return obj ;
        }
        virtual int nargs(){ return sizeof...(Args) ; }
        virtual void signature(std::string& s, const std::string& class_name ){
            ctor_signature<Args...>(s, class_name) ;
        }
    private:
        Fun fun ;
} ;        

#endif
