#ifndef RCPP__IOSTREAM__RSTREAMBUF_H
#define RCPP__IOSTREAM__RSTREAMBUF_H

#include <cstdio>

#include <streambuf>

// modified from 
// http://stackoverflow.com/questions/243696/correctly-over-loading-a-stringbuf-to-replace-cout-in-a-matlab-mex-file

namespace Rcpp {

    template <bool OUTPUT>
    class Rstreambuf : public std::streambuf {
    public:
        Rstreambuf(){}
    	
    protected:
        virtual std::streamsize xsputn(const char *s, std::streamsize n ) override;
        
        virtual int overflow(int c = EOF ) override;
        
        virtual int sync() override  ;
    };

  
}

#endif
