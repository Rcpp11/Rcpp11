#ifndef Rcpp_api_meat_Vector_h
#define Rcpp_api_meat_Vector_h

namespace Rcpp{ 

    template <int RTYPE, template <class> class StoragePolicy>
    typename Vector<RTYPE,StoragePolicy>::iterator Vector<RTYPE,StoragePolicy>::erase_single__impl( iterator position ){
        if( position < begin() || position > end() ) throw index_out_of_bounds( ) ;
        int n = size() ;
        Vector target( n - 1 ) ;
        iterator target_it(target.begin()) ;
        iterator it(begin()) ;
        iterator this_end(end()) ;
        SEXP names = RCPP_GET_NAMES( Storage::get__() ) ;
        if( names == R_NilValue ){
            int i=0; 
            for( ; it < position; ++it, ++target_it, i++){
                *target_it = *it;
            }
            ++it ;
            for( ; it < this_end ; ++it, ++target_it){
                *target_it = *it;
            }
            Storage::set__( target.get__() ) ;
            return begin()+i ;
        } else {
            Shield<SEXP> newnames = ::Rf_allocVector( STRSXP, n-1 );
            int i= 0 ;
            for( ; it < position; ++it, ++target_it,i++){
                *target_it = *it;
                SET_STRING_ELT( newnames, i , STRING_ELT(names,i) ) ;
            }
            int result=i ;
            ++it ;
            i++ ;
            for( ; it < this_end ; ++it, ++target_it, i++){
                *target_it = *it;
                SET_STRING_ELT( newnames, i-1, STRING_ELT(names,i) ) ;
            }
            target.attr( "names" ) = newnames ;
            Storage::set__( target.get__() ) ;
            return begin()+result ;
        }
    }
    
    template <int RTYPE, template <class> class StoragePolicy>
    typename Vector<RTYPE,StoragePolicy>::iterator Vector<RTYPE,StoragePolicy>::erase_range__impl( iterator first, iterator last ){
        if( first > last ) throw std::range_error("invalid range") ;
        if( last > end() || first < begin() ) throw index_out_of_bounds() ;
        
        iterator it = begin() ;
        iterator this_end = end() ;
        int nremoved = std::distance(first,last) ;
        int target_size = size() - nremoved  ;
        Vector target( target_size ) ;
        iterator target_it = target.begin() ;
        
        SEXP names = RCPP_GET_NAMES( Storage::get__() ) ;
        iterator result ;
        if( names == R_NilValue ){
            int i=0; 
            for( ; it < first; ++it, ++target_it, i++ ){
                *target_it = *it ;
            }
            result = begin() + i + 1 ;
            for( it = last ; it < this_end; ++it, ++target_it ){
                *target_it = *it ;
            }
        } else{
            Shield<SEXP> newnames = ::Rf_allocVector(STRSXP, target_size);
            int i= 0 ;
            for( ; it < first; ++it, ++target_it, i++ ){
                *target_it = *it ;
                SET_STRING_ELT( newnames, i, STRING_ELT(names, i ) );
            }
            result = begin() + i + 1 ;
            for( it = last ; it < this_end; ++it, ++target_it, i++ ){
                *target_it = *it ;
                SET_STRING_ELT( newnames, i, STRING_ELT(names, i + nremoved ) );
            }
            target.attr("names" ) = newnames ;
        }
        Storage::set__( target.get__() );
        return result ;
    }
    
 
    template <int RTYPE, template <class> class StoragePolicy>
    void Vector<RTYPE,StoragePolicy>::push_back__impl(const stored_type& object, std::false_type){
        int n = size() ;
        Vector target( n + 1 ) ;
        SEXP names = RCPP_GET_NAMES( Storage::get__() ) ;
        iterator target_it( target.begin() ) ;
        iterator it(begin()) ;
        iterator this_end(end());
        if( names == R_NilValue ){
            for( ; it < this_end; ++it, ++target_it ){
                *target_it = *it ;
            }
        } else {
            Shield<SEXP> newnames = ::Rf_allocVector( STRSXP, n + 1) ;
            int i = 0 ;
            for( ; it < this_end; ++it, ++target_it, i++ ){
                *target_it = *it ;
                SET_STRING_ELT( newnames, i, STRING_ELT(names, i ) ) ;
            }
            SET_STRING_ELT( newnames, i, Rf_mkChar("") ) ;
            target.attr("names") = newnames ;
        }
        *target_it = object;
        Storage::set__( target.get__() ) ;
    }    
    
