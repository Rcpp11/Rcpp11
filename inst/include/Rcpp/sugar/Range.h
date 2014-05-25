#ifndef RCPP_SUGAR_RANGE_H
#define RCPP_SUGAR_RANGE_H

namespace Rcpp{

    class Range : public SugarVectorExpression<INTSXP,false, Range >{
    public:
        Range( R_xlen_t start_, R_xlen_t end__ ) : start(start_), end_(end__){
            if( start_ > end__ ){
                throw std::range_error( "upper value must be greater than lower value" ) ;
            }
        }
                
        inline R_xlen_t size() const{
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
                
    private:
        R_xlen_t start, end_ ;
    } ;
        
} 

#endif
