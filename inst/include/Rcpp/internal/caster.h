#ifndef Rcpp__internal__caster__h
#define Rcpp__internal__caster__h

namespace Rcpp{
    namespace internal{
    
        template <typename FROM, typename TO> TO caster(FROM from){
            return static_cast<TO>(from) ;
        }
        template <> inline Rcomplex caster<int, Rcomplex>(int from){
            return Rcomplex { static_cast<double>(from), 0.0 } ;
        }
        template <> inline Rcomplex caster<double, Rcomplex>(double from){
            return Rcomplex{ from, 0.0 } ;
        }
        
        template<> inline Rcomplex caster<std::complex<double>, Rcomplex>( std::complex<double> from){
            return Rcomplex{ from.real(), from.imag() };
        } 
        template<> inline Rcomplex caster<std::complex<float>, Rcomplex>( std::complex<float> from){
            return Rcomplex{ static_cast<double>( from.real() ), static_cast<double>( from.imag() ) };
        }
        
        template<> inline std::complex<double> caster<Rcomplex,std::complex<double> >( Rcomplex from){
            return std::complex<double>(from.r, from.i ) ;    
        }
        template<> inline std::complex<float>  caster<Rcomplex,std::complex<float>  >( Rcomplex from){
            return std::complex<float>(static_cast<float>(from.r), static_cast<float>(from.i) ) ;    
        }
        
        template<> SEXP caster<String,SEXP>( String from ); 
    
    }
}

#endif