    template <int RTYPE, template <class> class StoragePolicy>
    void Vector<RTYPE,StoragePolicy>::push_back__impl(const stored_type& object, std::true_type){
        Shield<SEXP> object_sexp = object ;
        int n = size() ;
        Vector target( n + 1 ) ;
        SEXP names = RCPP_GET_NAMES( Storage::get__() ) ;
        iterator target_it( target.begin() ) ;
        iterator it(begin()) ;
        iterator this_end(end());
        if( names == R_NilValue ){
            for( ; it < this_end; ++it, ++target_it ){
                *target_it = *it ;
            }
        } else {
            Shield<SEXP> newnames = ::Rf_allocVector( STRSXP, n + 1) ;
            int i = 0 ;
            for( ; it < this_end; ++it, ++target_it, i++ ){
                *target_it = *it ;
                SET_STRING_ELT( newnames, i, STRING_ELT(names, i ) ) ;
            }
            SET_STRING_ELT( newnames, i, Rf_mkChar("") ) ;
            target.attr("names") = newnames ;
        }
        *target_it = object_sexp;
        Storage::set__( target.get__() ) ;
    }    
        
    template <int RTYPE, template <class> class StoragePolicy>
    void Vector<RTYPE,StoragePolicy>::push_back_name__impl(const stored_type& object, const std::string& name, std::false_type ){
        int n = size() ;
        Vector target( n + 1 ) ;
        iterator target_it( target.begin() ) ;
        iterator it(begin()) ;
        iterator this_end(end());
        SEXP names = RCPP_GET_NAMES( Storage::get__() ) ;
        Shield<SEXP> newnames = ::Rf_allocVector( STRSXP, n+1 ) ;
        int i=0;
        if( names == R_NilValue ){
            SEXP dummy = Rf_mkChar("") ;
            for( ; it < this_end; ++it, ++target_it,i++ ){
                *target_it = *it ;
                SET_STRING_ELT( newnames, i , dummy );
            }
        } else {
            for( ; it < this_end; ++it, ++target_it, i++ ){
                *target_it = *it ;
                SET_STRING_ELT( newnames, i, STRING_ELT(names, i ) ) ;
            }
        }
        SET_STRING_ELT( newnames, i, Rf_mkChar( name.c_str() ) );
        target.attr("names") = newnames ;
            
        *target_it = object;
        Storage::set__( target.get__() ) ;
    }
        
    template <int RTYPE, template <class> class StoragePolicy>
    void Vector<RTYPE,StoragePolicy>::push_back_name__impl(const stored_type& object, const std::string& name, std::true_type ){
        Shield<SEXP> object_sexp = object ;
        int n = size() ;
        Vector target( n + 1 ) ;
        iterator target_it( target.begin() ) ;
        iterator it(begin()) ;
        iterator this_end(end());
        SEXP names = RCPP_GET_NAMES( Storage::get__() ) ;
        Shield<SEXP> newnames = ::Rf_allocVector( STRSXP, n+1 ) ;
        int i=0;
        if( names == R_NilValue ){
            SEXP dummy = Rf_mkChar("") ;
            for( ; it < this_end; ++it, ++target_it,i++ ){
                *target_it = *it ;
                SET_STRING_ELT( newnames, i , dummy );
            }
        } else {
            for( ; it < this_end; ++it, ++target_it, i++ ){
                *target_it = *it ;
                SET_STRING_ELT( newnames, i, STRING_ELT(names, i ) ) ;
            }
        }
        SET_STRING_ELT( newnames, i, Rf_mkChar( name.c_str() ) );
        target.attr("names") = newnames ;
            
        *target_it = object_sexp;
        Storage::set__( target.get__() ) ;
    }
        
    template <int RTYPE, template <class> class StoragePolicy>
    void Vector<RTYPE,StoragePolicy>::push_front__impl(const stored_type& object, std::false_type ){
        int n = size() ;
        Vector target( n+1);
        iterator target_it(target.begin());
        iterator it(begin());
        iterator this_end(end());
        *target_it = object ;
        ++target_it ;
        SEXP names = RCPP_GET_NAMES( Storage::get__() ) ;
        if( names == R_NilValue ){
            for( ; it<this_end; ++it, ++target_it){
                *target_it = *it ;
            }
        } else{
            Shield<SEXP> newnames = ::Rf_allocVector( STRSXP, n + 1);
            int i=1 ;
            SET_STRING_ELT( newnames, 0, Rf_mkChar("") ) ;
            for( ; it<this_end; ++it, ++target_it, i++){
                *target_it = *it ;
                SET_STRING_ELT( newnames, i, STRING_ELT(names, i-1 ) ) ;
            }
            target.attr("names") = newnames ;
        }
        Storage::set__( target.get__() ) ;
    }
        
