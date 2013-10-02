// Copyright (C) 2003 Romain Francois
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

#ifndef Rcpp_SlotProxy_h
#define Rcpp_SlotProxy_h

namespace Rcpp{
    
template <typename CLASS>
class SlotProxyPolicy {
public:
    
    /**
     * Proxy for objects slots. 
     */
    class SlotProxy {
    public:
        /**
         * Creates a slot proxy. This throws an exception 
         * if the parent object is not an S4 object or if the 
         * class of parent object does not have the requested 
         * slot
         *
         * @param v parent object of which we get/set a slot
         * @param name slot name
         */
        SlotProxy( CLASS& v, const std::string& name) : parent(v), slot_name(Rf_install(name.c_str())) {
            if( !R_has_slot( v, slot_name) ){
                throw no_such_slot() ; 
            }  
        }
        
        /**
         * lhs use. Assigns the target slot using the current 
         * value of another slot proxy.
         *
         * @param rhs another slot proxy
         */
        SlotProxy& operator=(const SlotProxy& rhs) ;
              
        /**
         * lhs use. Assigns the slot by wrapping the rhs object
         *
         * @param rhs wrappable object
         */
        template <typename T> SlotProxy& operator=(const T& rhs) ;
            
        /**
         * rhs use. Retrieves the current value of the slot
         * and structures it as a T object. This only works 
         * when as<T> makes sense
         */ 
        template <typename T> operator T() const ;
        inline operator SEXP() const { return get() ; }
        
    private:
        CLASS& parent; 
        SEXP slot_name ;
            
        SEXP get() const ;
        void set(SEXP x ) ;
    } ;
    
    /**
     * Proxy for objects slots. 
     */
    class const_SlotProxy {
    public:
        /**
         * Creates a slot proxy. This throws an exception 
         * if the parent object is not an S4 object or if the 
         * class of parent object does not have the requested 
         * slot
         *
         * @param v parent object of which we get/set a slot
         * @param name slot name
         */
        const_SlotProxy( const CLASS& v, const std::string& name) ;
    
        /**
         * lhs use. Assigns the target slot using the current 
         * value of another slot proxy.
         *
         * @param rhs another slot proxy
         */
        const_SlotProxy& operator=(const const_SlotProxy& rhs) ;
              
        /**
         * rhs use. Retrieves the current value of the slot
         * and structures it as a T object. This only works 
         * when as<T> makes sense
         */ 
        template <typename T> operator T() const ;
        inline operator SEXP() const { return get() ; }
        
    private:
        const CLASS& parent; 
        SEXP slot_name ;
            
        SEXP get() const ;
    } ;
    
    SlotProxy slot(const std::string& name) ;
    const_SlotProxy slot(const std::string& name) const ;
    
} ;

}
#endif
