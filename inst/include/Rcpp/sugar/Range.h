#ifndef RCPP_SUGAR_RANGE_H
#define RCPP_SUGAR_RANGE_H

namespace Rcpp{

    class Range : public SugarVectorExpression<INTSXP,false, Range >{
    public:
        Range( int start_, int end__ ) : start(start_), end_(end__){
            if( start_ > end__ ){
                throw std::range_error( "upper value must be greater than lower value" ) ;
            }
        }
                
        inline int size() const{
            return end_ - start + 1;
        }
                
        inline int operator[]( R_xlen_t i) const {
            return start + i ;
        }
                
        Range& operator++() {
            start++ ; end_++ ;
            return *this ;
        }
        Range operator++(int) {
            Range orig(*this) ;
            ++(*this);
            return orig ;
        }
                
        Range& operator--() {
            start-- ; end_-- ;
            return *this ;
        }
        Range operator--(int) {
            Range orig(*this) ;
            --(*this);
            return orig ;
        }
                
        Range& operator+=(int n) {
            start += n ; end_ += n ;
            return *this ;
        }
                
        Range& operator-=(int n) {
            start -= n ; end_ -= n ;
            return *this ;
        }
                
        Range operator+( int n ){
            return Range( start + n, end_ + n ) ;
        }
        Range operator-( int n ){
            return Range( start - n, end_ - n ) ;
        }
                
        inline int get_start() const { return start ; }
        inline int get_end() const { return end_ ; }
                
    private:
        int start ;
        int end_ ;
    } ;
        
} 

#endif
