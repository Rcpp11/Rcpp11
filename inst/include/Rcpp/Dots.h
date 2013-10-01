// Copyright (C) 2013    Romain Francois
//
// This file is part of Rcpp11.
//
// Rcpp11 is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// Rcpp11 is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Rcpp11.  If not, see <http://www.gnu.org/licenses/>.

#ifndef Rcpp__Dots__h
#define Rcpp__Dots__h

namespace Rcpp{

    class Dots {
    public:
        
        Dots( List calls_, List frames_ ) : 
            calls(calls_), frames(frames_), env(0), exprs(0), tags(0)
        {
            init() ;
        }
            
        SEXP eval(int i){
            return Rf_eval( exprs[i], env[i] );   
        }
        
        SEXP envir(int i){
            return env[i] ;    
        }
        
        SEXP expr( int i ){ 
            return exprs[i] ;
        }
        
        inline size_t size() const{ return exprs.size(); } 
        
        
    private:
        
        void init(){
            process( frames.size() - 1 ) ;
        }
        
        void process(int i){
            if( i < 0 ) return ;
            SEXP p = calls[i] ;
            if( TYPEOF(p) != LANGSXP ) return ;
            
            p = CDR(p) ;
            SEXP head ;
            while( p != R_NilValue ){
                head = CAR(p) ;
                if( is_ellipsis(head) ) {
                    process(i-1) ;
                } else {
                    exprs.push_back( head ) ;
                    env.push_back( frames[i-1] ) ;
                    tags.push_back( TAG(p) );
                }
                p = CDR(p) ;
            }
        }
        
        bool is_ellipsis( SEXP x){
             return x == R_DotsSymbol ;   
        }
        
        List calls, frames ;
        // all of what we put in there is already protected by R. 
        std::vector<SEXP> env ;
        std::vector<SEXP> exprs ;
        std::vector<SEXP> tags ;
        
    } ;

} // Rcpp 

#endif
