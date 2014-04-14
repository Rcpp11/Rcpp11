#ifndef RCPP_TIMER_H
#define RCPP_TIMER_H

namespace Rcpp {

    template <typename Clock = std::chrono::high_resolution_clock>
    class Timer {
    public:
        typedef typename Clock::time_point time_point ;
        typedef std::pair<std::string,time_point> Step;
        typedef std::vector<Step> Steps;
        typedef std::chrono::duration<double, std::micro> microseconds ;
        
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
                res[i] = std::chrono::duration_cast<microseconds>( it->second - origin ).count() ;
                names[i] = it->first ;
            }
            res.names() = names ;
            return res ;
        }
        
        inline time_point now() const {
            return Clock::now() ;    
        }
        
        static std::vector<Timer> get_timers(int n){
            return std::vector<Timer>( n, Timer() ) ;    
        }
        
    private:
        
        Steps data ;
        time_point origin ;
        
    } ;
    
}
    
#endif

