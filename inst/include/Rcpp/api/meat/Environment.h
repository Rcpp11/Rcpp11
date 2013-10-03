//
// Environment.h:  
//
// Copyright (C) 2012    Dirk Eddelbuettel and Romain Francois
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

#ifndef Rcpp_api_meat_Environment_h
#define Rcpp_api_meat_Environment_h

namespace Rcpp{ 

    template < template <class> class StoragePolicy>
    Environment_Impl<StoragePolicy>::Environment_Impl(SEXP x){
        Storage::set__(x) ;
        RCPP_DEBUG( "Environment::Environment( SEXP = %p)", x ) ;
        if( ! Rf_isEnvironment(x) ) {
            /* not an environment, but maybe convertible to one using as.environment, try that */
            SEXP res ;
            try {
                SEXP asEnvironmentSym = Rf_install("as.environment"); 
                res = Evaluator::run( Rf_lang2(asEnvironmentSym, x ) ) ;
            } catch( const eval_error& ex){
                throw not_compatible( "cannot convert to environment"  ) ; 
            }
            Storage::set__( res ) ;
        }    
    }
     
    template < template <class> class StoragePolicy>
    Environment_Impl<StoragePolicy>::Environment_Impl(const std::string& name ){
        Storage::set__(R_EmptyEnv) ;
        /* similar to matchEnvir@envir.c */
        if( name == ".GlobalEnv" ) {
            Storage::set__( R_GlobalEnv ) ;
        } else if( name == "package:base" ){
            Storage::set__( R_BaseEnv ) ;
        } else{
            SEXP res = R_NilValue ;
            try{
                SEXP asEnvironmentSym = Rf_install("as.environment"); 
                res = Evaluator::run(Rf_lang2( asEnvironmentSym, Rf_mkString(name.c_str()) ) ) ;
            } catch( const eval_error& ex){
                throw no_such_env(name) ;
            }
            Storage::set__( res ) ;
        }
    }
    
    template < template <class> class StoragePolicy>
    Environment_Impl<StoragePolicy>::Environment_Impl(int pos ){
        Storage::set__( R_GlobalEnv) ;
        SEXP res ;
        try{
            SEXP asEnvironmentSym = Rf_install("as.environment"); 
            res =  Evaluator::run( Rf_lang2( asEnvironmentSym, Rf_ScalarInteger(pos) ) ) ;
        } catch( const eval_error& ex){
            throw no_such_env(pos) ;
        }
        Storage::set__( res ) ;
    
    }
      
    template < template <class> class StoragePolicy>
    Environment_Impl<StoragePolicy> Environment_Impl<StoragePolicy>::namespace_env(const std::string& package ){
        SEXP env = R_NilValue ;
        try{
            SEXP getNamespaceSym = Rf_install("getNamespace");
            env = Evaluator::run( Rf_lang2(getNamespaceSym, Rf_mkString(package.c_str()) ) ) ;
        } catch( const eval_error& ex){
            throw no_such_namespace( package  ) ; 
        }
        return Environment( env ) ;
    }
    
    template < template <class> class StoragePolicy>
    Environment_Impl<StoragePolicy> Environment_Impl<StoragePolicy>::new_child(bool hashed){
        SEXP newEnvSym = Rf_install("new.env");
        return Environment( Evaluator::run(Rf_lang3( newEnvSym, Rf_ScalarLogical(hashed), Storage::get__() )) );
    }
        
    
    
    template < template <class> class StoragePolicy>
    template <typename WRAPPABLE>
    bool Environment_Impl<StoragePolicy>::assign( const std::string& name, const WRAPPABLE& x) const {
        return assign( name, wrap( x ) ) ;
    }
    
    template < template <class> class StoragePolicy>
    template <typename T> 
    Environment_Impl<StoragePolicy>::Binding::operator T() const{
        SEXP x = env.get(name) ;
        return as<T>(x) ;
    }  
        
    template < template <class> class StoragePolicy>
    template <typename WRAPPABLE>
    typename Environment_Impl<StoragePolicy>::Binding& Environment_Impl<StoragePolicy>::Binding::operator=(const WRAPPABLE& rhs){
        env.assign( name, rhs ) ;
        return *this ;
    }
    
} // namespace Rcpp

#endif
