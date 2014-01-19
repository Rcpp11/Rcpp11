#ifndef RCPP__IOSTREAM__iostream_H
#define RCPP__IOSTREAM__iostream_H

#include <Rcpp/iostream/Rstreambuf.h>
#include <Rcpp/iostream/Rostream.h>

namespace Rcpp{ 
    
    // Rostream
    template <> inline std::streamsize Rstreambuf<true>::xsputn(const char *s, std::streamsize num ) {
        Rprintf( "%.*s", num, s ) ;
        return num ;
    }
    template <> inline std::streamsize Rstreambuf<false>::xsputn(const char *s, std::streamsize num ) {
        REprintf( "%.*s", num, s ) ; 
        return num ;
    }
    
    template <> inline int Rstreambuf<true>::overflow(int c ) {
      if (c != EOF) Rprintf( "%.1s", &c ) ;
      return c ;
    }
    template <> inline int Rstreambuf<false>::overflow(int c ) {
      if (c != EOF) REprintf( "%.1s", &c ) ;
      return c ;
    }
        
    template <> inline int Rstreambuf<true>::sync(){
        ::R_FlushConsole() ;
        return 0 ;
    }
    template <> inline int Rstreambuf<false>::sync(){
        ::R_FlushConsole() ;
        return 0 ;
    }
    
}
#endif
