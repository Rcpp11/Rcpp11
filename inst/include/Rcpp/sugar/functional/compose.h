#ifndef Rcpp__sugar__functional__compose_h
#define Rcpp__sugar__functional__compose_h

namespace Rcpp {
    namespace functional {

        template <typename F1, typename F2>
        class Compose : public Functoid<Compose<F1,F2>> {
        private:
            F1 f1 ;
            F2 f2 ;
        
        public:
            Compose( F1 f1_, F2 f2_ ) : f1(f1_), f2(f2_){}
        
            template <typename... Args>
            inline auto operator()( Args... args ) const -> decltype( f2( f1( args... ) ) ) {
                return f2( f1( args... ) );
            }
        
        } ;

    }

    template <typename F1, typename F2>
    inline functional::Compose<F1, F2> Compose( F1 f1, F2 f2){
        return functional::Compose<F1,F2>(f1,f2) ;
    }

    template <typename F1, typename F2>
    inline functional::Compose<F1,F2> operator>>( const functional::Functoid<F1>& f1, F2 f2 ){
        return functional::Compose<F1,F2>( f1.get_ref(), f2) ;
    }


} // end namespace Rcpp


#endif
