// Copyright (C) 2012 Dirk Eddelbuettel and Romain Francois
// Copyright (C) 2014 Romain Francois

#ifndef Rcpp_api_meat_Environment_h
#define Rcpp_api_meat_Environment_h

namespace Rcpp{ 

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
                res = Rcpp_eval(Rf_lang2( asEnvironmentSym, Rf_mkString(name.c_str()) ) ) ;
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
            res =  Rcpp_eval( Rf_lang2( asEnvironmentSym, Rf_ScalarInteger(pos) ) ) ;
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
            env = Rcpp_eval( Rf_lang2(getNamespaceSym, Rf_mkString(package.c_str()) ) ) ;
        } catch( const eval_error& ex){
            throw no_such_namespace( package  ) ; 
        }
        return Environment( env ) ;
    }
    
    template < template <class> class StoragePolicy>
    Environment_Impl<StoragePolicy> Environment_Impl<StoragePolicy>::new_child(bool hashed){
        SEXP newEnvSym = Rf_install("new.env");
        return Environment( Rcpp_eval(Rf_lang3( newEnvSym, Rf_ScalarLogical(hashed), Storage::get__() )) );
    }
        
    template < template <class> class StoragePolicy>
    template <typename WRAPPABLE>
    bool Environment_Impl<StoragePolicy>::assign( const std::string& name, const WRAPPABLE& x) const {
        return assign( name, wrap( x ) ) ;
    }
    
    
} // namespace Rcpp

#endif
