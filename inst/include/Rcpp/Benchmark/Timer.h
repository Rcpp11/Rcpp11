#ifndef RCPP_BENCHMARH_TIMER_H
#define RCPP_BENCHMARH_TIMER_H

#include <stdint.h>
#include <vector>
#include <string>

#define R_NO_REMAP
#include <Rinternals.h>

namespace Rcpp{

    nanotime_t get_nanotime(void); 
    
    namespace internal{
        String get_first( const std::pair<std::string,nanotime_t>& pair ){
            return pair.first ;    
        }
        double get_second( const std::pair<std::string,nanotime_t>& pair ){
            return static_cast<double>(pair.second) ;    
        }
    }
            
    class Timer {
    public:
        Timer() : data(), start_time( get_nanotime() ){}
        
        void step( const std::string& name ){
            nanotime_t now = get_nanotime() ;
            data.push_back( std::make_pair( name, now - start_time ) ) ;
            start_time = get_nanotime() ; 
        }
        
        operator SEXP() const {
            NumericVector out = transform( data.begin(), data.end(), internal::get_second ) ; 
            CharacterVector names = transform( data.begin(), data.end(), internal::get_first ) ;
            out.attr( "names" ) = names ;
            return out ;
        }
        
        void align_with( const Timer& other){
            start_time = other.start_time ;    
        }
        
        private:
            typedef std::pair<std::string,nanotime_t> Step;
            typedef std::vector<Step> Steps;
            
            Steps data ;
            nanotime_t start_time ;
            
    } ;
    
}
    
#endif

