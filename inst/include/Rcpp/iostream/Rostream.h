#ifndef RCPP__IOSTREAM__ROSTREAM_H
#define RCPP__IOSTREAM__ROSTREAM_H

namespace Rcpp {   

    template <bool OUTPUT>
    class Rostream : public std::ostream {
        typedef Rstreambuf<OUTPUT> Buffer ; 
        Buffer* buf ;
    public:
        Rostream() : 
            std::ostream( new Buffer ), 
            buf( static_cast<Buffer*>( rdbuf() ) )
        {}
        ~Rostream() { 
            if (buf != NULL) {
                delete buf; 
                buf = NULL;
            }
        }
    };
    
}

#endif
