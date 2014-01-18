// Copyright (C) 2014 Romain Francois

#ifndef Rcpp__traits__all_named__h
#define Rcpp__traits__all_named__h

namespace Rcpp{
    namespace traits{
        
        template <typename... Args> 
        struct all_named {
            typedef typename and_< typename is_named<Args>::type ... >::type type;
        } ;

    }
}

#endif

