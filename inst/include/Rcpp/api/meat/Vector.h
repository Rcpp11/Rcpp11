//
// Vector.h:  Vector meat 
//
// Copyright (C) 2012 - 2013    Dirk Eddelbuettel and Romain Francois
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

#ifndef Rcpp_api_meat_Vector_h
#define Rcpp_api_meat_Vector_h

namespace Rcpp{ 

    template <int RTYPE>
    Vector<RTYPE>::Vector() {
        RCPP_DEBUG_CTOR( Vector, "()" )
        Storage::set__( Rf_allocVector( RTYPE, 0 ) ) ;
        init() ;
    }
    
    template <int RTYPE>
    Vector<RTYPE>::Vector( const int& size ) {
        RCPP_DEBUG_CTOR( Vector, "( int = %d ) ", size )
        Storage::set__( Rf_allocVector( RTYPE, size) ) ;
        init() ;
    }
    
    template <int RTYPE>
    Vector<RTYPE>::Vector( const Dimension& dims ) {
        RCPP_DEBUG_CTOR( Vector, "( const Dimension& (%d) )", dims.size()  )
        Storage::set__(Rf_allocVector( RTYPE, dims.prod() )) ; 
        init() ;
        if( dims.size() > 1 ){
            AttributeProxy_::attr( "dim" ) = dims;
        }
    }
    
    template <int RTYPE>
    template <typename U>
    Vector<RTYPE>::Vector( const Dimension& dims, const U& u) {
        RCPP_DEBUG_CTOR( Vector, "( const Dimension& (%d), const %s& )", dims.size(), DEMANGLE(U) )
        Storage::set__( Rf_allocVector( RTYPE, dims.prod() ) ) ;
        fill(u) ;
        if( dims.size() > 1 ){
            AttributeProxy_::attr( "dim" ) = dims;
        }
    }
    
    template <int RTYPE>
    template <typename U>
    Vector<RTYPE>::Vector( const int& size, const U& u) {
        RCPP_DEBUG_CTOR( Vector, "( const int& size, const %s& u )", size, DEMANGLE(U) )
        Storage::set__( Rf_allocVector( RTYPE, size) ) ;
        fill( u ) ;	
    }
        
    template <int RTYPE>
    template <bool NA, typename VEC>
    Vector<RTYPE>::Vector( const VectorBase<RTYPE,NA,VEC>& other ) {
        RCPP_DEBUG_CTOR( Vector, "( const VectorBase<%d,%s,VEC>& ) [VEC = %s]", RTYPE, (NA?"true":"false"), DEMANGLE(VEC) )
        import_sugar_expression( other, typename std::is_same<Vector,VEC>::type() ) ;
    }
    
    template <int RTYPE>
    template <bool NA, typename T>
    Vector<RTYPE>::Vector( const sugar::SingleLogicalResult<NA,T>& obj ) {
        Storage::set__( r_cast<RTYPE>( const_cast<sugar::SingleLogicalResult<NA,T>&>(obj).get_sexp() ) );
        RCPP_DEBUG_CTOR( Vector, "( const sugar::SingleLogicalResult<%s,T>& ) [T = %s]", (NA?"true":"false"), DEMANGLE(T) )
    }
    
    
    template <int RTYPE>
    template <typename T> 
    Vector<RTYPE>& Vector<RTYPE>::operator=( const T &x ){
        assign_object( x, typename traits::is_sugar_expression<T>::type() ) ;
        return *this ;
    }
    
    template <int RTYPE>
    template <bool NA, typename T>
    inline void Vector<RTYPE>::assign_sugar_expression( const VectorBase<RTYPE,NA,T>& x ){
        int n = size() ;
        if( n == x.size() ){
            // just copy the data 
            import_expression<T>(x.get_ref(), n ) ;
        } else{
            // different size, so we change the memory
            Vector<RTYPE> tmp(x) ;
            Storage::set__( tmp ); 
        }
    }
    
    // sugar
    template <int RTYPE>
    template <typename T>
    inline void Vector<RTYPE>::assign_object( const T& x, std::true_type ){
        assign_sugar_expression( x ) ;
    }
    
    // anything else
    template <int RTYPE>
    template <typename T>
    inline void Vector<RTYPE>::assign_object( const T& x, std::false_type ){
        Storage::set__( r_cast<RTYPE>( wrap(x) ) ) ;
    }
    
    template <int RTYPE>
    template <bool NA, typename VEC>
    inline void Vector<RTYPE>::import_sugar_expression( const Rcpp::VectorBase<RTYPE,NA,VEC>& other, std::false_type ){
        RCPP_DEBUG_CLASS( Vector, "::import_sugar_expression( VectorBase<%d,%s,%s>, false_type )", RTYPE, (NA?"true":"false"), RTYPE, DEMANGLE(VEC) ) ;
        int n = other.size() ;
        Storage::set__( Rf_allocVector( RTYPE, n ) ) ;
        import_expression<VEC>( other.get_ref() , n ) ;
    }   
    
