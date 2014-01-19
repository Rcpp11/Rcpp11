.rcpp_error_recorder <- function(e){  
    invisible( .Call( rcpp_error_recorder, e ) )
}

