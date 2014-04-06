#ifndef RCPP_TIMER_H
#define RCPP_TIMER_H

namespace Rcpp {

    template <typename Clock>
    class Timer {
    public:
        using time_point = std::chrono::time_point<Clock> ;
        using Step  = std::pair<std::string,time_point>;
        using Steps = std::vector<Step> ;
        
        Timer(time_point origin_ ) : data(), origin(origin_){}
        Timer() : data(), origin(now()) {}
        
        inline void reset(){
            data.clear() ;
            origin = now() ;
        }
        
        inline void step( const std::string& name ){
            data.push_back( std::make_pair( name, now() ) ) ;
        }
        
        operator SEXP() const {
            int n = data.size() ;
            NumericVector res(n) ;
            CharacterVector names(n) ;
            auto it = data.begin() ;
            for( int i=0; i<n; i++, ++it){
                res[i] = static_cast<double>( 
                    std::chrono::duration_cast<std::chrono::microseconds>( it->second )
                ) ;
                names[i] = it->first ;
            }
            res.names() = names ;
            return res ;
        }
        
        inline time_point now() const {
            return time_point::now() ;    
        }
        
    private:
        
        Steps data ;
        time_point origin ;
        
    } ;
    
    template <typename Clock>
    inline std::vector<Timer<Clock>> get_timers( int n ){
        return std::vector<Timer<Clock>>(n, Timer<Clock>() ) ;
    }
    
}
    
#endif

