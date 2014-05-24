
#ifndef RCPP__complex_H
#define RCPP__complex_H

inline Rcomplex& operator+=( Rcomplex& lhs, const Rcomplex& rhs ){
    lhs.r += rhs.r ;
    lhs.i += rhs.i ;
    return lhs ;
}

// Rcomplex support
inline Rcomplex operator*( const Rcomplex& lhs, const Rcomplex& rhs){          
    Rcomplex y ;
    y.r = lhs.r * rhs.r - lhs.i * rhs.i ;
    y.i = lhs.r * rhs.i + rhs.r * lhs.i ;
    return y ;
}
inline Rcomplex operator+( const Rcomplex& lhs, const Rcomplex& rhs){
    Rcomplex y ;
    y.r = lhs.r + rhs.r ;
    y.i = lhs.i + rhs.i ;
    return y ;
}

inline Rcomplex operator-( const Rcomplex& lhs, const Rcomplex& rhs){
    Rcomplex y ;
    y.r = lhs.r - rhs.r ;
    y.i = lhs.i - rhs.i ;
    return y ;
}
 
inline Rcomplex operator-( const Rcomplex& lhs ){
    return Rcomplex{ -lhs.r, -lhs.i } ;    
}

inline Rcomplex operator/( const Rcomplex& a, const Rcomplex& b){
    Rcomplex c ;
    double ratio, den;
    double abr, abi;

    if( (abr = b.r) < 0) abr = - abr;
    if( (abi = b.i) < 0) abi = - abi;
    if( abr <= abi ) {
        ratio = b.r / b.i ;
        den = b.i * (1 + ratio*ratio);
        c.r = (a.r*ratio + a.i) / den;
        c.i = (a.i*ratio - a.r) / den;
    } else {
        ratio = b.i / b.r ;
        den = b.r * (1 + ratio*ratio);
        c.r = (a.r + a.i*ratio) / den;
        c.i = (a.i - a.r*ratio) / den;
    }
    return c ;  
}
inline Rcomplex operator/( Rcomplex a, double n){
    return Rcomplex{ a.r / n, a.i / n } ;
}

inline bool operator==( const Rcomplex& a, const Rcomplex& b){
    return a.r == b.r && a.i == b.i ;    
}

#endif