    template <int RTYPE>
    template <bool NA, typename VEC>
    inline void Vector<RTYPE>::import_sugar_expression( const Rcpp::VectorBase<RTYPE,NA,VEC>& other, std::true_type ){
        RCPP_DEBUG_CLASS( Vector, "::import_sugar_expression( VectorBase<%d,%s,%s>, true_type )", RTYPE, (NA?"true":"false"), RTYPE, DEMANGLE(VEC) ) ;
        Storage::set__( other.get_ref() ) ;
    }   

    template <int RTYPE>
    template <typename T>
    inline void Vector<RTYPE>::import_expression( const T& other, int n ){
        iterator start = begin() ; 
        RCPP_LOOP_UNROLL(start,other)
    }
    
    template <int RTYPE>
    typename Vector<RTYPE>::iterator Vector<RTYPE>::erase_single__impl( iterator position ){
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
            SEXP newnames = PROTECT(::Rf_allocVector( STRSXP, n-1 ));
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
            UNPROTECT(1) ; /* newnames */
            Storage::set__( target.get__() ) ;
            return begin()+result ;
        }
    }
    
    template <int RTYPE>
    typename Vector<RTYPE>::iterator Vector<RTYPE>::erase_range__impl( iterator first, iterator last ){
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
            SEXP newnames = PROTECT( ::Rf_allocVector(STRSXP, target_size) ) ;
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
            UNPROTECT(1) ; /* newnames */
        }
        Storage::set__( target.get__() );
        return result ;
    }
    
 
    template <int RTYPE>
    void Vector<RTYPE>::push_back__impl(const stored_type& object, std::false_type){
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
            SEXP newnames = PROTECT( ::Rf_allocVector( STRSXP, n + 1) ) ;
            int i = 0 ;
            for( ; it < this_end; ++it, ++target_it, i++ ){
                *target_it = *it ;
                SET_STRING_ELT( newnames, i, STRING_ELT(names, i ) ) ;
            }
            SET_STRING_ELT( newnames, i, Rf_mkChar("") ) ;
            target.attr("names") = newnames ;
            UNPROTECT(1) ; /* newnames */
        }
        *target_it = object;
        Storage::set__( target.get__() ) ;
    }	
    
    template <int RTYPE>
    void Vector<RTYPE>::push_back__impl(const stored_type& object, std::true_type){
        SEXP object_sexp = PROTECT( object ) ;
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
            SEXP newnames = PROTECT( ::Rf_allocVector( STRSXP, n + 1) ) ;
            int i = 0 ;
            for( ; it < this_end; ++it, ++target_it, i++ ){
                *target_it = *it ;
                SET_STRING_ELT( newnames, i, STRING_ELT(names, i ) ) ;
            }
            SET_STRING_ELT( newnames, i, Rf_mkChar("") ) ;
            target.attr("names") = newnames ;
            UNPROTECT(1) ; /* newnames */
        }
        *target_it = object_sexp;
        Storage::set__( target.get__() ) ;
        UNPROTECT(1) ;
    }	
    	
    template <int RTYPE>
    void Vector<RTYPE>::push_back_name__impl(const stored_type& object, const std::string& name, std::false_type ){
        int n = size() ;
        Vector target( n + 1 ) ;
        iterator target_it( target.begin() ) ;
        iterator it(begin()) ;
        iterator this_end(end());
        SEXP names = RCPP_GET_NAMES( Storage::get__() ) ;
        SEXP newnames = PROTECT( ::Rf_allocVector( STRSXP, n+1 ) ) ;
        int i=0;
        if( names == R_NilValue ){
            SEXP dummy = PROTECT( Rf_mkChar("") );
            for( ; it < this_end; ++it, ++target_it,i++ ){
                *target_it = *it ;
                SET_STRING_ELT( newnames, i , dummy );
            }
            UNPROTECT(1) ; /* dummy */
        } else {
            for( ; it < this_end; ++it, ++target_it, i++ ){
                *target_it = *it ;
                SET_STRING_ELT( newnames, i, STRING_ELT(names, i ) ) ;
            }
        }
        SET_STRING_ELT( newnames, i, Rf_mkChar( name.c_str() ) );
        target.attr("names") = newnames ;
    		
        *target_it = object;
        UNPROTECT(1) ; /* newnames, */
        Storage::set__( target.get__() ) ;
    }
    	
    template <int RTYPE>
    void Vector<RTYPE>::push_back_name__impl(const stored_type& object, const std::string& name, std::true_type ){
        SEXP object_sexp = PROTECT( object ) ;
        int n = size() ;
        Vector target( n + 1 ) ;
        iterator target_it( target.begin() ) ;
        iterator it(begin()) ;
        iterator this_end(end());
        SEXP names = RCPP_GET_NAMES( Storage::get__() ) ;
        SEXP newnames = PROTECT( ::Rf_allocVector( STRSXP, n+1 ) ) ;
        int i=0;
        if( names == R_NilValue ){
            SEXP dummy = PROTECT( Rf_mkChar("") );
            for( ; it < this_end; ++it, ++target_it,i++ ){
                *target_it = *it ;
                SET_STRING_ELT( newnames, i , dummy );
            }
            UNPROTECT(1) ; /* dummy */
        } else {
            for( ; it < this_end; ++it, ++target_it, i++ ){
                *target_it = *it ;
                SET_STRING_ELT( newnames, i, STRING_ELT(names, i ) ) ;
            }
        }
        SET_STRING_ELT( newnames, i, Rf_mkChar( name.c_str() ) );
        target.attr("names") = newnames ;
    		
        *target_it = object_sexp;
        UNPROTECT(2) ; /* newnames, object_sexp */
        Storage::set__( target.get__() ) ;
    }
    	
    template <int RTYPE>
    void Vector<RTYPE>::push_front__impl(const stored_type& object, std::false_type ){
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
            SEXP newnames = PROTECT( ::Rf_allocVector( STRSXP, n + 1) );
            int i=1 ;
            SET_STRING_ELT( newnames, 0, Rf_mkChar("") ) ;
            for( ; it<this_end; ++it, ++target_it, i++){
                *target_it = *it ;
                SET_STRING_ELT( newnames, i, STRING_ELT(names, i-1 ) ) ;
            }
            target.attr("names") = newnames ;
            UNPROTECT(1) ; /* newnames */
        }
        Storage::set__( target.get__() ) ;
    }
    	
    template <int RTYPE>
    void Vector<RTYPE>::push_front__impl(const stored_type& object, std::true_type ){
        SEXP object_sexp = PROTECT( object ) ;
        int n = size() ;
        Vector target( n+1);
        iterator target_it(target.begin());
        iterator it(begin());
        iterator this_end(end());
        *target_it = object_sexp ;
        UNPROTECT(1); /* object_sexp */
        ++target_it ;
        SEXP names = RCPP_GET_NAMES( Storage::get__() ) ;
        if( names == R_NilValue ){
            for( ; it<this_end; ++it, ++target_it){
                *target_it = *it ;
            }
        } else{
            SEXP newnames = PROTECT( ::Rf_allocVector( STRSXP, n + 1) );
            int i=1 ;
            SET_STRING_ELT( newnames, 0, Rf_mkChar("") ) ;
            for( ; it<this_end; ++it, ++target_it, i++){
                *target_it = *it ;
                SET_STRING_ELT( newnames, i, STRING_ELT(names, i-1 ) ) ;
            }
            target.attr("names") = newnames ;
            UNPROTECT(1) ; /* newnames */
        }
        Storage::set__( target.get__() ) ;
    }
    	
    template <int RTYPE>
    void Vector<RTYPE>::push_front_name__impl(const stored_type& object, const std::string& name, std::false_type ){
        int n = size() ;
        Vector target( n + 1 ) ;
        iterator target_it( target.begin() ) ;
        iterator it(begin()) ;
        iterator this_end(end());
        SEXP names = RCPP_GET_NAMES( Storage::get__() ) ;
        SEXP newnames = PROTECT( ::Rf_allocVector( STRSXP, n+1 ) ) ;
        int i=1;
        SET_STRING_ELT( newnames, 0, Rf_mkChar( name.c_str() ) );
        *target_it = object;
        ++target_it ;
    		
        if( names == R_NilValue ){
            SEXP dummy = PROTECT( Rf_mkChar("") );
            for( ; it < this_end; ++it, ++target_it,i++ ){
                *target_it = *it ;
                SET_STRING_ELT( newnames, i , dummy );
            }
            UNPROTECT(1) ; /* dummy */
        } else {
            for( ; it < this_end; ++it, ++target_it, i++ ){
                *target_it = *it ;
                SET_STRING_ELT( newnames, i, STRING_ELT(names, i-1 ) ) ;
            }
        }
        target.attr("names") = newnames ;
    		
        UNPROTECT(1) ; /* newnames, */
        Storage::set__( target.get__() ) ;
    }
    	
    template <int RTYPE>
    void Vector<RTYPE>::push_front_name__impl(const stored_type& object, const std::string& name, std::true_type ){
        SEXP object_sexp = PROTECT(object) ;
        int n = size() ;
        Vector target( n + 1 ) ;
        iterator target_it( target.begin() ) ;
        iterator it(begin()) ;
        iterator this_end(end());
        SEXP names = RCPP_GET_NAMES( Storage::get__() ) ;
        SEXP newnames = PROTECT( ::Rf_allocVector( STRSXP, n+1 ) ) ;
        int i=1;
        SET_STRING_ELT( newnames, 0, Rf_mkChar( name.c_str() ) );
        *target_it = object_sexp;
        ++target_it ;
    		
        if( names == R_NilValue ){
            SEXP dummy = PROTECT( Rf_mkChar("") );
            for( ; it < this_end; ++it, ++target_it,i++ ){
                *target_it = *it ;
                SET_STRING_ELT( newnames, i , dummy );
            }
            UNPROTECT(1) ; /* dummy */
        } else {
            for( ; it < this_end; ++it, ++target_it, i++ ){
                *target_it = *it ;
                SET_STRING_ELT( newnames, i, STRING_ELT(names, i-1 ) ) ;
            }
        }
        target.attr("names") = newnames ;
    		
        UNPROTECT(2) ; /* newnames, object_sexp */
        Storage::set__( target.get__() ) ;
    }
    	
    
    template <int RTYPE>
    template <typename T>
    typename Vector<RTYPE>::iterator Vector<RTYPE>::insert( iterator position, const T& object){
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
            SEXP newnames = PROTECT( ::Rf_allocVector( STRSXP, n + 1 ) ) ;
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
            UNPROTECT(1) ; /* newmanes */
        }
        Storage::set__( target.get__() );
        return result ;
    
    }
    
    
    template <int RTYPE>
    template <typename EXPR_VEC>
    Vector<RTYPE>& Vector<RTYPE>::operator+=( const VectorBase<RTYPE,true,EXPR_VEC>& rhs ){
        const EXPR_VEC& ref = rhs.get_ref() ;
        iterator start = begin() ;
        int n = size() ;
        // TODO: maybe unroll this
        stored_type tmp ;
        for( int i=0; i<n; i++){
            Proxy left = start[i] ;
            if( ! traits::is_na<RTYPE>( left ) ){
                tmp = ref[i] ;
                left = traits::is_na<RTYPE>( tmp ) ? tmp : ( left + tmp ) ;
            }
        }
        return *this ;  
    }
    
    template <int RTYPE>
    template <typename EXPR_VEC>
    Vector<RTYPE>& Vector<RTYPE>::operator+=( const VectorBase<RTYPE,false,EXPR_VEC>& rhs ){
        const EXPR_VEC& ref = rhs.get_ref() ;
        iterator start = begin() ;
        int n = size() ;
        stored_type tmp ;
        for( int i=0; i<n; i++){
            if( ! traits::is_na<RTYPE>(start[i]) ){
                start[i] += ref[i] ;
            }
        }
        return *this ;  
    }
    
    template <>
    template <typename EXPR_VEC>
    Vector<REALSXP>& Vector<REALSXP>::operator+=( const VectorBase<REALSXP,false,EXPR_VEC>& rhs ){
        const EXPR_VEC& vec = rhs.get_ref() ;
        int n = size() ;
        iterator start = begin() ;
        for( int i=0; i<n; i++){
            start[i] += vec[i] ;        
        }
        return *this ;
    }
    
    template <>
    template <typename EXPR_VEC>
    Vector<REALSXP>& Vector<REALSXP>::operator+=( const VectorBase<REALSXP,true,EXPR_VEC>& rhs ){
        const EXPR_VEC& vec = rhs.get_ref() ;
        int n = size() ;
        iterator start = begin() ;
        for( int i=0; i<n; i++){
            start[i] += vec[i] ;        
        }
        return *this ;
    }
    
    
    template <int RTYPE>
    bool Vector<RTYPE>::containsElementNamed( const char* target ) const {
        SEXP names = RCPP_GET_NAMES( Storage::get__() ) ; 
        if( Rf_isNull(names) ) return false ;
        int n = Rf_length(names) ;
        for( int i=0; i<n; i++){
            if( !strcmp( target, CHAR(STRING_ELT(names, i)) ) ) 
                return true ;   
        }
        return false ;
    }
     
    namespace internal {
    
        template <typename T>
        inline SEXP wrap_range_sugar_expression( const T& object) {
            const int RTYPE = T::r_type::value ;
            return Rcpp::Vector<RTYPE>(object) ;
        }

    }
    
    template <int RTYPE>
    template <typename... Args> 
    Vector<RTYPE> Vector<RTYPE>::create(Args... args){
        return typename create_type<RTYPE, Args...>::type( args... ) ;
    }
    
    
} // namespace Rcpp

#endif
