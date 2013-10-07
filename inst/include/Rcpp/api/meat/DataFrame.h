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

#ifndef Rcpp_api_meat_DataFrame_h
#define Rcpp_api_meat_DataFrame_h

namespace Rcpp{ 

    namespace internal{
        inline SEXP empty_data_frame(){
            SEXP dataFrameSym = ::Rf_install( "data.frame");
            return ::Rf_eval( ::Rf_lang1( dataFrameSym ), R_GlobalEnv ) ;       
        }
    }
    
    template <template <class> class StoragePolicy> 
    template <typename T> 
    DataFrame_Impl<StoragePolicy>::DataFrame_Impl( const T& obj) : DataFrame_Impl( wrap(obj) ) {} 
    
    template <template <class> class StoragePolicy>         
    DataFrame_Impl<StoragePolicy>::DataFrame_Impl(): List( internal::empty_data_frame() ){}
    
    template <template <class> class StoragePolicy>
    DataFrame_Impl<StoragePolicy>::DataFrame_Impl(SEXP x) {
        set_sexp(x) ;
    }  
    
    template <template <class> class StoragePolicy>
    DataFrame_Impl<StoragePolicy>::DataFrame_Impl( const DataFrame_Impl& other): List(other.get__()) {}
    
    template <template <class> class StoragePolicy>
    DataFrame_Impl<StoragePolicy>& DataFrame_Impl<StoragePolicy>::operator=( DataFrame_Impl& other) {
        Storage::set__( other.get__() ) ;
        return *this ;
    }
            
    template <template <class> class StoragePolicy>
    DataFrame_Impl<StoragePolicy>& DataFrame_Impl<StoragePolicy>::operator=( SEXP x) {
        Storage::set__(x) ;
        return *this ;
    }
    
    template <template <class> class StoragePolicy>
    DataFrame_Impl<StoragePolicy>::~DataFrame_Impl(){}     
    
    template <template <class> class StoragePolicy>
    void DataFrame_Impl<StoragePolicy>::set_sexp(SEXP x) {
        if( ::Rf_inherits( x, "data.frame" )){
            Storage::set__( x ) ;
        } else{
            SEXP y = internal::convert_using_rfunction( x, "as.data.frame" ) ;
            Storage::set__( y ) ;
            x = y ;
        }
    } 
    template <template <class> class StoragePolicy>
    int DataFrame_Impl<StoragePolicy>::nrows() const { 
        return Rf_length( VECTOR_ELT(Storage::get__(), 0) );
    }
        
    template <template <class> class StoragePolicy>
    DataFrame_Impl<StoragePolicy> DataFrame_Impl<StoragePolicy>::from_list( List obj ){
        bool use_default_strings_as_factors = true ;
        bool strings_as_factors = true ;
        int strings_as_factors_index = -1 ;
        int n = obj.size() ;
        CharacterVector names = obj.attr( "names" ) ;
        if( !names.isNULL() ){
            for( int i=0; i<n; i++){
                if( names[i] == "stringsAsFactors" ){
                    strings_as_factors_index = i ;
                    use_default_strings_as_factors = false ;        
                    if( !as<bool>(obj[i]) ) strings_as_factors = false ;
                    break ;         
                }
            }
        }
        if( use_default_strings_as_factors ) 
            return DataFrame(obj) ;
        SEXP as_df_symb = Rf_install("as.data.frame");
        SEXP strings_as_factors_symb = Rf_install("stringsAsFactors");
        
        obj.erase(strings_as_factors_index) ;
        names.erase(strings_as_factors_index) ;
        obj.attr( "names") = names ;
        Scoped<SEXP> call  = Rf_lang3(as_df_symb, obj, wrap( strings_as_factors ) ) ;
        SET_TAG( CDDR(call),  strings_as_factors_symb ) ;   
        Scoped<SEXP> res = Rcpp_eval( call ) ; 
        DataFrame out( res ) ;
        return out ;
    }
    
    
    
} // namespace Rcpp

#endif
