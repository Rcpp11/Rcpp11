// Copyright (C) 2013 Romain Francois
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
                            
#ifndef Rcpp_Module__h
#define Rcpp_Module__h
     
template <typename Class>
Class* factory_new( Class* (*fun)(), SEXP* args, int nargs ){ return fun ; }

template <typename Class, typename U0>
Class* factory_new( Class* (*fun)(), SEXP* args, int nargs ){ 
    typename Rcpp::traits::input_parameter<U0>::type x0( args[0] ) ;
    return fun( x0 ) ;
}
template <typename Class, typename U0, typename U1>
Class* factory_new( Class* (*fun)(), SEXP* args, int nargs ){ 
    typename Rcpp::traits::input_parameter<U0>::type x0( args[0] ) ;
    typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
    return fun( x0, x1 ) ;
}
template <typename Class, typename U0, typename U1, typename U2>
Class* factory_new( Class* (*fun)(), SEXP* args, int nargs ){ 
    typename Rcpp::traits::input_parameter<U0>::type x0( args[0] ) ;
    typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
    typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
    return fun( x0, x1, x2 ) ;
}
template <typename Class, typename U0, typename U1, typename U2, typename U3>
Class* factory_new( Class* (*fun)(), SEXP* args, int nargs ){ 
    typename Rcpp::traits::input_parameter<U0>::type x0( args[0] ) ;
    typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
    typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
    typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
    return fun( x0, x1, x2, x3) ;
}
template <typename Class, typename U0, typename U1, typename U2, typename U3, typename U4>
Class* factory_new( Class* (*fun)(), SEXP* args, int nargs ){ 
    typename Rcpp::traits::input_parameter<U0>::type x0( args[0] ) ;
    typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
    typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
    typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
    typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
    return fun( x0, x1, x2, x3, x4) ;
}
template <typename Class, typename U0, typename U1, typename U2, typename U3, typename U4, typename U5>
Class* factory_new( Class* (*fun)(), SEXP* args, int nargs ){ 
    typename Rcpp::traits::input_parameter<U0>::type x0( args[0] ) ;
    typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
    typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
    typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
    typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
    typename Rcpp::traits::input_parameter<U4>::type x5( args[5] ) ;
    return fun( x0, x1, x2, x3, x4, x5) ;
}
template <typename Class, typename U0, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6>
Class* factory_new( Class* (*fun)(), SEXP* args, int nargs ){ 
    typename Rcpp::traits::input_parameter<U0>::type x0( args[0] ) ;
    typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
    typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
    typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
    typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
    typename Rcpp::traits::input_parameter<U4>::type x5( args[5] ) ;
    typename Rcpp::traits::input_parameter<U4>::type x6( args[6] ) ;
    return fun( x0, x1, x2, x3, x4, x5, x6) ;
}

#endif
