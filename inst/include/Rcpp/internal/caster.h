#ifndef Rcpp__internal__caster__h
#define Rcpp__internal__caster__h

namespace Rcpp{
    namespace internal{
    
        template <typename FROM, typename TO> TO caster(FROM from){
            return static_cast<TO>(from) ;
        }
        template <> Rcomplex caster<int, Rcomplex>(int from){
            Rcomplex cx{ static_cast<double>(from), 0.0 } ;
            return cx ;
        }
        template <> Rcomplex caster<double, Rcomplex>(double from){
            Rcomplex cx{ from, 0.0 } ;
            return cx ;
        }
        
        template<> inline Rcomplex caster<std::complex<double>, Rcomplex>( std::complex<double> from){
            Rcomplex cx { from.real(), from.imag() };
            return cx ;
        } 
        template<> inline Rcomplex caster<std::complex<float>, Rcomplex>( std::complex<float> from){
            Rcomplex cx { static_cast<double>( from.real() ), static_cast<double>( from.imag() ) };
            return cx ;
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

