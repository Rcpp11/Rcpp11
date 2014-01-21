#ifndef Rcpp__macros_unroll_h
#define Rcpp__macros_unroll_h

#define RCPP_LOOP_UNROLL_LHSFUN(TARGET,FUN,SOURCE)           \
int __trip_count = n >> 2 ;                       \
int i = 0 ;                                       \
for ( ; __trip_count > 0 ; --__trip_count) {      \
	TARGET[FUN(i)] = SOURCE[i] ; i++ ;                 \
	TARGET[FUN(i)] = SOURCE[i] ; i++ ;                 \
	TARGET[FUN(i)] = SOURCE[i] ; i++ ;                 \
	TARGET[FUN(i)] = SOURCE[i] ; i++ ;                 \
}                                                 \
switch (n - i){                                   \
  case 3:                                         \
      TARGET[FUN(i)] = SOURCE[i] ; i++ ;               \
  case 2:                                         \
      TARGET[FUN(i)] = SOURCE[i] ; i++ ;               \
  case 1:                                         \
      TARGET[FUN(i)] = SOURCE[i] ; i++ ;               \
  case 0:                                         \
  default:                                        \
      {}                                          \
}

#endif
