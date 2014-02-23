# is set internally in R_init_Rcpp11
.rcpp_cache <- NULL

.rcpp_error_recorder <- function(e){  
  .rcpp_cache[[3L]] <- e
}

