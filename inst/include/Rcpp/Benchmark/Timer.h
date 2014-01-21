#ifndef RCPP_BENCHMARH_TIMER_H
#define RCPP_BENCHMARH_TIMER_H

#include <stdint.h>
#include <vector>
#include <string>

#define R_NO_REMAP
#include <Rinternals.h>

namespace Rcpp{

    nanotime_t get_nanotime(void); 
    
    class Timer {
    public:
        Timer() : data(), origin(get_nanotime()) {}
        Timer(nanotime_t origin_) : data(), origin(origin_) {}
        
        inline void step( const std::string& name ){
            data.emplace_back( std::make_pair( name, get_nanotime()-origin ) ) ;
        }
        
        operator SEXP() const {                                    
            NumericVector out = transform( data.begin(), data.end(), 
                [](Step pair){ return static_cast<double>(pair.second) ;}  ) ; 
            CharacterVector names = transform( data.begin(), data.end(), 
                [](Step pair){ return String(pair.first) ;} ) ;
            out.attr( "names" ) = names ;
            return out ;
        }
        
    private:
        typedef std::pair<std::string,nanotime_t> Step;
        typedef std::vector<Step> Steps;
        
        Steps data ;
        
        nanotime_t origin ;
        
    } ;
    
    inline std::vector<Timer> get_timers( int n ){
        return std::vector<Timer>(n, Timer(get_nanotime())) ;
    }
    
}
    
#endif