    template <int RTYPE, template <class> class StoragePolicy>
    void Vector<RTYPE,StoragePolicy>::push_front__impl(const stored_type& object, std::true_type ){
        Shield<SEXP> object_sexp = object ;
        int n = size() ;
        Vector target( n+1);
        iterator target_it(target.begin());
        iterator it(begin());
        iterator this_end(end());
        *target_it = object_sexp ;
        ++target_it ;
        SEXP names = RCPP_GET_NAMES( Storage::get__() ) ;
        if( names == R_NilValue ){
            for( ; it<this_end; ++it, ++target_it){
                *target_it = *it ;
            }
        } else{
            Shield<SEXP> newnames = ::Rf_allocVector( STRSXP, n + 1);
            int i=1 ;
            SET_STRING_ELT( newnames, 0, Rf_mkChar("") ) ;
            for( ; it<this_end; ++it, ++target_it, i++){
                *target_it = *it ;
                SET_STRING_ELT( newnames, i, STRING_ELT(names, i-1 ) ) ;
            }
            target.attr("names") = newnames ;
        }
        Storage::set__( target.get__() ) ;
    }
        
    template <int RTYPE, template <class> class StoragePolicy>
    void Vector<RTYPE,StoragePolicy>::push_front_name__impl(const stored_type& object, const std::string& name, std::false_type ){
        int n = size() ;
        Vector target( n + 1 ) ;
        iterator target_it( target.begin() ) ;
        iterator it(begin()) ;
        iterator this_end(end());
        SEXP names = RCPP_GET_NAMES( Storage::get__() ) ;
        Shield<SEXP> newnames = ::Rf_allocVector( STRSXP, n+1 ) ;
        int i=1;
        SET_STRING_ELT( newnames, 0, Rf_mkChar( name.c_str() ) );
        *target_it = object;
        ++target_it ;
            
        if( names == R_NilValue ){
            Shield<SEXP> dummy = Rf_mkChar("");
            for( ; it < this_end; ++it, ++target_it,i++ ){
                *target_it = *it ;
                SET_STRING_ELT( newnames, i , dummy );
            }
        } else {
            for( ; it < this_end; ++it, ++target_it, i++ ){
                *target_it = *it ;
                SET_STRING_ELT( newnames, i, STRING_ELT(names, i-1 ) ) ;
            }
        }
        target.attr("names") = newnames ;
            
        Storage::set__( target.get__() ) ;
    }
        
    template <int RTYPE, template <class> class StoragePolicy>
    void Vector<RTYPE,StoragePolicy>::push_front_name__impl(const stored_type& object, const std::string& name, std::true_type ){
        Shield<SEXP> object_sexp = object ;
        int n = size() ;
        Vector target( n + 1 ) ;
        iterator target_it( target.begin() ) ;
        iterator it(begin()) ;
        iterator this_end(end());
        SEXP names = RCPP_GET_NAMES( Storage::get__() ) ;
        Shield<SEXP> newnames = ::Rf_allocVector( STRSXP, n+1 ) ;
        int i=1;
        SET_STRING_ELT( newnames, 0, Rf_mkChar( name.c_str() ) );
        *target_it = object_sexp;
        ++target_it ;
            
        if( names == R_NilValue ){
            Shield<SEXP> dummy = Rf_mkChar("");
            for( ; it < this_end; ++it, ++target_it,i++ ){
                *target_it = *it ;
                SET_STRING_ELT( newnames, i , dummy );
            }
        } else {
            for( ; it < this_end; ++it, ++target_it, i++ ){
                *target_it = *it ;
                SET_STRING_ELT( newnames, i, STRING_ELT(names, i-1 ) ) ;
            }
        }
        target.attr("names") = newnames ;
            
        Storage::set__( target.get__() ) ;
    }
        
    
    template <int RTYPE, template <class> class StoragePolicy>
    template <typename T>
    typename Vector<RTYPE,StoragePolicy>::iterator Vector<RTYPE,StoragePolicy>::insert( iterator position, const T& object){
        int n = size() ;
        Vector target( n+1 ) ;
        iterator target_it = target.begin();
        iterator it = begin() ;
        iterator this_end = end() ;
        SEXP names = RCPP_GET_NAMES( Storage::get__() ) ;
        iterator result ;
        if( names == R_NilValue ){
            for( ; it < position; ++it, ++target_it){
                *target_it = *it ;
            }
            result = target_it;
            *target_it = converter_type::get( object ) ; 
            ++target_it ;
            for( ; it < this_end; ++it, ++target_it ){
                *target_it = *it ;
            }
        } else{
            Shield<SEXP> newnames = ::Rf_allocVector( STRSXP, n + 1 ) ;
            int i=0;
            for( ; it < position; ++it, ++target_it, i++){
                *target_it = *it ;
                SET_STRING_ELT( newnames, i, STRING_ELT(names, i ) ) ;
            }
            result = target_it;
            *target_it = converter_type::get(object) ;
            SET_STRING_ELT( newnames, i, Rf_mkChar( internal::get_object_name(object) ) ) ;
            i++ ;
            ++target_it ;
            for( ; it < this_end; ++it, ++target_it, i++ ){
                *target_it = *it ;
                SET_STRING_ELT( newnames, i, STRING_ELT(names, i - 1) ) ;
            }
            target.attr( "names" ) = newnames ;
        }
        Storage::set__( target.get__() );
        return result ;
    
    }
    
} // namespace Rcpp

#endif
