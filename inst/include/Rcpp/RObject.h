//
// RObject.h:  general R object wrapper
//
// Copyright (C) 2009 - 2012    Dirk Eddelbuettel and Romain Francois
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

#ifndef Rcpp_RObject_h
#define Rcpp_RObject_h

namespace Rcpp{ 

    class RObject : public SlotProxyPolicy<RObject>, public AttributeProxyPolicy<RObject> {
    public:
        
        /**
         * default constructor. uses R_NilValue
         */ 
        RObject() ; 

        /**
         * wraps a SEXP. The SEXP is automatically protected from garbage 
         * collection by this object and the protection vanishes when this 
         * object is destroyed
         */
        RObject(SEXP x) ;

        /**
         * Copy constructor. set this SEXP to the SEXP of the copied object
         */
        RObject( const RObject& other ) ;

        RObject( RObject&& other ) ;
        RObject& operator=( RObject&& other ) ;
        
        /**
         * Assignment operator. set this SEXP to the SEXP of the copied object
         */
        RObject& operator=( const RObject& other ) ;

        /** 
         * Assignement operator. Set this SEXP to the given SEXP
         */ 
        RObject& operator=( SEXP other ) ;

        /**
         * Removes the protection. The enclosed SEXP becomes subject
         * to garbage collection, if not otherwise protected
         */
        virtual ~RObject() ;

        /**
         * implicit conversion to SEXP.
         */
        inline operator SEXP() const { return m_sexp ; }

        /**
         * Does this object inherit from a given class
         */
        inline bool inherits(const char* clazz) const { return ::Rf_inherits( m_sexp, clazz) ; }
    
        /* attributes */

        /**
         * extracts the names of the attributes of the wrapped SEXP
         */
        CharacterVector attributeNames() const ;

        /**
         * Identifies if the SEXP has the given attribute
         */
        bool hasAttribute( const std::string& attr) const ; 
   
        /**
         * is this object NULL
         */
        inline bool isNULL() const{ return Rf_isNull(m_sexp) ; }

        /** 
         * explicit conversion to SEXP
         */
        inline SEXP asSexp() const { return m_sexp ; }

        /**
         * Tests if the SEXP has the object bit set
         */
        inline bool isObject() const { return ::Rf_isObject(m_sexp) ;}

        /**
         * Tests if the SEXP is an S4 object
         */
        inline bool isS4() const { return ::Rf_isS4(m_sexp) ; }

        /**
         * Indicates if this S4 object has the given slot
         *
         * @throw not_s4 if the object is not an S4 object
         */
        bool hasSlot(const std::string& name) const ;

    protected:                                  

        /**
         * sets the SEXP wrapped by this object
         *
         * @param x new SEXP to attach to this object
         */
        void setSEXP(SEXP x) ;

        /**
         * The SEXP this is wrapping. This has to be considered read only.
         * to change it, use setSEXP
         */
        SEXP m_sexp ;
    
    };

} // namespace Rcpp

#endif
