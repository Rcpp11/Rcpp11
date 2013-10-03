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

#ifndef Rcpp__internal_coerce_to_string_h
#define Rcpp__internal_coerce_to_string_h

namespace Rcpp{
namespace internal{
     
    inline int integer_width( int n ){
        return n < 0 ? ( (int) ( ::log10( -n+0.5) + 2 ) ) : ( (int) ( ::log10( n+0.5) + 1 ) ) ;    
    }

    #define NB 1000
    template <> inline const char* coerce_to_string<INTSXP>(int from){
        static char buffer[NB] ;
        snprintf( buffer, NB, "%*d", integer_width(from), from );
        return buffer ;
    }
    template <> inline const char* coerce_to_string<LGLSXP>(int from){
        return from == 0 ? "FALSE" : "TRUE" ;    
    }
    template <> inline const char* coerce_to_string<RAWSXP>(Rbyte from){
        static char buff[3];
        snprintf(buff, 3, "%02x", from);
        return buff ;    
    }
        
    template <typename charT>
    const charT* dropTrailing0(charT *s, charT cdec) {
        /* Note that  's'  is modified */
        charT *p = s;
        for (p = s; *p; p++) {
            if(*p == cdec) {
                charT *replace = p++;
                while ('0' <= *p  &&  *p <= '9') if(*(p++) != '0') replace = p;
                if(replace != p) while((*(replace++) = *(p++))) ;
                break;
            }
        }
        return s;
    }
    
    template <> inline const char* coerce_to_string<REALSXP>(double x){
        //int w,d,e ;
        // cf src/main/format.c in R's sources:
        //   The return values are
        //     w : the required field width
        //     d : use %w.df in fixed format, %#w.de in scientific format
        //     e : use scientific format if != 0, value is number of exp digits - 1
        //
        //   nsmall specifies the minimum number of decimal digits in fixed format:
        //   it is 0 except when called from do_format.
        //Rf_formatReal( &x, 1, &w, &d, &e, 0 ) ;
        // we are no longer allowed to use this:
        //     char* tmp = const_cast<char*>( Rf_EncodeReal(x, w, d, e, '.') );
        // so approximate it poorly as
        static char tmp[128];
        snprintf(tmp, 127, "%f", x); 
        return dropTrailing0(tmp, '.');
    }
    
    template <> inline const char* coerce_to_string<CPLXSXP>(Rcomplex x){
        //int wr, dr, er, wi, di, ei;
        //Rf_formatComplex(&x, 1, &wr, &dr, &er, &wi, &di, &ei, 0);
        // we are no longer allowed to use this:
        //     Rf_EncodeComplex(x, wr, dr, er, wi, di, ei, '.' );
        // so approximate it poorly as
        static char tmp1[128], tmp2[128], tmp3[256];
        //snprintf(tmp, 127, "%*.*f+%*.*fi", wr, dr, x.r, wi, di, x.i);
        //snprintf(tmp, 127, "%f+%fi", x.r, x.i); // FIXEM: barebones default formatting
        snprintf(tmp1, 127, "%f", x.r); 
        snprintf(tmp2, 127, "%f", x.i); 
        snprintf(tmp3, 255, "%s+%si", dropTrailing0(tmp1, '.'), dropTrailing0(tmp2, '.'));
        return tmp3;
    }
  
}
}

#endif
