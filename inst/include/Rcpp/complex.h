#ifndef RCPP__complex_H
#define RCPP__complex_H

inline Rcomplex& operator+=( Rcomplex& lhs, const Rcomplex& rhs ){
    lhs.r += rhs.r ;
    lhs.i += rhs.i ;
    return lhs ;
}

inline Rcomplex operator*( const Rcomplex& lhs, const Rcomplex& rhs){          
    return Rcomplex { lhs.r * rhs.r - lhs.i * rhs.i, lhs.r * rhs.i + rhs.r * lhs.i };
}
inline Rcomplex operator+( const Rcomplex& lhs, const Rcomplex& rhs){
    return Rcomplex { lhs.r + rhs.r, lhs.i + rhs.i } ;
}

inline Rcomplex operator-( const Rcomplex& lhs, const Rcomplex& rhs){
    return Rcomplex { lhs.r - rhs.r, lhs.i - rhs.i } ;
}
 
inline Rcomplex operator-( const Rcomplex& lhs ){
    return Rcomplex{ -lhs.r, -lhs.i } ;    
}

inline bool operator!( const Rcomplex& lhs ){
    return ( lhs.r != 0.0 || lhs.i != 0.0 ) ;    
}

inline Rcomplex operator/( const Rcomplex& a, const Rcomplex& b){
    double ratio, den;
    double abr, abi;

    if( (abr = b.r) < 0) abr = - abr;
    if( (abi = b.i) < 0) abi = - abi;
    if( abr <= abi ) {
        ratio = b.r / b.i ;
        den = b.i * (1 + ratio*ratio);
        return Rcomplex{
            (a.r*ratio + a.i) / den,
            (a.i*ratio - a.r) / den
        } ;
    } else {
        ratio = b.i / b.r ;
        den = b.r * (1 + ratio*ratio);
        return Rcomplex {
            (a.r + a.i*ratio) / den,
            (a.i - a.r*ratio) / den
        } ;
    }  
}
inline Rcomplex operator/( Rcomplex a, double n){
    return Rcomplex{ a.r / n, a.i / n } ;
}

inline bool operator==( const Rcomplex& a, const Rcomplex& b){
    return a.r == b.r && a.i == b.i ;    
}

#endif
