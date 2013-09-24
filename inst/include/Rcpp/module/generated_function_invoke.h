
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

#ifndef Rcpp_Module_generated_function_invoke_h
#define Rcpp_Module_generated_function_invoke_h
     
template <typename OUT>
SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ return wrap(ptr_fun()) ; }


    template <typename OUT, typename U1>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        return wrap(ptr_fun(x1)) ;
    }
    

    template <typename OUT, typename U1, typename U2>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        return wrap(ptr_fun(x1, x2)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        return wrap(ptr_fun(x1, x2, x3)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4, typename U5>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        typename Rcpp::traits::input_parameter<U5>::type x5( args[5] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4, x5)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        typename Rcpp::traits::input_parameter<U5>::type x5( args[5] ) ;
        typename Rcpp::traits::input_parameter<U6>::type x6( args[6] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4, x5, x6)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        typename Rcpp::traits::input_parameter<U5>::type x5( args[5] ) ;
        typename Rcpp::traits::input_parameter<U6>::type x6( args[6] ) ;
        typename Rcpp::traits::input_parameter<U7>::type x7( args[7] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4, x5, x6, x7)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        typename Rcpp::traits::input_parameter<U5>::type x5( args[5] ) ;
        typename Rcpp::traits::input_parameter<U6>::type x6( args[6] ) ;
        typename Rcpp::traits::input_parameter<U7>::type x7( args[7] ) ;
        typename Rcpp::traits::input_parameter<U8>::type x8( args[8] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4, x5, x6, x7, x8)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        typename Rcpp::traits::input_parameter<U5>::type x5( args[5] ) ;
        typename Rcpp::traits::input_parameter<U6>::type x6( args[6] ) ;
        typename Rcpp::traits::input_parameter<U7>::type x7( args[7] ) ;
        typename Rcpp::traits::input_parameter<U8>::type x8( args[8] ) ;
        typename Rcpp::traits::input_parameter<U9>::type x9( args[9] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4, x5, x6, x7, x8, x9)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9, typename U10>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        typename Rcpp::traits::input_parameter<U5>::type x5( args[5] ) ;
        typename Rcpp::traits::input_parameter<U6>::type x6( args[6] ) ;
        typename Rcpp::traits::input_parameter<U7>::type x7( args[7] ) ;
        typename Rcpp::traits::input_parameter<U8>::type x8( args[8] ) ;
        typename Rcpp::traits::input_parameter<U9>::type x9( args[9] ) ;
        typename Rcpp::traits::input_parameter<U10>::type x10( args[10] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9, typename U10, typename U11>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        typename Rcpp::traits::input_parameter<U5>::type x5( args[5] ) ;
        typename Rcpp::traits::input_parameter<U6>::type x6( args[6] ) ;
        typename Rcpp::traits::input_parameter<U7>::type x7( args[7] ) ;
        typename Rcpp::traits::input_parameter<U8>::type x8( args[8] ) ;
        typename Rcpp::traits::input_parameter<U9>::type x9( args[9] ) ;
        typename Rcpp::traits::input_parameter<U10>::type x10( args[10] ) ;
        typename Rcpp::traits::input_parameter<U11>::type x11( args[11] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9, typename U10, typename U11, typename U12>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        typename Rcpp::traits::input_parameter<U5>::type x5( args[5] ) ;
        typename Rcpp::traits::input_parameter<U6>::type x6( args[6] ) ;
        typename Rcpp::traits::input_parameter<U7>::type x7( args[7] ) ;
        typename Rcpp::traits::input_parameter<U8>::type x8( args[8] ) ;
        typename Rcpp::traits::input_parameter<U9>::type x9( args[9] ) ;
        typename Rcpp::traits::input_parameter<U10>::type x10( args[10] ) ;
        typename Rcpp::traits::input_parameter<U11>::type x11( args[11] ) ;
        typename Rcpp::traits::input_parameter<U12>::type x12( args[12] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9, typename U10, typename U11, typename U12, typename U13>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        typename Rcpp::traits::input_parameter<U5>::type x5( args[5] ) ;
        typename Rcpp::traits::input_parameter<U6>::type x6( args[6] ) ;
        typename Rcpp::traits::input_parameter<U7>::type x7( args[7] ) ;
        typename Rcpp::traits::input_parameter<U8>::type x8( args[8] ) ;
        typename Rcpp::traits::input_parameter<U9>::type x9( args[9] ) ;
        typename Rcpp::traits::input_parameter<U10>::type x10( args[10] ) ;
        typename Rcpp::traits::input_parameter<U11>::type x11( args[11] ) ;
        typename Rcpp::traits::input_parameter<U12>::type x12( args[12] ) ;
        typename Rcpp::traits::input_parameter<U13>::type x13( args[13] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9, typename U10, typename U11, typename U12, typename U13, typename U14>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        typename Rcpp::traits::input_parameter<U5>::type x5( args[5] ) ;
        typename Rcpp::traits::input_parameter<U6>::type x6( args[6] ) ;
        typename Rcpp::traits::input_parameter<U7>::type x7( args[7] ) ;
        typename Rcpp::traits::input_parameter<U8>::type x8( args[8] ) ;
        typename Rcpp::traits::input_parameter<U9>::type x9( args[9] ) ;
        typename Rcpp::traits::input_parameter<U10>::type x10( args[10] ) ;
        typename Rcpp::traits::input_parameter<U11>::type x11( args[11] ) ;
        typename Rcpp::traits::input_parameter<U12>::type x12( args[12] ) ;
        typename Rcpp::traits::input_parameter<U13>::type x13( args[13] ) ;
        typename Rcpp::traits::input_parameter<U14>::type x14( args[14] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9, typename U10, typename U11, typename U12, typename U13, typename U14, typename U15>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        typename Rcpp::traits::input_parameter<U5>::type x5( args[5] ) ;
        typename Rcpp::traits::input_parameter<U6>::type x6( args[6] ) ;
        typename Rcpp::traits::input_parameter<U7>::type x7( args[7] ) ;
        typename Rcpp::traits::input_parameter<U8>::type x8( args[8] ) ;
        typename Rcpp::traits::input_parameter<U9>::type x9( args[9] ) ;
        typename Rcpp::traits::input_parameter<U10>::type x10( args[10] ) ;
        typename Rcpp::traits::input_parameter<U11>::type x11( args[11] ) ;
        typename Rcpp::traits::input_parameter<U12>::type x12( args[12] ) ;
        typename Rcpp::traits::input_parameter<U13>::type x13( args[13] ) ;
        typename Rcpp::traits::input_parameter<U14>::type x14( args[14] ) ;
        typename Rcpp::traits::input_parameter<U15>::type x15( args[15] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9, typename U10, typename U11, typename U12, typename U13, typename U14, typename U15, typename U16>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        typename Rcpp::traits::input_parameter<U5>::type x5( args[5] ) ;
        typename Rcpp::traits::input_parameter<U6>::type x6( args[6] ) ;
        typename Rcpp::traits::input_parameter<U7>::type x7( args[7] ) ;
        typename Rcpp::traits::input_parameter<U8>::type x8( args[8] ) ;
        typename Rcpp::traits::input_parameter<U9>::type x9( args[9] ) ;
        typename Rcpp::traits::input_parameter<U10>::type x10( args[10] ) ;
        typename Rcpp::traits::input_parameter<U11>::type x11( args[11] ) ;
        typename Rcpp::traits::input_parameter<U12>::type x12( args[12] ) ;
        typename Rcpp::traits::input_parameter<U13>::type x13( args[13] ) ;
        typename Rcpp::traits::input_parameter<U14>::type x14( args[14] ) ;
        typename Rcpp::traits::input_parameter<U15>::type x15( args[15] ) ;
        typename Rcpp::traits::input_parameter<U16>::type x16( args[16] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9, typename U10, typename U11, typename U12, typename U13, typename U14, typename U15, typename U16, typename U17>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        typename Rcpp::traits::input_parameter<U5>::type x5( args[5] ) ;
        typename Rcpp::traits::input_parameter<U6>::type x6( args[6] ) ;
        typename Rcpp::traits::input_parameter<U7>::type x7( args[7] ) ;
        typename Rcpp::traits::input_parameter<U8>::type x8( args[8] ) ;
        typename Rcpp::traits::input_parameter<U9>::type x9( args[9] ) ;
        typename Rcpp::traits::input_parameter<U10>::type x10( args[10] ) ;
        typename Rcpp::traits::input_parameter<U11>::type x11( args[11] ) ;
        typename Rcpp::traits::input_parameter<U12>::type x12( args[12] ) ;
        typename Rcpp::traits::input_parameter<U13>::type x13( args[13] ) ;
        typename Rcpp::traits::input_parameter<U14>::type x14( args[14] ) ;
        typename Rcpp::traits::input_parameter<U15>::type x15( args[15] ) ;
        typename Rcpp::traits::input_parameter<U16>::type x16( args[16] ) ;
        typename Rcpp::traits::input_parameter<U17>::type x17( args[17] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9, typename U10, typename U11, typename U12, typename U13, typename U14, typename U15, typename U16, typename U17, typename U18>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        typename Rcpp::traits::input_parameter<U5>::type x5( args[5] ) ;
        typename Rcpp::traits::input_parameter<U6>::type x6( args[6] ) ;
        typename Rcpp::traits::input_parameter<U7>::type x7( args[7] ) ;
        typename Rcpp::traits::input_parameter<U8>::type x8( args[8] ) ;
        typename Rcpp::traits::input_parameter<U9>::type x9( args[9] ) ;
        typename Rcpp::traits::input_parameter<U10>::type x10( args[10] ) ;
        typename Rcpp::traits::input_parameter<U11>::type x11( args[11] ) ;
        typename Rcpp::traits::input_parameter<U12>::type x12( args[12] ) ;
        typename Rcpp::traits::input_parameter<U13>::type x13( args[13] ) ;
        typename Rcpp::traits::input_parameter<U14>::type x14( args[14] ) ;
        typename Rcpp::traits::input_parameter<U15>::type x15( args[15] ) ;
        typename Rcpp::traits::input_parameter<U16>::type x16( args[16] ) ;
        typename Rcpp::traits::input_parameter<U17>::type x17( args[17] ) ;
        typename Rcpp::traits::input_parameter<U18>::type x18( args[18] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9, typename U10, typename U11, typename U12, typename U13, typename U14, typename U15, typename U16, typename U17, typename U18, typename U19>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        typename Rcpp::traits::input_parameter<U5>::type x5( args[5] ) ;
        typename Rcpp::traits::input_parameter<U6>::type x6( args[6] ) ;
        typename Rcpp::traits::input_parameter<U7>::type x7( args[7] ) ;
        typename Rcpp::traits::input_parameter<U8>::type x8( args[8] ) ;
        typename Rcpp::traits::input_parameter<U9>::type x9( args[9] ) ;
        typename Rcpp::traits::input_parameter<U10>::type x10( args[10] ) ;
        typename Rcpp::traits::input_parameter<U11>::type x11( args[11] ) ;
        typename Rcpp::traits::input_parameter<U12>::type x12( args[12] ) ;
        typename Rcpp::traits::input_parameter<U13>::type x13( args[13] ) ;
        typename Rcpp::traits::input_parameter<U14>::type x14( args[14] ) ;
        typename Rcpp::traits::input_parameter<U15>::type x15( args[15] ) ;
        typename Rcpp::traits::input_parameter<U16>::type x16( args[16] ) ;
        typename Rcpp::traits::input_parameter<U17>::type x17( args[17] ) ;
        typename Rcpp::traits::input_parameter<U18>::type x18( args[18] ) ;
        typename Rcpp::traits::input_parameter<U19>::type x19( args[19] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9, typename U10, typename U11, typename U12, typename U13, typename U14, typename U15, typename U16, typename U17, typename U18, typename U19, typename U20>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        typename Rcpp::traits::input_parameter<U5>::type x5( args[5] ) ;
        typename Rcpp::traits::input_parameter<U6>::type x6( args[6] ) ;
        typename Rcpp::traits::input_parameter<U7>::type x7( args[7] ) ;
        typename Rcpp::traits::input_parameter<U8>::type x8( args[8] ) ;
        typename Rcpp::traits::input_parameter<U9>::type x9( args[9] ) ;
        typename Rcpp::traits::input_parameter<U10>::type x10( args[10] ) ;
        typename Rcpp::traits::input_parameter<U11>::type x11( args[11] ) ;
        typename Rcpp::traits::input_parameter<U12>::type x12( args[12] ) ;
        typename Rcpp::traits::input_parameter<U13>::type x13( args[13] ) ;
        typename Rcpp::traits::input_parameter<U14>::type x14( args[14] ) ;
        typename Rcpp::traits::input_parameter<U15>::type x15( args[15] ) ;
        typename Rcpp::traits::input_parameter<U16>::type x16( args[16] ) ;
        typename Rcpp::traits::input_parameter<U17>::type x17( args[17] ) ;
        typename Rcpp::traits::input_parameter<U18>::type x18( args[18] ) ;
        typename Rcpp::traits::input_parameter<U19>::type x19( args[19] ) ;
        typename Rcpp::traits::input_parameter<U20>::type x20( args[20] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9, typename U10, typename U11, typename U12, typename U13, typename U14, typename U15, typename U16, typename U17, typename U18, typename U19, typename U20, typename U21>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        typename Rcpp::traits::input_parameter<U5>::type x5( args[5] ) ;
        typename Rcpp::traits::input_parameter<U6>::type x6( args[6] ) ;
        typename Rcpp::traits::input_parameter<U7>::type x7( args[7] ) ;
        typename Rcpp::traits::input_parameter<U8>::type x8( args[8] ) ;
        typename Rcpp::traits::input_parameter<U9>::type x9( args[9] ) ;
        typename Rcpp::traits::input_parameter<U10>::type x10( args[10] ) ;
        typename Rcpp::traits::input_parameter<U11>::type x11( args[11] ) ;
        typename Rcpp::traits::input_parameter<U12>::type x12( args[12] ) ;
        typename Rcpp::traits::input_parameter<U13>::type x13( args[13] ) ;
        typename Rcpp::traits::input_parameter<U14>::type x14( args[14] ) ;
        typename Rcpp::traits::input_parameter<U15>::type x15( args[15] ) ;
        typename Rcpp::traits::input_parameter<U16>::type x16( args[16] ) ;
        typename Rcpp::traits::input_parameter<U17>::type x17( args[17] ) ;
        typename Rcpp::traits::input_parameter<U18>::type x18( args[18] ) ;
        typename Rcpp::traits::input_parameter<U19>::type x19( args[19] ) ;
        typename Rcpp::traits::input_parameter<U20>::type x20( args[20] ) ;
        typename Rcpp::traits::input_parameter<U21>::type x21( args[21] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9, typename U10, typename U11, typename U12, typename U13, typename U14, typename U15, typename U16, typename U17, typename U18, typename U19, typename U20, typename U21, typename U22>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        typename Rcpp::traits::input_parameter<U5>::type x5( args[5] ) ;
        typename Rcpp::traits::input_parameter<U6>::type x6( args[6] ) ;
        typename Rcpp::traits::input_parameter<U7>::type x7( args[7] ) ;
        typename Rcpp::traits::input_parameter<U8>::type x8( args[8] ) ;
        typename Rcpp::traits::input_parameter<U9>::type x9( args[9] ) ;
        typename Rcpp::traits::input_parameter<U10>::type x10( args[10] ) ;
        typename Rcpp::traits::input_parameter<U11>::type x11( args[11] ) ;
        typename Rcpp::traits::input_parameter<U12>::type x12( args[12] ) ;
        typename Rcpp::traits::input_parameter<U13>::type x13( args[13] ) ;
        typename Rcpp::traits::input_parameter<U14>::type x14( args[14] ) ;
        typename Rcpp::traits::input_parameter<U15>::type x15( args[15] ) ;
        typename Rcpp::traits::input_parameter<U16>::type x16( args[16] ) ;
        typename Rcpp::traits::input_parameter<U17>::type x17( args[17] ) ;
        typename Rcpp::traits::input_parameter<U18>::type x18( args[18] ) ;
        typename Rcpp::traits::input_parameter<U19>::type x19( args[19] ) ;
        typename Rcpp::traits::input_parameter<U20>::type x20( args[20] ) ;
        typename Rcpp::traits::input_parameter<U21>::type x21( args[21] ) ;
        typename Rcpp::traits::input_parameter<U22>::type x22( args[22] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9, typename U10, typename U11, typename U12, typename U13, typename U14, typename U15, typename U16, typename U17, typename U18, typename U19, typename U20, typename U21, typename U22, typename U23>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        typename Rcpp::traits::input_parameter<U5>::type x5( args[5] ) ;
        typename Rcpp::traits::input_parameter<U6>::type x6( args[6] ) ;
        typename Rcpp::traits::input_parameter<U7>::type x7( args[7] ) ;
        typename Rcpp::traits::input_parameter<U8>::type x8( args[8] ) ;
        typename Rcpp::traits::input_parameter<U9>::type x9( args[9] ) ;
        typename Rcpp::traits::input_parameter<U10>::type x10( args[10] ) ;
        typename Rcpp::traits::input_parameter<U11>::type x11( args[11] ) ;
        typename Rcpp::traits::input_parameter<U12>::type x12( args[12] ) ;
        typename Rcpp::traits::input_parameter<U13>::type x13( args[13] ) ;
        typename Rcpp::traits::input_parameter<U14>::type x14( args[14] ) ;
        typename Rcpp::traits::input_parameter<U15>::type x15( args[15] ) ;
        typename Rcpp::traits::input_parameter<U16>::type x16( args[16] ) ;
        typename Rcpp::traits::input_parameter<U17>::type x17( args[17] ) ;
        typename Rcpp::traits::input_parameter<U18>::type x18( args[18] ) ;
        typename Rcpp::traits::input_parameter<U19>::type x19( args[19] ) ;
        typename Rcpp::traits::input_parameter<U20>::type x20( args[20] ) ;
        typename Rcpp::traits::input_parameter<U21>::type x21( args[21] ) ;
        typename Rcpp::traits::input_parameter<U22>::type x22( args[22] ) ;
        typename Rcpp::traits::input_parameter<U23>::type x23( args[23] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9, typename U10, typename U11, typename U12, typename U13, typename U14, typename U15, typename U16, typename U17, typename U18, typename U19, typename U20, typename U21, typename U22, typename U23, typename U24>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        typename Rcpp::traits::input_parameter<U5>::type x5( args[5] ) ;
        typename Rcpp::traits::input_parameter<U6>::type x6( args[6] ) ;
        typename Rcpp::traits::input_parameter<U7>::type x7( args[7] ) ;
        typename Rcpp::traits::input_parameter<U8>::type x8( args[8] ) ;
        typename Rcpp::traits::input_parameter<U9>::type x9( args[9] ) ;
        typename Rcpp::traits::input_parameter<U10>::type x10( args[10] ) ;
        typename Rcpp::traits::input_parameter<U11>::type x11( args[11] ) ;
        typename Rcpp::traits::input_parameter<U12>::type x12( args[12] ) ;
        typename Rcpp::traits::input_parameter<U13>::type x13( args[13] ) ;
        typename Rcpp::traits::input_parameter<U14>::type x14( args[14] ) ;
        typename Rcpp::traits::input_parameter<U15>::type x15( args[15] ) ;
        typename Rcpp::traits::input_parameter<U16>::type x16( args[16] ) ;
        typename Rcpp::traits::input_parameter<U17>::type x17( args[17] ) ;
        typename Rcpp::traits::input_parameter<U18>::type x18( args[18] ) ;
        typename Rcpp::traits::input_parameter<U19>::type x19( args[19] ) ;
        typename Rcpp::traits::input_parameter<U20>::type x20( args[20] ) ;
        typename Rcpp::traits::input_parameter<U21>::type x21( args[21] ) ;
        typename Rcpp::traits::input_parameter<U22>::type x22( args[22] ) ;
        typename Rcpp::traits::input_parameter<U23>::type x23( args[23] ) ;
        typename Rcpp::traits::input_parameter<U24>::type x24( args[24] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9, typename U10, typename U11, typename U12, typename U13, typename U14, typename U15, typename U16, typename U17, typename U18, typename U19, typename U20, typename U21, typename U22, typename U23, typename U24, typename U25>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        typename Rcpp::traits::input_parameter<U5>::type x5( args[5] ) ;
        typename Rcpp::traits::input_parameter<U6>::type x6( args[6] ) ;
        typename Rcpp::traits::input_parameter<U7>::type x7( args[7] ) ;
        typename Rcpp::traits::input_parameter<U8>::type x8( args[8] ) ;
        typename Rcpp::traits::input_parameter<U9>::type x9( args[9] ) ;
        typename Rcpp::traits::input_parameter<U10>::type x10( args[10] ) ;
        typename Rcpp::traits::input_parameter<U11>::type x11( args[11] ) ;
        typename Rcpp::traits::input_parameter<U12>::type x12( args[12] ) ;
        typename Rcpp::traits::input_parameter<U13>::type x13( args[13] ) ;
        typename Rcpp::traits::input_parameter<U14>::type x14( args[14] ) ;
        typename Rcpp::traits::input_parameter<U15>::type x15( args[15] ) ;
        typename Rcpp::traits::input_parameter<U16>::type x16( args[16] ) ;
        typename Rcpp::traits::input_parameter<U17>::type x17( args[17] ) ;
        typename Rcpp::traits::input_parameter<U18>::type x18( args[18] ) ;
        typename Rcpp::traits::input_parameter<U19>::type x19( args[19] ) ;
        typename Rcpp::traits::input_parameter<U20>::type x20( args[20] ) ;
        typename Rcpp::traits::input_parameter<U21>::type x21( args[21] ) ;
        typename Rcpp::traits::input_parameter<U22>::type x22( args[22] ) ;
        typename Rcpp::traits::input_parameter<U23>::type x23( args[23] ) ;
        typename Rcpp::traits::input_parameter<U24>::type x24( args[24] ) ;
        typename Rcpp::traits::input_parameter<U25>::type x25( args[25] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9, typename U10, typename U11, typename U12, typename U13, typename U14, typename U15, typename U16, typename U17, typename U18, typename U19, typename U20, typename U21, typename U22, typename U23, typename U24, typename U25, typename U26>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        typename Rcpp::traits::input_parameter<U5>::type x5( args[5] ) ;
        typename Rcpp::traits::input_parameter<U6>::type x6( args[6] ) ;
        typename Rcpp::traits::input_parameter<U7>::type x7( args[7] ) ;
        typename Rcpp::traits::input_parameter<U8>::type x8( args[8] ) ;
        typename Rcpp::traits::input_parameter<U9>::type x9( args[9] ) ;
        typename Rcpp::traits::input_parameter<U10>::type x10( args[10] ) ;
        typename Rcpp::traits::input_parameter<U11>::type x11( args[11] ) ;
        typename Rcpp::traits::input_parameter<U12>::type x12( args[12] ) ;
        typename Rcpp::traits::input_parameter<U13>::type x13( args[13] ) ;
        typename Rcpp::traits::input_parameter<U14>::type x14( args[14] ) ;
        typename Rcpp::traits::input_parameter<U15>::type x15( args[15] ) ;
        typename Rcpp::traits::input_parameter<U16>::type x16( args[16] ) ;
        typename Rcpp::traits::input_parameter<U17>::type x17( args[17] ) ;
        typename Rcpp::traits::input_parameter<U18>::type x18( args[18] ) ;
        typename Rcpp::traits::input_parameter<U19>::type x19( args[19] ) ;
        typename Rcpp::traits::input_parameter<U20>::type x20( args[20] ) ;
        typename Rcpp::traits::input_parameter<U21>::type x21( args[21] ) ;
        typename Rcpp::traits::input_parameter<U22>::type x22( args[22] ) ;
        typename Rcpp::traits::input_parameter<U23>::type x23( args[23] ) ;
        typename Rcpp::traits::input_parameter<U24>::type x24( args[24] ) ;
        typename Rcpp::traits::input_parameter<U25>::type x25( args[25] ) ;
        typename Rcpp::traits::input_parameter<U26>::type x26( args[26] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9, typename U10, typename U11, typename U12, typename U13, typename U14, typename U15, typename U16, typename U17, typename U18, typename U19, typename U20, typename U21, typename U22, typename U23, typename U24, typename U25, typename U26, typename U27>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        typename Rcpp::traits::input_parameter<U5>::type x5( args[5] ) ;
        typename Rcpp::traits::input_parameter<U6>::type x6( args[6] ) ;
        typename Rcpp::traits::input_parameter<U7>::type x7( args[7] ) ;
        typename Rcpp::traits::input_parameter<U8>::type x8( args[8] ) ;
        typename Rcpp::traits::input_parameter<U9>::type x9( args[9] ) ;
        typename Rcpp::traits::input_parameter<U10>::type x10( args[10] ) ;
        typename Rcpp::traits::input_parameter<U11>::type x11( args[11] ) ;
        typename Rcpp::traits::input_parameter<U12>::type x12( args[12] ) ;
        typename Rcpp::traits::input_parameter<U13>::type x13( args[13] ) ;
        typename Rcpp::traits::input_parameter<U14>::type x14( args[14] ) ;
        typename Rcpp::traits::input_parameter<U15>::type x15( args[15] ) ;
        typename Rcpp::traits::input_parameter<U16>::type x16( args[16] ) ;
        typename Rcpp::traits::input_parameter<U17>::type x17( args[17] ) ;
        typename Rcpp::traits::input_parameter<U18>::type x18( args[18] ) ;
        typename Rcpp::traits::input_parameter<U19>::type x19( args[19] ) ;
        typename Rcpp::traits::input_parameter<U20>::type x20( args[20] ) ;
        typename Rcpp::traits::input_parameter<U21>::type x21( args[21] ) ;
        typename Rcpp::traits::input_parameter<U22>::type x22( args[22] ) ;
        typename Rcpp::traits::input_parameter<U23>::type x23( args[23] ) ;
        typename Rcpp::traits::input_parameter<U24>::type x24( args[24] ) ;
        typename Rcpp::traits::input_parameter<U25>::type x25( args[25] ) ;
        typename Rcpp::traits::input_parameter<U26>::type x26( args[26] ) ;
        typename Rcpp::traits::input_parameter<U27>::type x27( args[27] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9, typename U10, typename U11, typename U12, typename U13, typename U14, typename U15, typename U16, typename U17, typename U18, typename U19, typename U20, typename U21, typename U22, typename U23, typename U24, typename U25, typename U26, typename U27, typename U28>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        typename Rcpp::traits::input_parameter<U5>::type x5( args[5] ) ;
        typename Rcpp::traits::input_parameter<U6>::type x6( args[6] ) ;
        typename Rcpp::traits::input_parameter<U7>::type x7( args[7] ) ;
        typename Rcpp::traits::input_parameter<U8>::type x8( args[8] ) ;
        typename Rcpp::traits::input_parameter<U9>::type x9( args[9] ) ;
        typename Rcpp::traits::input_parameter<U10>::type x10( args[10] ) ;
        typename Rcpp::traits::input_parameter<U11>::type x11( args[11] ) ;
        typename Rcpp::traits::input_parameter<U12>::type x12( args[12] ) ;
        typename Rcpp::traits::input_parameter<U13>::type x13( args[13] ) ;
        typename Rcpp::traits::input_parameter<U14>::type x14( args[14] ) ;
        typename Rcpp::traits::input_parameter<U15>::type x15( args[15] ) ;
        typename Rcpp::traits::input_parameter<U16>::type x16( args[16] ) ;
        typename Rcpp::traits::input_parameter<U17>::type x17( args[17] ) ;
        typename Rcpp::traits::input_parameter<U18>::type x18( args[18] ) ;
        typename Rcpp::traits::input_parameter<U19>::type x19( args[19] ) ;
        typename Rcpp::traits::input_parameter<U20>::type x20( args[20] ) ;
        typename Rcpp::traits::input_parameter<U21>::type x21( args[21] ) ;
        typename Rcpp::traits::input_parameter<U22>::type x22( args[22] ) ;
        typename Rcpp::traits::input_parameter<U23>::type x23( args[23] ) ;
        typename Rcpp::traits::input_parameter<U24>::type x24( args[24] ) ;
        typename Rcpp::traits::input_parameter<U25>::type x25( args[25] ) ;
        typename Rcpp::traits::input_parameter<U26>::type x26( args[26] ) ;
        typename Rcpp::traits::input_parameter<U27>::type x27( args[27] ) ;
        typename Rcpp::traits::input_parameter<U28>::type x28( args[28] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9, typename U10, typename U11, typename U12, typename U13, typename U14, typename U15, typename U16, typename U17, typename U18, typename U19, typename U20, typename U21, typename U22, typename U23, typename U24, typename U25, typename U26, typename U27, typename U28, typename U29>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        typename Rcpp::traits::input_parameter<U5>::type x5( args[5] ) ;
        typename Rcpp::traits::input_parameter<U6>::type x6( args[6] ) ;
        typename Rcpp::traits::input_parameter<U7>::type x7( args[7] ) ;
        typename Rcpp::traits::input_parameter<U8>::type x8( args[8] ) ;
        typename Rcpp::traits::input_parameter<U9>::type x9( args[9] ) ;
        typename Rcpp::traits::input_parameter<U10>::type x10( args[10] ) ;
        typename Rcpp::traits::input_parameter<U11>::type x11( args[11] ) ;
        typename Rcpp::traits::input_parameter<U12>::type x12( args[12] ) ;
        typename Rcpp::traits::input_parameter<U13>::type x13( args[13] ) ;
        typename Rcpp::traits::input_parameter<U14>::type x14( args[14] ) ;
        typename Rcpp::traits::input_parameter<U15>::type x15( args[15] ) ;
        typename Rcpp::traits::input_parameter<U16>::type x16( args[16] ) ;
        typename Rcpp::traits::input_parameter<U17>::type x17( args[17] ) ;
        typename Rcpp::traits::input_parameter<U18>::type x18( args[18] ) ;
        typename Rcpp::traits::input_parameter<U19>::type x19( args[19] ) ;
        typename Rcpp::traits::input_parameter<U20>::type x20( args[20] ) ;
        typename Rcpp::traits::input_parameter<U21>::type x21( args[21] ) ;
        typename Rcpp::traits::input_parameter<U22>::type x22( args[22] ) ;
        typename Rcpp::traits::input_parameter<U23>::type x23( args[23] ) ;
        typename Rcpp::traits::input_parameter<U24>::type x24( args[24] ) ;
        typename Rcpp::traits::input_parameter<U25>::type x25( args[25] ) ;
        typename Rcpp::traits::input_parameter<U26>::type x26( args[26] ) ;
        typename Rcpp::traits::input_parameter<U27>::type x27( args[27] ) ;
        typename Rcpp::traits::input_parameter<U28>::type x28( args[28] ) ;
        typename Rcpp::traits::input_parameter<U29>::type x29( args[29] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9, typename U10, typename U11, typename U12, typename U13, typename U14, typename U15, typename U16, typename U17, typename U18, typename U19, typename U20, typename U21, typename U22, typename U23, typename U24, typename U25, typename U26, typename U27, typename U28, typename U29, typename U30>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        typename Rcpp::traits::input_parameter<U5>::type x5( args[5] ) ;
        typename Rcpp::traits::input_parameter<U6>::type x6( args[6] ) ;
        typename Rcpp::traits::input_parameter<U7>::type x7( args[7] ) ;
        typename Rcpp::traits::input_parameter<U8>::type x8( args[8] ) ;
        typename Rcpp::traits::input_parameter<U9>::type x9( args[9] ) ;
        typename Rcpp::traits::input_parameter<U10>::type x10( args[10] ) ;
        typename Rcpp::traits::input_parameter<U11>::type x11( args[11] ) ;
        typename Rcpp::traits::input_parameter<U12>::type x12( args[12] ) ;
        typename Rcpp::traits::input_parameter<U13>::type x13( args[13] ) ;
        typename Rcpp::traits::input_parameter<U14>::type x14( args[14] ) ;
        typename Rcpp::traits::input_parameter<U15>::type x15( args[15] ) ;
        typename Rcpp::traits::input_parameter<U16>::type x16( args[16] ) ;
        typename Rcpp::traits::input_parameter<U17>::type x17( args[17] ) ;
        typename Rcpp::traits::input_parameter<U18>::type x18( args[18] ) ;
        typename Rcpp::traits::input_parameter<U19>::type x19( args[19] ) ;
        typename Rcpp::traits::input_parameter<U20>::type x20( args[20] ) ;
        typename Rcpp::traits::input_parameter<U21>::type x21( args[21] ) ;
        typename Rcpp::traits::input_parameter<U22>::type x22( args[22] ) ;
        typename Rcpp::traits::input_parameter<U23>::type x23( args[23] ) ;
        typename Rcpp::traits::input_parameter<U24>::type x24( args[24] ) ;
        typename Rcpp::traits::input_parameter<U25>::type x25( args[25] ) ;
        typename Rcpp::traits::input_parameter<U26>::type x26( args[26] ) ;
        typename Rcpp::traits::input_parameter<U27>::type x27( args[27] ) ;
        typename Rcpp::traits::input_parameter<U28>::type x28( args[28] ) ;
        typename Rcpp::traits::input_parameter<U29>::type x29( args[29] ) ;
        typename Rcpp::traits::input_parameter<U30>::type x30( args[30] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9, typename U10, typename U11, typename U12, typename U13, typename U14, typename U15, typename U16, typename U17, typename U18, typename U19, typename U20, typename U21, typename U22, typename U23, typename U24, typename U25, typename U26, typename U27, typename U28, typename U29, typename U30, typename U31>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        typename Rcpp::traits::input_parameter<U5>::type x5( args[5] ) ;
        typename Rcpp::traits::input_parameter<U6>::type x6( args[6] ) ;
        typename Rcpp::traits::input_parameter<U7>::type x7( args[7] ) ;
        typename Rcpp::traits::input_parameter<U8>::type x8( args[8] ) ;
        typename Rcpp::traits::input_parameter<U9>::type x9( args[9] ) ;
        typename Rcpp::traits::input_parameter<U10>::type x10( args[10] ) ;
        typename Rcpp::traits::input_parameter<U11>::type x11( args[11] ) ;
        typename Rcpp::traits::input_parameter<U12>::type x12( args[12] ) ;
        typename Rcpp::traits::input_parameter<U13>::type x13( args[13] ) ;
        typename Rcpp::traits::input_parameter<U14>::type x14( args[14] ) ;
        typename Rcpp::traits::input_parameter<U15>::type x15( args[15] ) ;
        typename Rcpp::traits::input_parameter<U16>::type x16( args[16] ) ;
        typename Rcpp::traits::input_parameter<U17>::type x17( args[17] ) ;
        typename Rcpp::traits::input_parameter<U18>::type x18( args[18] ) ;
        typename Rcpp::traits::input_parameter<U19>::type x19( args[19] ) ;
        typename Rcpp::traits::input_parameter<U20>::type x20( args[20] ) ;
        typename Rcpp::traits::input_parameter<U21>::type x21( args[21] ) ;
        typename Rcpp::traits::input_parameter<U22>::type x22( args[22] ) ;
        typename Rcpp::traits::input_parameter<U23>::type x23( args[23] ) ;
        typename Rcpp::traits::input_parameter<U24>::type x24( args[24] ) ;
        typename Rcpp::traits::input_parameter<U25>::type x25( args[25] ) ;
        typename Rcpp::traits::input_parameter<U26>::type x26( args[26] ) ;
        typename Rcpp::traits::input_parameter<U27>::type x27( args[27] ) ;
        typename Rcpp::traits::input_parameter<U28>::type x28( args[28] ) ;
        typename Rcpp::traits::input_parameter<U29>::type x29( args[29] ) ;
        typename Rcpp::traits::input_parameter<U30>::type x30( args[30] ) ;
        typename Rcpp::traits::input_parameter<U31>::type x31( args[31] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9, typename U10, typename U11, typename U12, typename U13, typename U14, typename U15, typename U16, typename U17, typename U18, typename U19, typename U20, typename U21, typename U22, typename U23, typename U24, typename U25, typename U26, typename U27, typename U28, typename U29, typename U30, typename U31, typename U32>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        typename Rcpp::traits::input_parameter<U5>::type x5( args[5] ) ;
        typename Rcpp::traits::input_parameter<U6>::type x6( args[6] ) ;
        typename Rcpp::traits::input_parameter<U7>::type x7( args[7] ) ;
        typename Rcpp::traits::input_parameter<U8>::type x8( args[8] ) ;
        typename Rcpp::traits::input_parameter<U9>::type x9( args[9] ) ;
        typename Rcpp::traits::input_parameter<U10>::type x10( args[10] ) ;
        typename Rcpp::traits::input_parameter<U11>::type x11( args[11] ) ;
        typename Rcpp::traits::input_parameter<U12>::type x12( args[12] ) ;
        typename Rcpp::traits::input_parameter<U13>::type x13( args[13] ) ;
        typename Rcpp::traits::input_parameter<U14>::type x14( args[14] ) ;
        typename Rcpp::traits::input_parameter<U15>::type x15( args[15] ) ;
        typename Rcpp::traits::input_parameter<U16>::type x16( args[16] ) ;
        typename Rcpp::traits::input_parameter<U17>::type x17( args[17] ) ;
        typename Rcpp::traits::input_parameter<U18>::type x18( args[18] ) ;
        typename Rcpp::traits::input_parameter<U19>::type x19( args[19] ) ;
        typename Rcpp::traits::input_parameter<U20>::type x20( args[20] ) ;
        typename Rcpp::traits::input_parameter<U21>::type x21( args[21] ) ;
        typename Rcpp::traits::input_parameter<U22>::type x22( args[22] ) ;
        typename Rcpp::traits::input_parameter<U23>::type x23( args[23] ) ;
        typename Rcpp::traits::input_parameter<U24>::type x24( args[24] ) ;
        typename Rcpp::traits::input_parameter<U25>::type x25( args[25] ) ;
        typename Rcpp::traits::input_parameter<U26>::type x26( args[26] ) ;
        typename Rcpp::traits::input_parameter<U27>::type x27( args[27] ) ;
        typename Rcpp::traits::input_parameter<U28>::type x28( args[28] ) ;
        typename Rcpp::traits::input_parameter<U29>::type x29( args[29] ) ;
        typename Rcpp::traits::input_parameter<U30>::type x30( args[30] ) ;
        typename Rcpp::traits::input_parameter<U31>::type x31( args[31] ) ;
        typename Rcpp::traits::input_parameter<U32>::type x32( args[32] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9, typename U10, typename U11, typename U12, typename U13, typename U14, typename U15, typename U16, typename U17, typename U18, typename U19, typename U20, typename U21, typename U22, typename U23, typename U24, typename U25, typename U26, typename U27, typename U28, typename U29, typename U30, typename U31, typename U32, typename U33>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        typename Rcpp::traits::input_parameter<U5>::type x5( args[5] ) ;
        typename Rcpp::traits::input_parameter<U6>::type x6( args[6] ) ;
        typename Rcpp::traits::input_parameter<U7>::type x7( args[7] ) ;
        typename Rcpp::traits::input_parameter<U8>::type x8( args[8] ) ;
        typename Rcpp::traits::input_parameter<U9>::type x9( args[9] ) ;
        typename Rcpp::traits::input_parameter<U10>::type x10( args[10] ) ;
        typename Rcpp::traits::input_parameter<U11>::type x11( args[11] ) ;
        typename Rcpp::traits::input_parameter<U12>::type x12( args[12] ) ;
        typename Rcpp::traits::input_parameter<U13>::type x13( args[13] ) ;
        typename Rcpp::traits::input_parameter<U14>::type x14( args[14] ) ;
        typename Rcpp::traits::input_parameter<U15>::type x15( args[15] ) ;
        typename Rcpp::traits::input_parameter<U16>::type x16( args[16] ) ;
        typename Rcpp::traits::input_parameter<U17>::type x17( args[17] ) ;
        typename Rcpp::traits::input_parameter<U18>::type x18( args[18] ) ;
        typename Rcpp::traits::input_parameter<U19>::type x19( args[19] ) ;
        typename Rcpp::traits::input_parameter<U20>::type x20( args[20] ) ;
        typename Rcpp::traits::input_parameter<U21>::type x21( args[21] ) ;
        typename Rcpp::traits::input_parameter<U22>::type x22( args[22] ) ;
        typename Rcpp::traits::input_parameter<U23>::type x23( args[23] ) ;
        typename Rcpp::traits::input_parameter<U24>::type x24( args[24] ) ;
        typename Rcpp::traits::input_parameter<U25>::type x25( args[25] ) ;
        typename Rcpp::traits::input_parameter<U26>::type x26( args[26] ) ;
        typename Rcpp::traits::input_parameter<U27>::type x27( args[27] ) ;
        typename Rcpp::traits::input_parameter<U28>::type x28( args[28] ) ;
        typename Rcpp::traits::input_parameter<U29>::type x29( args[29] ) ;
        typename Rcpp::traits::input_parameter<U30>::type x30( args[30] ) ;
        typename Rcpp::traits::input_parameter<U31>::type x31( args[31] ) ;
        typename Rcpp::traits::input_parameter<U32>::type x32( args[32] ) ;
        typename Rcpp::traits::input_parameter<U33>::type x33( args[33] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9, typename U10, typename U11, typename U12, typename U13, typename U14, typename U15, typename U16, typename U17, typename U18, typename U19, typename U20, typename U21, typename U22, typename U23, typename U24, typename U25, typename U26, typename U27, typename U28, typename U29, typename U30, typename U31, typename U32, typename U33, typename U34>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        typename Rcpp::traits::input_parameter<U5>::type x5( args[5] ) ;
        typename Rcpp::traits::input_parameter<U6>::type x6( args[6] ) ;
        typename Rcpp::traits::input_parameter<U7>::type x7( args[7] ) ;
        typename Rcpp::traits::input_parameter<U8>::type x8( args[8] ) ;
        typename Rcpp::traits::input_parameter<U9>::type x9( args[9] ) ;
        typename Rcpp::traits::input_parameter<U10>::type x10( args[10] ) ;
        typename Rcpp::traits::input_parameter<U11>::type x11( args[11] ) ;
        typename Rcpp::traits::input_parameter<U12>::type x12( args[12] ) ;
        typename Rcpp::traits::input_parameter<U13>::type x13( args[13] ) ;
        typename Rcpp::traits::input_parameter<U14>::type x14( args[14] ) ;
        typename Rcpp::traits::input_parameter<U15>::type x15( args[15] ) ;
        typename Rcpp::traits::input_parameter<U16>::type x16( args[16] ) ;
        typename Rcpp::traits::input_parameter<U17>::type x17( args[17] ) ;
        typename Rcpp::traits::input_parameter<U18>::type x18( args[18] ) ;
        typename Rcpp::traits::input_parameter<U19>::type x19( args[19] ) ;
        typename Rcpp::traits::input_parameter<U20>::type x20( args[20] ) ;
        typename Rcpp::traits::input_parameter<U21>::type x21( args[21] ) ;
        typename Rcpp::traits::input_parameter<U22>::type x22( args[22] ) ;
        typename Rcpp::traits::input_parameter<U23>::type x23( args[23] ) ;
        typename Rcpp::traits::input_parameter<U24>::type x24( args[24] ) ;
        typename Rcpp::traits::input_parameter<U25>::type x25( args[25] ) ;
        typename Rcpp::traits::input_parameter<U26>::type x26( args[26] ) ;
        typename Rcpp::traits::input_parameter<U27>::type x27( args[27] ) ;
        typename Rcpp::traits::input_parameter<U28>::type x28( args[28] ) ;
        typename Rcpp::traits::input_parameter<U29>::type x29( args[29] ) ;
        typename Rcpp::traits::input_parameter<U30>::type x30( args[30] ) ;
        typename Rcpp::traits::input_parameter<U31>::type x31( args[31] ) ;
        typename Rcpp::traits::input_parameter<U32>::type x32( args[32] ) ;
        typename Rcpp::traits::input_parameter<U33>::type x33( args[33] ) ;
        typename Rcpp::traits::input_parameter<U34>::type x34( args[34] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9, typename U10, typename U11, typename U12, typename U13, typename U14, typename U15, typename U16, typename U17, typename U18, typename U19, typename U20, typename U21, typename U22, typename U23, typename U24, typename U25, typename U26, typename U27, typename U28, typename U29, typename U30, typename U31, typename U32, typename U33, typename U34, typename U35>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        typename Rcpp::traits::input_parameter<U5>::type x5( args[5] ) ;
        typename Rcpp::traits::input_parameter<U6>::type x6( args[6] ) ;
        typename Rcpp::traits::input_parameter<U7>::type x7( args[7] ) ;
        typename Rcpp::traits::input_parameter<U8>::type x8( args[8] ) ;
        typename Rcpp::traits::input_parameter<U9>::type x9( args[9] ) ;
        typename Rcpp::traits::input_parameter<U10>::type x10( args[10] ) ;
        typename Rcpp::traits::input_parameter<U11>::type x11( args[11] ) ;
        typename Rcpp::traits::input_parameter<U12>::type x12( args[12] ) ;
        typename Rcpp::traits::input_parameter<U13>::type x13( args[13] ) ;
        typename Rcpp::traits::input_parameter<U14>::type x14( args[14] ) ;
        typename Rcpp::traits::input_parameter<U15>::type x15( args[15] ) ;
        typename Rcpp::traits::input_parameter<U16>::type x16( args[16] ) ;
        typename Rcpp::traits::input_parameter<U17>::type x17( args[17] ) ;
        typename Rcpp::traits::input_parameter<U18>::type x18( args[18] ) ;
        typename Rcpp::traits::input_parameter<U19>::type x19( args[19] ) ;
        typename Rcpp::traits::input_parameter<U20>::type x20( args[20] ) ;
        typename Rcpp::traits::input_parameter<U21>::type x21( args[21] ) ;
        typename Rcpp::traits::input_parameter<U22>::type x22( args[22] ) ;
        typename Rcpp::traits::input_parameter<U23>::type x23( args[23] ) ;
        typename Rcpp::traits::input_parameter<U24>::type x24( args[24] ) ;
        typename Rcpp::traits::input_parameter<U25>::type x25( args[25] ) ;
        typename Rcpp::traits::input_parameter<U26>::type x26( args[26] ) ;
        typename Rcpp::traits::input_parameter<U27>::type x27( args[27] ) ;
        typename Rcpp::traits::input_parameter<U28>::type x28( args[28] ) ;
        typename Rcpp::traits::input_parameter<U29>::type x29( args[29] ) ;
        typename Rcpp::traits::input_parameter<U30>::type x30( args[30] ) ;
        typename Rcpp::traits::input_parameter<U31>::type x31( args[31] ) ;
        typename Rcpp::traits::input_parameter<U32>::type x32( args[32] ) ;
        typename Rcpp::traits::input_parameter<U33>::type x33( args[33] ) ;
        typename Rcpp::traits::input_parameter<U34>::type x34( args[34] ) ;
        typename Rcpp::traits::input_parameter<U35>::type x35( args[35] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9, typename U10, typename U11, typename U12, typename U13, typename U14, typename U15, typename U16, typename U17, typename U18, typename U19, typename U20, typename U21, typename U22, typename U23, typename U24, typename U25, typename U26, typename U27, typename U28, typename U29, typename U30, typename U31, typename U32, typename U33, typename U34, typename U35, typename U36>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        typename Rcpp::traits::input_parameter<U5>::type x5( args[5] ) ;
        typename Rcpp::traits::input_parameter<U6>::type x6( args[6] ) ;
        typename Rcpp::traits::input_parameter<U7>::type x7( args[7] ) ;
        typename Rcpp::traits::input_parameter<U8>::type x8( args[8] ) ;
        typename Rcpp::traits::input_parameter<U9>::type x9( args[9] ) ;
        typename Rcpp::traits::input_parameter<U10>::type x10( args[10] ) ;
        typename Rcpp::traits::input_parameter<U11>::type x11( args[11] ) ;
        typename Rcpp::traits::input_parameter<U12>::type x12( args[12] ) ;
        typename Rcpp::traits::input_parameter<U13>::type x13( args[13] ) ;
        typename Rcpp::traits::input_parameter<U14>::type x14( args[14] ) ;
        typename Rcpp::traits::input_parameter<U15>::type x15( args[15] ) ;
        typename Rcpp::traits::input_parameter<U16>::type x16( args[16] ) ;
        typename Rcpp::traits::input_parameter<U17>::type x17( args[17] ) ;
        typename Rcpp::traits::input_parameter<U18>::type x18( args[18] ) ;
        typename Rcpp::traits::input_parameter<U19>::type x19( args[19] ) ;
        typename Rcpp::traits::input_parameter<U20>::type x20( args[20] ) ;
        typename Rcpp::traits::input_parameter<U21>::type x21( args[21] ) ;
        typename Rcpp::traits::input_parameter<U22>::type x22( args[22] ) ;
        typename Rcpp::traits::input_parameter<U23>::type x23( args[23] ) ;
        typename Rcpp::traits::input_parameter<U24>::type x24( args[24] ) ;
        typename Rcpp::traits::input_parameter<U25>::type x25( args[25] ) ;
        typename Rcpp::traits::input_parameter<U26>::type x26( args[26] ) ;
        typename Rcpp::traits::input_parameter<U27>::type x27( args[27] ) ;
        typename Rcpp::traits::input_parameter<U28>::type x28( args[28] ) ;
        typename Rcpp::traits::input_parameter<U29>::type x29( args[29] ) ;
        typename Rcpp::traits::input_parameter<U30>::type x30( args[30] ) ;
        typename Rcpp::traits::input_parameter<U31>::type x31( args[31] ) ;
        typename Rcpp::traits::input_parameter<U32>::type x32( args[32] ) ;
        typename Rcpp::traits::input_parameter<U33>::type x33( args[33] ) ;
        typename Rcpp::traits::input_parameter<U34>::type x34( args[34] ) ;
        typename Rcpp::traits::input_parameter<U35>::type x35( args[35] ) ;
        typename Rcpp::traits::input_parameter<U36>::type x36( args[36] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9, typename U10, typename U11, typename U12, typename U13, typename U14, typename U15, typename U16, typename U17, typename U18, typename U19, typename U20, typename U21, typename U22, typename U23, typename U24, typename U25, typename U26, typename U27, typename U28, typename U29, typename U30, typename U31, typename U32, typename U33, typename U34, typename U35, typename U36, typename U37>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        typename Rcpp::traits::input_parameter<U5>::type x5( args[5] ) ;
        typename Rcpp::traits::input_parameter<U6>::type x6( args[6] ) ;
        typename Rcpp::traits::input_parameter<U7>::type x7( args[7] ) ;
        typename Rcpp::traits::input_parameter<U8>::type x8( args[8] ) ;
        typename Rcpp::traits::input_parameter<U9>::type x9( args[9] ) ;
        typename Rcpp::traits::input_parameter<U10>::type x10( args[10] ) ;
        typename Rcpp::traits::input_parameter<U11>::type x11( args[11] ) ;
        typename Rcpp::traits::input_parameter<U12>::type x12( args[12] ) ;
        typename Rcpp::traits::input_parameter<U13>::type x13( args[13] ) ;
        typename Rcpp::traits::input_parameter<U14>::type x14( args[14] ) ;
        typename Rcpp::traits::input_parameter<U15>::type x15( args[15] ) ;
        typename Rcpp::traits::input_parameter<U16>::type x16( args[16] ) ;
        typename Rcpp::traits::input_parameter<U17>::type x17( args[17] ) ;
        typename Rcpp::traits::input_parameter<U18>::type x18( args[18] ) ;
        typename Rcpp::traits::input_parameter<U19>::type x19( args[19] ) ;
        typename Rcpp::traits::input_parameter<U20>::type x20( args[20] ) ;
        typename Rcpp::traits::input_parameter<U21>::type x21( args[21] ) ;
        typename Rcpp::traits::input_parameter<U22>::type x22( args[22] ) ;
        typename Rcpp::traits::input_parameter<U23>::type x23( args[23] ) ;
        typename Rcpp::traits::input_parameter<U24>::type x24( args[24] ) ;
        typename Rcpp::traits::input_parameter<U25>::type x25( args[25] ) ;
        typename Rcpp::traits::input_parameter<U26>::type x26( args[26] ) ;
        typename Rcpp::traits::input_parameter<U27>::type x27( args[27] ) ;
        typename Rcpp::traits::input_parameter<U28>::type x28( args[28] ) ;
        typename Rcpp::traits::input_parameter<U29>::type x29( args[29] ) ;
        typename Rcpp::traits::input_parameter<U30>::type x30( args[30] ) ;
        typename Rcpp::traits::input_parameter<U31>::type x31( args[31] ) ;
        typename Rcpp::traits::input_parameter<U32>::type x32( args[32] ) ;
        typename Rcpp::traits::input_parameter<U33>::type x33( args[33] ) ;
        typename Rcpp::traits::input_parameter<U34>::type x34( args[34] ) ;
        typename Rcpp::traits::input_parameter<U35>::type x35( args[35] ) ;
        typename Rcpp::traits::input_parameter<U36>::type x36( args[36] ) ;
        typename Rcpp::traits::input_parameter<U37>::type x37( args[37] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9, typename U10, typename U11, typename U12, typename U13, typename U14, typename U15, typename U16, typename U17, typename U18, typename U19, typename U20, typename U21, typename U22, typename U23, typename U24, typename U25, typename U26, typename U27, typename U28, typename U29, typename U30, typename U31, typename U32, typename U33, typename U34, typename U35, typename U36, typename U37, typename U38>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        typename Rcpp::traits::input_parameter<U5>::type x5( args[5] ) ;
        typename Rcpp::traits::input_parameter<U6>::type x6( args[6] ) ;
        typename Rcpp::traits::input_parameter<U7>::type x7( args[7] ) ;
        typename Rcpp::traits::input_parameter<U8>::type x8( args[8] ) ;
        typename Rcpp::traits::input_parameter<U9>::type x9( args[9] ) ;
        typename Rcpp::traits::input_parameter<U10>::type x10( args[10] ) ;
        typename Rcpp::traits::input_parameter<U11>::type x11( args[11] ) ;
        typename Rcpp::traits::input_parameter<U12>::type x12( args[12] ) ;
        typename Rcpp::traits::input_parameter<U13>::type x13( args[13] ) ;
        typename Rcpp::traits::input_parameter<U14>::type x14( args[14] ) ;
        typename Rcpp::traits::input_parameter<U15>::type x15( args[15] ) ;
        typename Rcpp::traits::input_parameter<U16>::type x16( args[16] ) ;
        typename Rcpp::traits::input_parameter<U17>::type x17( args[17] ) ;
        typename Rcpp::traits::input_parameter<U18>::type x18( args[18] ) ;
        typename Rcpp::traits::input_parameter<U19>::type x19( args[19] ) ;
        typename Rcpp::traits::input_parameter<U20>::type x20( args[20] ) ;
        typename Rcpp::traits::input_parameter<U21>::type x21( args[21] ) ;
        typename Rcpp::traits::input_parameter<U22>::type x22( args[22] ) ;
        typename Rcpp::traits::input_parameter<U23>::type x23( args[23] ) ;
        typename Rcpp::traits::input_parameter<U24>::type x24( args[24] ) ;
        typename Rcpp::traits::input_parameter<U25>::type x25( args[25] ) ;
        typename Rcpp::traits::input_parameter<U26>::type x26( args[26] ) ;
        typename Rcpp::traits::input_parameter<U27>::type x27( args[27] ) ;
        typename Rcpp::traits::input_parameter<U28>::type x28( args[28] ) ;
        typename Rcpp::traits::input_parameter<U29>::type x29( args[29] ) ;
        typename Rcpp::traits::input_parameter<U30>::type x30( args[30] ) ;
        typename Rcpp::traits::input_parameter<U31>::type x31( args[31] ) ;
        typename Rcpp::traits::input_parameter<U32>::type x32( args[32] ) ;
        typename Rcpp::traits::input_parameter<U33>::type x33( args[33] ) ;
        typename Rcpp::traits::input_parameter<U34>::type x34( args[34] ) ;
        typename Rcpp::traits::input_parameter<U35>::type x35( args[35] ) ;
        typename Rcpp::traits::input_parameter<U36>::type x36( args[36] ) ;
        typename Rcpp::traits::input_parameter<U37>::type x37( args[37] ) ;
        typename Rcpp::traits::input_parameter<U38>::type x38( args[38] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9, typename U10, typename U11, typename U12, typename U13, typename U14, typename U15, typename U16, typename U17, typename U18, typename U19, typename U20, typename U21, typename U22, typename U23, typename U24, typename U25, typename U26, typename U27, typename U28, typename U29, typename U30, typename U31, typename U32, typename U33, typename U34, typename U35, typename U36, typename U37, typename U38, typename U39>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        typename Rcpp::traits::input_parameter<U5>::type x5( args[5] ) ;
        typename Rcpp::traits::input_parameter<U6>::type x6( args[6] ) ;
        typename Rcpp::traits::input_parameter<U7>::type x7( args[7] ) ;
        typename Rcpp::traits::input_parameter<U8>::type x8( args[8] ) ;
        typename Rcpp::traits::input_parameter<U9>::type x9( args[9] ) ;
        typename Rcpp::traits::input_parameter<U10>::type x10( args[10] ) ;
        typename Rcpp::traits::input_parameter<U11>::type x11( args[11] ) ;
        typename Rcpp::traits::input_parameter<U12>::type x12( args[12] ) ;
        typename Rcpp::traits::input_parameter<U13>::type x13( args[13] ) ;
        typename Rcpp::traits::input_parameter<U14>::type x14( args[14] ) ;
        typename Rcpp::traits::input_parameter<U15>::type x15( args[15] ) ;
        typename Rcpp::traits::input_parameter<U16>::type x16( args[16] ) ;
        typename Rcpp::traits::input_parameter<U17>::type x17( args[17] ) ;
        typename Rcpp::traits::input_parameter<U18>::type x18( args[18] ) ;
        typename Rcpp::traits::input_parameter<U19>::type x19( args[19] ) ;
        typename Rcpp::traits::input_parameter<U20>::type x20( args[20] ) ;
        typename Rcpp::traits::input_parameter<U21>::type x21( args[21] ) ;
        typename Rcpp::traits::input_parameter<U22>::type x22( args[22] ) ;
        typename Rcpp::traits::input_parameter<U23>::type x23( args[23] ) ;
        typename Rcpp::traits::input_parameter<U24>::type x24( args[24] ) ;
        typename Rcpp::traits::input_parameter<U25>::type x25( args[25] ) ;
        typename Rcpp::traits::input_parameter<U26>::type x26( args[26] ) ;
        typename Rcpp::traits::input_parameter<U27>::type x27( args[27] ) ;
        typename Rcpp::traits::input_parameter<U28>::type x28( args[28] ) ;
        typename Rcpp::traits::input_parameter<U29>::type x29( args[29] ) ;
        typename Rcpp::traits::input_parameter<U30>::type x30( args[30] ) ;
        typename Rcpp::traits::input_parameter<U31>::type x31( args[31] ) ;
        typename Rcpp::traits::input_parameter<U32>::type x32( args[32] ) ;
        typename Rcpp::traits::input_parameter<U33>::type x33( args[33] ) ;
        typename Rcpp::traits::input_parameter<U34>::type x34( args[34] ) ;
        typename Rcpp::traits::input_parameter<U35>::type x35( args[35] ) ;
        typename Rcpp::traits::input_parameter<U36>::type x36( args[36] ) ;
        typename Rcpp::traits::input_parameter<U37>::type x37( args[37] ) ;
        typename Rcpp::traits::input_parameter<U38>::type x38( args[38] ) ;
        typename Rcpp::traits::input_parameter<U39>::type x39( args[39] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9, typename U10, typename U11, typename U12, typename U13, typename U14, typename U15, typename U16, typename U17, typename U18, typename U19, typename U20, typename U21, typename U22, typename U23, typename U24, typename U25, typename U26, typename U27, typename U28, typename U29, typename U30, typename U31, typename U32, typename U33, typename U34, typename U35, typename U36, typename U37, typename U38, typename U39, typename U40>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        typename Rcpp::traits::input_parameter<U5>::type x5( args[5] ) ;
        typename Rcpp::traits::input_parameter<U6>::type x6( args[6] ) ;
        typename Rcpp::traits::input_parameter<U7>::type x7( args[7] ) ;
        typename Rcpp::traits::input_parameter<U8>::type x8( args[8] ) ;
        typename Rcpp::traits::input_parameter<U9>::type x9( args[9] ) ;
        typename Rcpp::traits::input_parameter<U10>::type x10( args[10] ) ;
        typename Rcpp::traits::input_parameter<U11>::type x11( args[11] ) ;
        typename Rcpp::traits::input_parameter<U12>::type x12( args[12] ) ;
        typename Rcpp::traits::input_parameter<U13>::type x13( args[13] ) ;
        typename Rcpp::traits::input_parameter<U14>::type x14( args[14] ) ;
        typename Rcpp::traits::input_parameter<U15>::type x15( args[15] ) ;
        typename Rcpp::traits::input_parameter<U16>::type x16( args[16] ) ;
        typename Rcpp::traits::input_parameter<U17>::type x17( args[17] ) ;
        typename Rcpp::traits::input_parameter<U18>::type x18( args[18] ) ;
        typename Rcpp::traits::input_parameter<U19>::type x19( args[19] ) ;
        typename Rcpp::traits::input_parameter<U20>::type x20( args[20] ) ;
        typename Rcpp::traits::input_parameter<U21>::type x21( args[21] ) ;
        typename Rcpp::traits::input_parameter<U22>::type x22( args[22] ) ;
        typename Rcpp::traits::input_parameter<U23>::type x23( args[23] ) ;
        typename Rcpp::traits::input_parameter<U24>::type x24( args[24] ) ;
        typename Rcpp::traits::input_parameter<U25>::type x25( args[25] ) ;
        typename Rcpp::traits::input_parameter<U26>::type x26( args[26] ) ;
        typename Rcpp::traits::input_parameter<U27>::type x27( args[27] ) ;
        typename Rcpp::traits::input_parameter<U28>::type x28( args[28] ) ;
        typename Rcpp::traits::input_parameter<U29>::type x29( args[29] ) ;
        typename Rcpp::traits::input_parameter<U30>::type x30( args[30] ) ;
        typename Rcpp::traits::input_parameter<U31>::type x31( args[31] ) ;
        typename Rcpp::traits::input_parameter<U32>::type x32( args[32] ) ;
        typename Rcpp::traits::input_parameter<U33>::type x33( args[33] ) ;
        typename Rcpp::traits::input_parameter<U34>::type x34( args[34] ) ;
        typename Rcpp::traits::input_parameter<U35>::type x35( args[35] ) ;
        typename Rcpp::traits::input_parameter<U36>::type x36( args[36] ) ;
        typename Rcpp::traits::input_parameter<U37>::type x37( args[37] ) ;
        typename Rcpp::traits::input_parameter<U38>::type x38( args[38] ) ;
        typename Rcpp::traits::input_parameter<U39>::type x39( args[39] ) ;
        typename Rcpp::traits::input_parameter<U40>::type x40( args[40] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9, typename U10, typename U11, typename U12, typename U13, typename U14, typename U15, typename U16, typename U17, typename U18, typename U19, typename U20, typename U21, typename U22, typename U23, typename U24, typename U25, typename U26, typename U27, typename U28, typename U29, typename U30, typename U31, typename U32, typename U33, typename U34, typename U35, typename U36, typename U37, typename U38, typename U39, typename U40, typename U41>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        typename Rcpp::traits::input_parameter<U5>::type x5( args[5] ) ;
        typename Rcpp::traits::input_parameter<U6>::type x6( args[6] ) ;
        typename Rcpp::traits::input_parameter<U7>::type x7( args[7] ) ;
        typename Rcpp::traits::input_parameter<U8>::type x8( args[8] ) ;
        typename Rcpp::traits::input_parameter<U9>::type x9( args[9] ) ;
        typename Rcpp::traits::input_parameter<U10>::type x10( args[10] ) ;
        typename Rcpp::traits::input_parameter<U11>::type x11( args[11] ) ;
        typename Rcpp::traits::input_parameter<U12>::type x12( args[12] ) ;
        typename Rcpp::traits::input_parameter<U13>::type x13( args[13] ) ;
        typename Rcpp::traits::input_parameter<U14>::type x14( args[14] ) ;
        typename Rcpp::traits::input_parameter<U15>::type x15( args[15] ) ;
        typename Rcpp::traits::input_parameter<U16>::type x16( args[16] ) ;
        typename Rcpp::traits::input_parameter<U17>::type x17( args[17] ) ;
        typename Rcpp::traits::input_parameter<U18>::type x18( args[18] ) ;
        typename Rcpp::traits::input_parameter<U19>::type x19( args[19] ) ;
        typename Rcpp::traits::input_parameter<U20>::type x20( args[20] ) ;
        typename Rcpp::traits::input_parameter<U21>::type x21( args[21] ) ;
        typename Rcpp::traits::input_parameter<U22>::type x22( args[22] ) ;
        typename Rcpp::traits::input_parameter<U23>::type x23( args[23] ) ;
        typename Rcpp::traits::input_parameter<U24>::type x24( args[24] ) ;
        typename Rcpp::traits::input_parameter<U25>::type x25( args[25] ) ;
        typename Rcpp::traits::input_parameter<U26>::type x26( args[26] ) ;
        typename Rcpp::traits::input_parameter<U27>::type x27( args[27] ) ;
        typename Rcpp::traits::input_parameter<U28>::type x28( args[28] ) ;
        typename Rcpp::traits::input_parameter<U29>::type x29( args[29] ) ;
        typename Rcpp::traits::input_parameter<U30>::type x30( args[30] ) ;
        typename Rcpp::traits::input_parameter<U31>::type x31( args[31] ) ;
        typename Rcpp::traits::input_parameter<U32>::type x32( args[32] ) ;
        typename Rcpp::traits::input_parameter<U33>::type x33( args[33] ) ;
        typename Rcpp::traits::input_parameter<U34>::type x34( args[34] ) ;
        typename Rcpp::traits::input_parameter<U35>::type x35( args[35] ) ;
        typename Rcpp::traits::input_parameter<U36>::type x36( args[36] ) ;
        typename Rcpp::traits::input_parameter<U37>::type x37( args[37] ) ;
        typename Rcpp::traits::input_parameter<U38>::type x38( args[38] ) ;
        typename Rcpp::traits::input_parameter<U39>::type x39( args[39] ) ;
        typename Rcpp::traits::input_parameter<U40>::type x40( args[40] ) ;
        typename Rcpp::traits::input_parameter<U41>::type x41( args[41] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9, typename U10, typename U11, typename U12, typename U13, typename U14, typename U15, typename U16, typename U17, typename U18, typename U19, typename U20, typename U21, typename U22, typename U23, typename U24, typename U25, typename U26, typename U27, typename U28, typename U29, typename U30, typename U31, typename U32, typename U33, typename U34, typename U35, typename U36, typename U37, typename U38, typename U39, typename U40, typename U41, typename U42>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        typename Rcpp::traits::input_parameter<U5>::type x5( args[5] ) ;
        typename Rcpp::traits::input_parameter<U6>::type x6( args[6] ) ;
        typename Rcpp::traits::input_parameter<U7>::type x7( args[7] ) ;
        typename Rcpp::traits::input_parameter<U8>::type x8( args[8] ) ;
        typename Rcpp::traits::input_parameter<U9>::type x9( args[9] ) ;
        typename Rcpp::traits::input_parameter<U10>::type x10( args[10] ) ;
        typename Rcpp::traits::input_parameter<U11>::type x11( args[11] ) ;
        typename Rcpp::traits::input_parameter<U12>::type x12( args[12] ) ;
        typename Rcpp::traits::input_parameter<U13>::type x13( args[13] ) ;
        typename Rcpp::traits::input_parameter<U14>::type x14( args[14] ) ;
        typename Rcpp::traits::input_parameter<U15>::type x15( args[15] ) ;
        typename Rcpp::traits::input_parameter<U16>::type x16( args[16] ) ;
        typename Rcpp::traits::input_parameter<U17>::type x17( args[17] ) ;
        typename Rcpp::traits::input_parameter<U18>::type x18( args[18] ) ;
        typename Rcpp::traits::input_parameter<U19>::type x19( args[19] ) ;
        typename Rcpp::traits::input_parameter<U20>::type x20( args[20] ) ;
        typename Rcpp::traits::input_parameter<U21>::type x21( args[21] ) ;
        typename Rcpp::traits::input_parameter<U22>::type x22( args[22] ) ;
        typename Rcpp::traits::input_parameter<U23>::type x23( args[23] ) ;
        typename Rcpp::traits::input_parameter<U24>::type x24( args[24] ) ;
        typename Rcpp::traits::input_parameter<U25>::type x25( args[25] ) ;
        typename Rcpp::traits::input_parameter<U26>::type x26( args[26] ) ;
        typename Rcpp::traits::input_parameter<U27>::type x27( args[27] ) ;
        typename Rcpp::traits::input_parameter<U28>::type x28( args[28] ) ;
        typename Rcpp::traits::input_parameter<U29>::type x29( args[29] ) ;
        typename Rcpp::traits::input_parameter<U30>::type x30( args[30] ) ;
        typename Rcpp::traits::input_parameter<U31>::type x31( args[31] ) ;
        typename Rcpp::traits::input_parameter<U32>::type x32( args[32] ) ;
        typename Rcpp::traits::input_parameter<U33>::type x33( args[33] ) ;
        typename Rcpp::traits::input_parameter<U34>::type x34( args[34] ) ;
        typename Rcpp::traits::input_parameter<U35>::type x35( args[35] ) ;
        typename Rcpp::traits::input_parameter<U36>::type x36( args[36] ) ;
        typename Rcpp::traits::input_parameter<U37>::type x37( args[37] ) ;
        typename Rcpp::traits::input_parameter<U38>::type x38( args[38] ) ;
        typename Rcpp::traits::input_parameter<U39>::type x39( args[39] ) ;
        typename Rcpp::traits::input_parameter<U40>::type x40( args[40] ) ;
        typename Rcpp::traits::input_parameter<U41>::type x41( args[41] ) ;
        typename Rcpp::traits::input_parameter<U42>::type x42( args[42] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9, typename U10, typename U11, typename U12, typename U13, typename U14, typename U15, typename U16, typename U17, typename U18, typename U19, typename U20, typename U21, typename U22, typename U23, typename U24, typename U25, typename U26, typename U27, typename U28, typename U29, typename U30, typename U31, typename U32, typename U33, typename U34, typename U35, typename U36, typename U37, typename U38, typename U39, typename U40, typename U41, typename U42, typename U43>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        typename Rcpp::traits::input_parameter<U5>::type x5( args[5] ) ;
        typename Rcpp::traits::input_parameter<U6>::type x6( args[6] ) ;
        typename Rcpp::traits::input_parameter<U7>::type x7( args[7] ) ;
        typename Rcpp::traits::input_parameter<U8>::type x8( args[8] ) ;
        typename Rcpp::traits::input_parameter<U9>::type x9( args[9] ) ;
        typename Rcpp::traits::input_parameter<U10>::type x10( args[10] ) ;
        typename Rcpp::traits::input_parameter<U11>::type x11( args[11] ) ;
        typename Rcpp::traits::input_parameter<U12>::type x12( args[12] ) ;
        typename Rcpp::traits::input_parameter<U13>::type x13( args[13] ) ;
        typename Rcpp::traits::input_parameter<U14>::type x14( args[14] ) ;
        typename Rcpp::traits::input_parameter<U15>::type x15( args[15] ) ;
        typename Rcpp::traits::input_parameter<U16>::type x16( args[16] ) ;
        typename Rcpp::traits::input_parameter<U17>::type x17( args[17] ) ;
        typename Rcpp::traits::input_parameter<U18>::type x18( args[18] ) ;
        typename Rcpp::traits::input_parameter<U19>::type x19( args[19] ) ;
        typename Rcpp::traits::input_parameter<U20>::type x20( args[20] ) ;
        typename Rcpp::traits::input_parameter<U21>::type x21( args[21] ) ;
        typename Rcpp::traits::input_parameter<U22>::type x22( args[22] ) ;
        typename Rcpp::traits::input_parameter<U23>::type x23( args[23] ) ;
        typename Rcpp::traits::input_parameter<U24>::type x24( args[24] ) ;
        typename Rcpp::traits::input_parameter<U25>::type x25( args[25] ) ;
        typename Rcpp::traits::input_parameter<U26>::type x26( args[26] ) ;
        typename Rcpp::traits::input_parameter<U27>::type x27( args[27] ) ;
        typename Rcpp::traits::input_parameter<U28>::type x28( args[28] ) ;
        typename Rcpp::traits::input_parameter<U29>::type x29( args[29] ) ;
        typename Rcpp::traits::input_parameter<U30>::type x30( args[30] ) ;
        typename Rcpp::traits::input_parameter<U31>::type x31( args[31] ) ;
        typename Rcpp::traits::input_parameter<U32>::type x32( args[32] ) ;
        typename Rcpp::traits::input_parameter<U33>::type x33( args[33] ) ;
        typename Rcpp::traits::input_parameter<U34>::type x34( args[34] ) ;
        typename Rcpp::traits::input_parameter<U35>::type x35( args[35] ) ;
        typename Rcpp::traits::input_parameter<U36>::type x36( args[36] ) ;
        typename Rcpp::traits::input_parameter<U37>::type x37( args[37] ) ;
        typename Rcpp::traits::input_parameter<U38>::type x38( args[38] ) ;
        typename Rcpp::traits::input_parameter<U39>::type x39( args[39] ) ;
        typename Rcpp::traits::input_parameter<U40>::type x40( args[40] ) ;
        typename Rcpp::traits::input_parameter<U41>::type x41( args[41] ) ;
        typename Rcpp::traits::input_parameter<U42>::type x42( args[42] ) ;
        typename Rcpp::traits::input_parameter<U43>::type x43( args[43] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9, typename U10, typename U11, typename U12, typename U13, typename U14, typename U15, typename U16, typename U17, typename U18, typename U19, typename U20, typename U21, typename U22, typename U23, typename U24, typename U25, typename U26, typename U27, typename U28, typename U29, typename U30, typename U31, typename U32, typename U33, typename U34, typename U35, typename U36, typename U37, typename U38, typename U39, typename U40, typename U41, typename U42, typename U43, typename U44>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        typename Rcpp::traits::input_parameter<U5>::type x5( args[5] ) ;
        typename Rcpp::traits::input_parameter<U6>::type x6( args[6] ) ;
        typename Rcpp::traits::input_parameter<U7>::type x7( args[7] ) ;
        typename Rcpp::traits::input_parameter<U8>::type x8( args[8] ) ;
        typename Rcpp::traits::input_parameter<U9>::type x9( args[9] ) ;
        typename Rcpp::traits::input_parameter<U10>::type x10( args[10] ) ;
        typename Rcpp::traits::input_parameter<U11>::type x11( args[11] ) ;
        typename Rcpp::traits::input_parameter<U12>::type x12( args[12] ) ;
        typename Rcpp::traits::input_parameter<U13>::type x13( args[13] ) ;
        typename Rcpp::traits::input_parameter<U14>::type x14( args[14] ) ;
        typename Rcpp::traits::input_parameter<U15>::type x15( args[15] ) ;
        typename Rcpp::traits::input_parameter<U16>::type x16( args[16] ) ;
        typename Rcpp::traits::input_parameter<U17>::type x17( args[17] ) ;
        typename Rcpp::traits::input_parameter<U18>::type x18( args[18] ) ;
        typename Rcpp::traits::input_parameter<U19>::type x19( args[19] ) ;
        typename Rcpp::traits::input_parameter<U20>::type x20( args[20] ) ;
        typename Rcpp::traits::input_parameter<U21>::type x21( args[21] ) ;
        typename Rcpp::traits::input_parameter<U22>::type x22( args[22] ) ;
        typename Rcpp::traits::input_parameter<U23>::type x23( args[23] ) ;
        typename Rcpp::traits::input_parameter<U24>::type x24( args[24] ) ;
        typename Rcpp::traits::input_parameter<U25>::type x25( args[25] ) ;
        typename Rcpp::traits::input_parameter<U26>::type x26( args[26] ) ;
        typename Rcpp::traits::input_parameter<U27>::type x27( args[27] ) ;
        typename Rcpp::traits::input_parameter<U28>::type x28( args[28] ) ;
        typename Rcpp::traits::input_parameter<U29>::type x29( args[29] ) ;
        typename Rcpp::traits::input_parameter<U30>::type x30( args[30] ) ;
        typename Rcpp::traits::input_parameter<U31>::type x31( args[31] ) ;
        typename Rcpp::traits::input_parameter<U32>::type x32( args[32] ) ;
        typename Rcpp::traits::input_parameter<U33>::type x33( args[33] ) ;
        typename Rcpp::traits::input_parameter<U34>::type x34( args[34] ) ;
        typename Rcpp::traits::input_parameter<U35>::type x35( args[35] ) ;
        typename Rcpp::traits::input_parameter<U36>::type x36( args[36] ) ;
        typename Rcpp::traits::input_parameter<U37>::type x37( args[37] ) ;
        typename Rcpp::traits::input_parameter<U38>::type x38( args[38] ) ;
        typename Rcpp::traits::input_parameter<U39>::type x39( args[39] ) ;
        typename Rcpp::traits::input_parameter<U40>::type x40( args[40] ) ;
        typename Rcpp::traits::input_parameter<U41>::type x41( args[41] ) ;
        typename Rcpp::traits::input_parameter<U42>::type x42( args[42] ) ;
        typename Rcpp::traits::input_parameter<U43>::type x43( args[43] ) ;
        typename Rcpp::traits::input_parameter<U44>::type x44( args[44] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9, typename U10, typename U11, typename U12, typename U13, typename U14, typename U15, typename U16, typename U17, typename U18, typename U19, typename U20, typename U21, typename U22, typename U23, typename U24, typename U25, typename U26, typename U27, typename U28, typename U29, typename U30, typename U31, typename U32, typename U33, typename U34, typename U35, typename U36, typename U37, typename U38, typename U39, typename U40, typename U41, typename U42, typename U43, typename U44, typename U45>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        typename Rcpp::traits::input_parameter<U5>::type x5( args[5] ) ;
        typename Rcpp::traits::input_parameter<U6>::type x6( args[6] ) ;
        typename Rcpp::traits::input_parameter<U7>::type x7( args[7] ) ;
        typename Rcpp::traits::input_parameter<U8>::type x8( args[8] ) ;
        typename Rcpp::traits::input_parameter<U9>::type x9( args[9] ) ;
        typename Rcpp::traits::input_parameter<U10>::type x10( args[10] ) ;
        typename Rcpp::traits::input_parameter<U11>::type x11( args[11] ) ;
        typename Rcpp::traits::input_parameter<U12>::type x12( args[12] ) ;
        typename Rcpp::traits::input_parameter<U13>::type x13( args[13] ) ;
        typename Rcpp::traits::input_parameter<U14>::type x14( args[14] ) ;
        typename Rcpp::traits::input_parameter<U15>::type x15( args[15] ) ;
        typename Rcpp::traits::input_parameter<U16>::type x16( args[16] ) ;
        typename Rcpp::traits::input_parameter<U17>::type x17( args[17] ) ;
        typename Rcpp::traits::input_parameter<U18>::type x18( args[18] ) ;
        typename Rcpp::traits::input_parameter<U19>::type x19( args[19] ) ;
        typename Rcpp::traits::input_parameter<U20>::type x20( args[20] ) ;
        typename Rcpp::traits::input_parameter<U21>::type x21( args[21] ) ;
        typename Rcpp::traits::input_parameter<U22>::type x22( args[22] ) ;
        typename Rcpp::traits::input_parameter<U23>::type x23( args[23] ) ;
        typename Rcpp::traits::input_parameter<U24>::type x24( args[24] ) ;
        typename Rcpp::traits::input_parameter<U25>::type x25( args[25] ) ;
        typename Rcpp::traits::input_parameter<U26>::type x26( args[26] ) ;
        typename Rcpp::traits::input_parameter<U27>::type x27( args[27] ) ;
        typename Rcpp::traits::input_parameter<U28>::type x28( args[28] ) ;
        typename Rcpp::traits::input_parameter<U29>::type x29( args[29] ) ;
        typename Rcpp::traits::input_parameter<U30>::type x30( args[30] ) ;
        typename Rcpp::traits::input_parameter<U31>::type x31( args[31] ) ;
        typename Rcpp::traits::input_parameter<U32>::type x32( args[32] ) ;
        typename Rcpp::traits::input_parameter<U33>::type x33( args[33] ) ;
        typename Rcpp::traits::input_parameter<U34>::type x34( args[34] ) ;
        typename Rcpp::traits::input_parameter<U35>::type x35( args[35] ) ;
        typename Rcpp::traits::input_parameter<U36>::type x36( args[36] ) ;
        typename Rcpp::traits::input_parameter<U37>::type x37( args[37] ) ;
        typename Rcpp::traits::input_parameter<U38>::type x38( args[38] ) ;
        typename Rcpp::traits::input_parameter<U39>::type x39( args[39] ) ;
        typename Rcpp::traits::input_parameter<U40>::type x40( args[40] ) ;
        typename Rcpp::traits::input_parameter<U41>::type x41( args[41] ) ;
        typename Rcpp::traits::input_parameter<U42>::type x42( args[42] ) ;
        typename Rcpp::traits::input_parameter<U43>::type x43( args[43] ) ;
        typename Rcpp::traits::input_parameter<U44>::type x44( args[44] ) ;
        typename Rcpp::traits::input_parameter<U45>::type x45( args[45] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9, typename U10, typename U11, typename U12, typename U13, typename U14, typename U15, typename U16, typename U17, typename U18, typename U19, typename U20, typename U21, typename U22, typename U23, typename U24, typename U25, typename U26, typename U27, typename U28, typename U29, typename U30, typename U31, typename U32, typename U33, typename U34, typename U35, typename U36, typename U37, typename U38, typename U39, typename U40, typename U41, typename U42, typename U43, typename U44, typename U45, typename U46>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        typename Rcpp::traits::input_parameter<U5>::type x5( args[5] ) ;
        typename Rcpp::traits::input_parameter<U6>::type x6( args[6] ) ;
        typename Rcpp::traits::input_parameter<U7>::type x7( args[7] ) ;
        typename Rcpp::traits::input_parameter<U8>::type x8( args[8] ) ;
        typename Rcpp::traits::input_parameter<U9>::type x9( args[9] ) ;
        typename Rcpp::traits::input_parameter<U10>::type x10( args[10] ) ;
        typename Rcpp::traits::input_parameter<U11>::type x11( args[11] ) ;
        typename Rcpp::traits::input_parameter<U12>::type x12( args[12] ) ;
        typename Rcpp::traits::input_parameter<U13>::type x13( args[13] ) ;
        typename Rcpp::traits::input_parameter<U14>::type x14( args[14] ) ;
        typename Rcpp::traits::input_parameter<U15>::type x15( args[15] ) ;
        typename Rcpp::traits::input_parameter<U16>::type x16( args[16] ) ;
        typename Rcpp::traits::input_parameter<U17>::type x17( args[17] ) ;
        typename Rcpp::traits::input_parameter<U18>::type x18( args[18] ) ;
        typename Rcpp::traits::input_parameter<U19>::type x19( args[19] ) ;
        typename Rcpp::traits::input_parameter<U20>::type x20( args[20] ) ;
        typename Rcpp::traits::input_parameter<U21>::type x21( args[21] ) ;
        typename Rcpp::traits::input_parameter<U22>::type x22( args[22] ) ;
        typename Rcpp::traits::input_parameter<U23>::type x23( args[23] ) ;
        typename Rcpp::traits::input_parameter<U24>::type x24( args[24] ) ;
        typename Rcpp::traits::input_parameter<U25>::type x25( args[25] ) ;
        typename Rcpp::traits::input_parameter<U26>::type x26( args[26] ) ;
        typename Rcpp::traits::input_parameter<U27>::type x27( args[27] ) ;
        typename Rcpp::traits::input_parameter<U28>::type x28( args[28] ) ;
        typename Rcpp::traits::input_parameter<U29>::type x29( args[29] ) ;
        typename Rcpp::traits::input_parameter<U30>::type x30( args[30] ) ;
        typename Rcpp::traits::input_parameter<U31>::type x31( args[31] ) ;
        typename Rcpp::traits::input_parameter<U32>::type x32( args[32] ) ;
        typename Rcpp::traits::input_parameter<U33>::type x33( args[33] ) ;
        typename Rcpp::traits::input_parameter<U34>::type x34( args[34] ) ;
        typename Rcpp::traits::input_parameter<U35>::type x35( args[35] ) ;
        typename Rcpp::traits::input_parameter<U36>::type x36( args[36] ) ;
        typename Rcpp::traits::input_parameter<U37>::type x37( args[37] ) ;
        typename Rcpp::traits::input_parameter<U38>::type x38( args[38] ) ;
        typename Rcpp::traits::input_parameter<U39>::type x39( args[39] ) ;
        typename Rcpp::traits::input_parameter<U40>::type x40( args[40] ) ;
        typename Rcpp::traits::input_parameter<U41>::type x41( args[41] ) ;
        typename Rcpp::traits::input_parameter<U42>::type x42( args[42] ) ;
        typename Rcpp::traits::input_parameter<U43>::type x43( args[43] ) ;
        typename Rcpp::traits::input_parameter<U44>::type x44( args[44] ) ;
        typename Rcpp::traits::input_parameter<U45>::type x45( args[45] ) ;
        typename Rcpp::traits::input_parameter<U46>::type x46( args[46] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9, typename U10, typename U11, typename U12, typename U13, typename U14, typename U15, typename U16, typename U17, typename U18, typename U19, typename U20, typename U21, typename U22, typename U23, typename U24, typename U25, typename U26, typename U27, typename U28, typename U29, typename U30, typename U31, typename U32, typename U33, typename U34, typename U35, typename U36, typename U37, typename U38, typename U39, typename U40, typename U41, typename U42, typename U43, typename U44, typename U45, typename U46, typename U47>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        typename Rcpp::traits::input_parameter<U5>::type x5( args[5] ) ;
        typename Rcpp::traits::input_parameter<U6>::type x6( args[6] ) ;
        typename Rcpp::traits::input_parameter<U7>::type x7( args[7] ) ;
        typename Rcpp::traits::input_parameter<U8>::type x8( args[8] ) ;
        typename Rcpp::traits::input_parameter<U9>::type x9( args[9] ) ;
        typename Rcpp::traits::input_parameter<U10>::type x10( args[10] ) ;
        typename Rcpp::traits::input_parameter<U11>::type x11( args[11] ) ;
        typename Rcpp::traits::input_parameter<U12>::type x12( args[12] ) ;
        typename Rcpp::traits::input_parameter<U13>::type x13( args[13] ) ;
        typename Rcpp::traits::input_parameter<U14>::type x14( args[14] ) ;
        typename Rcpp::traits::input_parameter<U15>::type x15( args[15] ) ;
        typename Rcpp::traits::input_parameter<U16>::type x16( args[16] ) ;
        typename Rcpp::traits::input_parameter<U17>::type x17( args[17] ) ;
        typename Rcpp::traits::input_parameter<U18>::type x18( args[18] ) ;
        typename Rcpp::traits::input_parameter<U19>::type x19( args[19] ) ;
        typename Rcpp::traits::input_parameter<U20>::type x20( args[20] ) ;
        typename Rcpp::traits::input_parameter<U21>::type x21( args[21] ) ;
        typename Rcpp::traits::input_parameter<U22>::type x22( args[22] ) ;
        typename Rcpp::traits::input_parameter<U23>::type x23( args[23] ) ;
        typename Rcpp::traits::input_parameter<U24>::type x24( args[24] ) ;
        typename Rcpp::traits::input_parameter<U25>::type x25( args[25] ) ;
        typename Rcpp::traits::input_parameter<U26>::type x26( args[26] ) ;
        typename Rcpp::traits::input_parameter<U27>::type x27( args[27] ) ;
        typename Rcpp::traits::input_parameter<U28>::type x28( args[28] ) ;
        typename Rcpp::traits::input_parameter<U29>::type x29( args[29] ) ;
        typename Rcpp::traits::input_parameter<U30>::type x30( args[30] ) ;
        typename Rcpp::traits::input_parameter<U31>::type x31( args[31] ) ;
        typename Rcpp::traits::input_parameter<U32>::type x32( args[32] ) ;
        typename Rcpp::traits::input_parameter<U33>::type x33( args[33] ) ;
        typename Rcpp::traits::input_parameter<U34>::type x34( args[34] ) ;
        typename Rcpp::traits::input_parameter<U35>::type x35( args[35] ) ;
        typename Rcpp::traits::input_parameter<U36>::type x36( args[36] ) ;
        typename Rcpp::traits::input_parameter<U37>::type x37( args[37] ) ;
        typename Rcpp::traits::input_parameter<U38>::type x38( args[38] ) ;
        typename Rcpp::traits::input_parameter<U39>::type x39( args[39] ) ;
        typename Rcpp::traits::input_parameter<U40>::type x40( args[40] ) ;
        typename Rcpp::traits::input_parameter<U41>::type x41( args[41] ) ;
        typename Rcpp::traits::input_parameter<U42>::type x42( args[42] ) ;
        typename Rcpp::traits::input_parameter<U43>::type x43( args[43] ) ;
        typename Rcpp::traits::input_parameter<U44>::type x44( args[44] ) ;
        typename Rcpp::traits::input_parameter<U45>::type x45( args[45] ) ;
        typename Rcpp::traits::input_parameter<U46>::type x46( args[46] ) ;
        typename Rcpp::traits::input_parameter<U47>::type x47( args[47] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9, typename U10, typename U11, typename U12, typename U13, typename U14, typename U15, typename U16, typename U17, typename U18, typename U19, typename U20, typename U21, typename U22, typename U23, typename U24, typename U25, typename U26, typename U27, typename U28, typename U29, typename U30, typename U31, typename U32, typename U33, typename U34, typename U35, typename U36, typename U37, typename U38, typename U39, typename U40, typename U41, typename U42, typename U43, typename U44, typename U45, typename U46, typename U47, typename U48>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        typename Rcpp::traits::input_parameter<U5>::type x5( args[5] ) ;
        typename Rcpp::traits::input_parameter<U6>::type x6( args[6] ) ;
        typename Rcpp::traits::input_parameter<U7>::type x7( args[7] ) ;
        typename Rcpp::traits::input_parameter<U8>::type x8( args[8] ) ;
        typename Rcpp::traits::input_parameter<U9>::type x9( args[9] ) ;
        typename Rcpp::traits::input_parameter<U10>::type x10( args[10] ) ;
        typename Rcpp::traits::input_parameter<U11>::type x11( args[11] ) ;
        typename Rcpp::traits::input_parameter<U12>::type x12( args[12] ) ;
        typename Rcpp::traits::input_parameter<U13>::type x13( args[13] ) ;
        typename Rcpp::traits::input_parameter<U14>::type x14( args[14] ) ;
        typename Rcpp::traits::input_parameter<U15>::type x15( args[15] ) ;
        typename Rcpp::traits::input_parameter<U16>::type x16( args[16] ) ;
        typename Rcpp::traits::input_parameter<U17>::type x17( args[17] ) ;
        typename Rcpp::traits::input_parameter<U18>::type x18( args[18] ) ;
        typename Rcpp::traits::input_parameter<U19>::type x19( args[19] ) ;
        typename Rcpp::traits::input_parameter<U20>::type x20( args[20] ) ;
        typename Rcpp::traits::input_parameter<U21>::type x21( args[21] ) ;
        typename Rcpp::traits::input_parameter<U22>::type x22( args[22] ) ;
        typename Rcpp::traits::input_parameter<U23>::type x23( args[23] ) ;
        typename Rcpp::traits::input_parameter<U24>::type x24( args[24] ) ;
        typename Rcpp::traits::input_parameter<U25>::type x25( args[25] ) ;
        typename Rcpp::traits::input_parameter<U26>::type x26( args[26] ) ;
        typename Rcpp::traits::input_parameter<U27>::type x27( args[27] ) ;
        typename Rcpp::traits::input_parameter<U28>::type x28( args[28] ) ;
        typename Rcpp::traits::input_parameter<U29>::type x29( args[29] ) ;
        typename Rcpp::traits::input_parameter<U30>::type x30( args[30] ) ;
        typename Rcpp::traits::input_parameter<U31>::type x31( args[31] ) ;
        typename Rcpp::traits::input_parameter<U32>::type x32( args[32] ) ;
        typename Rcpp::traits::input_parameter<U33>::type x33( args[33] ) ;
        typename Rcpp::traits::input_parameter<U34>::type x34( args[34] ) ;
        typename Rcpp::traits::input_parameter<U35>::type x35( args[35] ) ;
        typename Rcpp::traits::input_parameter<U36>::type x36( args[36] ) ;
        typename Rcpp::traits::input_parameter<U37>::type x37( args[37] ) ;
        typename Rcpp::traits::input_parameter<U38>::type x38( args[38] ) ;
        typename Rcpp::traits::input_parameter<U39>::type x39( args[39] ) ;
        typename Rcpp::traits::input_parameter<U40>::type x40( args[40] ) ;
        typename Rcpp::traits::input_parameter<U41>::type x41( args[41] ) ;
        typename Rcpp::traits::input_parameter<U42>::type x42( args[42] ) ;
        typename Rcpp::traits::input_parameter<U43>::type x43( args[43] ) ;
        typename Rcpp::traits::input_parameter<U44>::type x44( args[44] ) ;
        typename Rcpp::traits::input_parameter<U45>::type x45( args[45] ) ;
        typename Rcpp::traits::input_parameter<U46>::type x46( args[46] ) ;
        typename Rcpp::traits::input_parameter<U47>::type x47( args[47] ) ;
        typename Rcpp::traits::input_parameter<U48>::type x48( args[48] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9, typename U10, typename U11, typename U12, typename U13, typename U14, typename U15, typename U16, typename U17, typename U18, typename U19, typename U20, typename U21, typename U22, typename U23, typename U24, typename U25, typename U26, typename U27, typename U28, typename U29, typename U30, typename U31, typename U32, typename U33, typename U34, typename U35, typename U36, typename U37, typename U38, typename U39, typename U40, typename U41, typename U42, typename U43, typename U44, typename U45, typename U46, typename U47, typename U48, typename U49>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        typename Rcpp::traits::input_parameter<U5>::type x5( args[5] ) ;
        typename Rcpp::traits::input_parameter<U6>::type x6( args[6] ) ;
        typename Rcpp::traits::input_parameter<U7>::type x7( args[7] ) ;
        typename Rcpp::traits::input_parameter<U8>::type x8( args[8] ) ;
        typename Rcpp::traits::input_parameter<U9>::type x9( args[9] ) ;
        typename Rcpp::traits::input_parameter<U10>::type x10( args[10] ) ;
        typename Rcpp::traits::input_parameter<U11>::type x11( args[11] ) ;
        typename Rcpp::traits::input_parameter<U12>::type x12( args[12] ) ;
        typename Rcpp::traits::input_parameter<U13>::type x13( args[13] ) ;
        typename Rcpp::traits::input_parameter<U14>::type x14( args[14] ) ;
        typename Rcpp::traits::input_parameter<U15>::type x15( args[15] ) ;
        typename Rcpp::traits::input_parameter<U16>::type x16( args[16] ) ;
        typename Rcpp::traits::input_parameter<U17>::type x17( args[17] ) ;
        typename Rcpp::traits::input_parameter<U18>::type x18( args[18] ) ;
        typename Rcpp::traits::input_parameter<U19>::type x19( args[19] ) ;
        typename Rcpp::traits::input_parameter<U20>::type x20( args[20] ) ;
        typename Rcpp::traits::input_parameter<U21>::type x21( args[21] ) ;
        typename Rcpp::traits::input_parameter<U22>::type x22( args[22] ) ;
        typename Rcpp::traits::input_parameter<U23>::type x23( args[23] ) ;
        typename Rcpp::traits::input_parameter<U24>::type x24( args[24] ) ;
        typename Rcpp::traits::input_parameter<U25>::type x25( args[25] ) ;
        typename Rcpp::traits::input_parameter<U26>::type x26( args[26] ) ;
        typename Rcpp::traits::input_parameter<U27>::type x27( args[27] ) ;
        typename Rcpp::traits::input_parameter<U28>::type x28( args[28] ) ;
        typename Rcpp::traits::input_parameter<U29>::type x29( args[29] ) ;
        typename Rcpp::traits::input_parameter<U30>::type x30( args[30] ) ;
        typename Rcpp::traits::input_parameter<U31>::type x31( args[31] ) ;
        typename Rcpp::traits::input_parameter<U32>::type x32( args[32] ) ;
        typename Rcpp::traits::input_parameter<U33>::type x33( args[33] ) ;
        typename Rcpp::traits::input_parameter<U34>::type x34( args[34] ) ;
        typename Rcpp::traits::input_parameter<U35>::type x35( args[35] ) ;
        typename Rcpp::traits::input_parameter<U36>::type x36( args[36] ) ;
        typename Rcpp::traits::input_parameter<U37>::type x37( args[37] ) ;
        typename Rcpp::traits::input_parameter<U38>::type x38( args[38] ) ;
        typename Rcpp::traits::input_parameter<U39>::type x39( args[39] ) ;
        typename Rcpp::traits::input_parameter<U40>::type x40( args[40] ) ;
        typename Rcpp::traits::input_parameter<U41>::type x41( args[41] ) ;
        typename Rcpp::traits::input_parameter<U42>::type x42( args[42] ) ;
        typename Rcpp::traits::input_parameter<U43>::type x43( args[43] ) ;
        typename Rcpp::traits::input_parameter<U44>::type x44( args[44] ) ;
        typename Rcpp::traits::input_parameter<U45>::type x45( args[45] ) ;
        typename Rcpp::traits::input_parameter<U46>::type x46( args[46] ) ;
        typename Rcpp::traits::input_parameter<U47>::type x47( args[47] ) ;
        typename Rcpp::traits::input_parameter<U48>::type x48( args[48] ) ;
        typename Rcpp::traits::input_parameter<U49>::type x49( args[49] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9, typename U10, typename U11, typename U12, typename U13, typename U14, typename U15, typename U16, typename U17, typename U18, typename U19, typename U20, typename U21, typename U22, typename U23, typename U24, typename U25, typename U26, typename U27, typename U28, typename U29, typename U30, typename U31, typename U32, typename U33, typename U34, typename U35, typename U36, typename U37, typename U38, typename U39, typename U40, typename U41, typename U42, typename U43, typename U44, typename U45, typename U46, typename U47, typename U48, typename U49, typename U50>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        typename Rcpp::traits::input_parameter<U5>::type x5( args[5] ) ;
        typename Rcpp::traits::input_parameter<U6>::type x6( args[6] ) ;
        typename Rcpp::traits::input_parameter<U7>::type x7( args[7] ) ;
        typename Rcpp::traits::input_parameter<U8>::type x8( args[8] ) ;
        typename Rcpp::traits::input_parameter<U9>::type x9( args[9] ) ;
        typename Rcpp::traits::input_parameter<U10>::type x10( args[10] ) ;
        typename Rcpp::traits::input_parameter<U11>::type x11( args[11] ) ;
        typename Rcpp::traits::input_parameter<U12>::type x12( args[12] ) ;
        typename Rcpp::traits::input_parameter<U13>::type x13( args[13] ) ;
        typename Rcpp::traits::input_parameter<U14>::type x14( args[14] ) ;
        typename Rcpp::traits::input_parameter<U15>::type x15( args[15] ) ;
        typename Rcpp::traits::input_parameter<U16>::type x16( args[16] ) ;
        typename Rcpp::traits::input_parameter<U17>::type x17( args[17] ) ;
        typename Rcpp::traits::input_parameter<U18>::type x18( args[18] ) ;
        typename Rcpp::traits::input_parameter<U19>::type x19( args[19] ) ;
        typename Rcpp::traits::input_parameter<U20>::type x20( args[20] ) ;
        typename Rcpp::traits::input_parameter<U21>::type x21( args[21] ) ;
        typename Rcpp::traits::input_parameter<U22>::type x22( args[22] ) ;
        typename Rcpp::traits::input_parameter<U23>::type x23( args[23] ) ;
        typename Rcpp::traits::input_parameter<U24>::type x24( args[24] ) ;
        typename Rcpp::traits::input_parameter<U25>::type x25( args[25] ) ;
        typename Rcpp::traits::input_parameter<U26>::type x26( args[26] ) ;
        typename Rcpp::traits::input_parameter<U27>::type x27( args[27] ) ;
        typename Rcpp::traits::input_parameter<U28>::type x28( args[28] ) ;
        typename Rcpp::traits::input_parameter<U29>::type x29( args[29] ) ;
        typename Rcpp::traits::input_parameter<U30>::type x30( args[30] ) ;
        typename Rcpp::traits::input_parameter<U31>::type x31( args[31] ) ;
        typename Rcpp::traits::input_parameter<U32>::type x32( args[32] ) ;
        typename Rcpp::traits::input_parameter<U33>::type x33( args[33] ) ;
        typename Rcpp::traits::input_parameter<U34>::type x34( args[34] ) ;
        typename Rcpp::traits::input_parameter<U35>::type x35( args[35] ) ;
        typename Rcpp::traits::input_parameter<U36>::type x36( args[36] ) ;
        typename Rcpp::traits::input_parameter<U37>::type x37( args[37] ) ;
        typename Rcpp::traits::input_parameter<U38>::type x38( args[38] ) ;
        typename Rcpp::traits::input_parameter<U39>::type x39( args[39] ) ;
        typename Rcpp::traits::input_parameter<U40>::type x40( args[40] ) ;
        typename Rcpp::traits::input_parameter<U41>::type x41( args[41] ) ;
        typename Rcpp::traits::input_parameter<U42>::type x42( args[42] ) ;
        typename Rcpp::traits::input_parameter<U43>::type x43( args[43] ) ;
        typename Rcpp::traits::input_parameter<U44>::type x44( args[44] ) ;
        typename Rcpp::traits::input_parameter<U45>::type x45( args[45] ) ;
        typename Rcpp::traits::input_parameter<U46>::type x46( args[46] ) ;
        typename Rcpp::traits::input_parameter<U47>::type x47( args[47] ) ;
        typename Rcpp::traits::input_parameter<U48>::type x48( args[48] ) ;
        typename Rcpp::traits::input_parameter<U49>::type x49( args[49] ) ;
        typename Rcpp::traits::input_parameter<U50>::type x50( args[50] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9, typename U10, typename U11, typename U12, typename U13, typename U14, typename U15, typename U16, typename U17, typename U18, typename U19, typename U20, typename U21, typename U22, typename U23, typename U24, typename U25, typename U26, typename U27, typename U28, typename U29, typename U30, typename U31, typename U32, typename U33, typename U34, typename U35, typename U36, typename U37, typename U38, typename U39, typename U40, typename U41, typename U42, typename U43, typename U44, typename U45, typename U46, typename U47, typename U48, typename U49, typename U50, typename U51>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        typename Rcpp::traits::input_parameter<U5>::type x5( args[5] ) ;
        typename Rcpp::traits::input_parameter<U6>::type x6( args[6] ) ;
        typename Rcpp::traits::input_parameter<U7>::type x7( args[7] ) ;
        typename Rcpp::traits::input_parameter<U8>::type x8( args[8] ) ;
        typename Rcpp::traits::input_parameter<U9>::type x9( args[9] ) ;
        typename Rcpp::traits::input_parameter<U10>::type x10( args[10] ) ;
        typename Rcpp::traits::input_parameter<U11>::type x11( args[11] ) ;
        typename Rcpp::traits::input_parameter<U12>::type x12( args[12] ) ;
        typename Rcpp::traits::input_parameter<U13>::type x13( args[13] ) ;
        typename Rcpp::traits::input_parameter<U14>::type x14( args[14] ) ;
        typename Rcpp::traits::input_parameter<U15>::type x15( args[15] ) ;
        typename Rcpp::traits::input_parameter<U16>::type x16( args[16] ) ;
        typename Rcpp::traits::input_parameter<U17>::type x17( args[17] ) ;
        typename Rcpp::traits::input_parameter<U18>::type x18( args[18] ) ;
        typename Rcpp::traits::input_parameter<U19>::type x19( args[19] ) ;
        typename Rcpp::traits::input_parameter<U20>::type x20( args[20] ) ;
        typename Rcpp::traits::input_parameter<U21>::type x21( args[21] ) ;
        typename Rcpp::traits::input_parameter<U22>::type x22( args[22] ) ;
        typename Rcpp::traits::input_parameter<U23>::type x23( args[23] ) ;
        typename Rcpp::traits::input_parameter<U24>::type x24( args[24] ) ;
        typename Rcpp::traits::input_parameter<U25>::type x25( args[25] ) ;
        typename Rcpp::traits::input_parameter<U26>::type x26( args[26] ) ;
        typename Rcpp::traits::input_parameter<U27>::type x27( args[27] ) ;
        typename Rcpp::traits::input_parameter<U28>::type x28( args[28] ) ;
        typename Rcpp::traits::input_parameter<U29>::type x29( args[29] ) ;
        typename Rcpp::traits::input_parameter<U30>::type x30( args[30] ) ;
        typename Rcpp::traits::input_parameter<U31>::type x31( args[31] ) ;
        typename Rcpp::traits::input_parameter<U32>::type x32( args[32] ) ;
        typename Rcpp::traits::input_parameter<U33>::type x33( args[33] ) ;
        typename Rcpp::traits::input_parameter<U34>::type x34( args[34] ) ;
        typename Rcpp::traits::input_parameter<U35>::type x35( args[35] ) ;
        typename Rcpp::traits::input_parameter<U36>::type x36( args[36] ) ;
        typename Rcpp::traits::input_parameter<U37>::type x37( args[37] ) ;
        typename Rcpp::traits::input_parameter<U38>::type x38( args[38] ) ;
        typename Rcpp::traits::input_parameter<U39>::type x39( args[39] ) ;
        typename Rcpp::traits::input_parameter<U40>::type x40( args[40] ) ;
        typename Rcpp::traits::input_parameter<U41>::type x41( args[41] ) ;
        typename Rcpp::traits::input_parameter<U42>::type x42( args[42] ) ;
        typename Rcpp::traits::input_parameter<U43>::type x43( args[43] ) ;
        typename Rcpp::traits::input_parameter<U44>::type x44( args[44] ) ;
        typename Rcpp::traits::input_parameter<U45>::type x45( args[45] ) ;
        typename Rcpp::traits::input_parameter<U46>::type x46( args[46] ) ;
        typename Rcpp::traits::input_parameter<U47>::type x47( args[47] ) ;
        typename Rcpp::traits::input_parameter<U48>::type x48( args[48] ) ;
        typename Rcpp::traits::input_parameter<U49>::type x49( args[49] ) ;
        typename Rcpp::traits::input_parameter<U50>::type x50( args[50] ) ;
        typename Rcpp::traits::input_parameter<U51>::type x51( args[51] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9, typename U10, typename U11, typename U12, typename U13, typename U14, typename U15, typename U16, typename U17, typename U18, typename U19, typename U20, typename U21, typename U22, typename U23, typename U24, typename U25, typename U26, typename U27, typename U28, typename U29, typename U30, typename U31, typename U32, typename U33, typename U34, typename U35, typename U36, typename U37, typename U38, typename U39, typename U40, typename U41, typename U42, typename U43, typename U44, typename U45, typename U46, typename U47, typename U48, typename U49, typename U50, typename U51, typename U52>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        typename Rcpp::traits::input_parameter<U5>::type x5( args[5] ) ;
        typename Rcpp::traits::input_parameter<U6>::type x6( args[6] ) ;
        typename Rcpp::traits::input_parameter<U7>::type x7( args[7] ) ;
        typename Rcpp::traits::input_parameter<U8>::type x8( args[8] ) ;
        typename Rcpp::traits::input_parameter<U9>::type x9( args[9] ) ;
        typename Rcpp::traits::input_parameter<U10>::type x10( args[10] ) ;
        typename Rcpp::traits::input_parameter<U11>::type x11( args[11] ) ;
        typename Rcpp::traits::input_parameter<U12>::type x12( args[12] ) ;
        typename Rcpp::traits::input_parameter<U13>::type x13( args[13] ) ;
        typename Rcpp::traits::input_parameter<U14>::type x14( args[14] ) ;
        typename Rcpp::traits::input_parameter<U15>::type x15( args[15] ) ;
        typename Rcpp::traits::input_parameter<U16>::type x16( args[16] ) ;
        typename Rcpp::traits::input_parameter<U17>::type x17( args[17] ) ;
        typename Rcpp::traits::input_parameter<U18>::type x18( args[18] ) ;
        typename Rcpp::traits::input_parameter<U19>::type x19( args[19] ) ;
        typename Rcpp::traits::input_parameter<U20>::type x20( args[20] ) ;
        typename Rcpp::traits::input_parameter<U21>::type x21( args[21] ) ;
        typename Rcpp::traits::input_parameter<U22>::type x22( args[22] ) ;
        typename Rcpp::traits::input_parameter<U23>::type x23( args[23] ) ;
        typename Rcpp::traits::input_parameter<U24>::type x24( args[24] ) ;
        typename Rcpp::traits::input_parameter<U25>::type x25( args[25] ) ;
        typename Rcpp::traits::input_parameter<U26>::type x26( args[26] ) ;
        typename Rcpp::traits::input_parameter<U27>::type x27( args[27] ) ;
        typename Rcpp::traits::input_parameter<U28>::type x28( args[28] ) ;
        typename Rcpp::traits::input_parameter<U29>::type x29( args[29] ) ;
        typename Rcpp::traits::input_parameter<U30>::type x30( args[30] ) ;
        typename Rcpp::traits::input_parameter<U31>::type x31( args[31] ) ;
        typename Rcpp::traits::input_parameter<U32>::type x32( args[32] ) ;
        typename Rcpp::traits::input_parameter<U33>::type x33( args[33] ) ;
        typename Rcpp::traits::input_parameter<U34>::type x34( args[34] ) ;
        typename Rcpp::traits::input_parameter<U35>::type x35( args[35] ) ;
        typename Rcpp::traits::input_parameter<U36>::type x36( args[36] ) ;
        typename Rcpp::traits::input_parameter<U37>::type x37( args[37] ) ;
        typename Rcpp::traits::input_parameter<U38>::type x38( args[38] ) ;
        typename Rcpp::traits::input_parameter<U39>::type x39( args[39] ) ;
        typename Rcpp::traits::input_parameter<U40>::type x40( args[40] ) ;
        typename Rcpp::traits::input_parameter<U41>::type x41( args[41] ) ;
        typename Rcpp::traits::input_parameter<U42>::type x42( args[42] ) ;
        typename Rcpp::traits::input_parameter<U43>::type x43( args[43] ) ;
        typename Rcpp::traits::input_parameter<U44>::type x44( args[44] ) ;
        typename Rcpp::traits::input_parameter<U45>::type x45( args[45] ) ;
        typename Rcpp::traits::input_parameter<U46>::type x46( args[46] ) ;
        typename Rcpp::traits::input_parameter<U47>::type x47( args[47] ) ;
        typename Rcpp::traits::input_parameter<U48>::type x48( args[48] ) ;
        typename Rcpp::traits::input_parameter<U49>::type x49( args[49] ) ;
        typename Rcpp::traits::input_parameter<U50>::type x50( args[50] ) ;
        typename Rcpp::traits::input_parameter<U51>::type x51( args[51] ) ;
        typename Rcpp::traits::input_parameter<U52>::type x52( args[52] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9, typename U10, typename U11, typename U12, typename U13, typename U14, typename U15, typename U16, typename U17, typename U18, typename U19, typename U20, typename U21, typename U22, typename U23, typename U24, typename U25, typename U26, typename U27, typename U28, typename U29, typename U30, typename U31, typename U32, typename U33, typename U34, typename U35, typename U36, typename U37, typename U38, typename U39, typename U40, typename U41, typename U42, typename U43, typename U44, typename U45, typename U46, typename U47, typename U48, typename U49, typename U50, typename U51, typename U52, typename U53>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        typename Rcpp::traits::input_parameter<U5>::type x5( args[5] ) ;
        typename Rcpp::traits::input_parameter<U6>::type x6( args[6] ) ;
        typename Rcpp::traits::input_parameter<U7>::type x7( args[7] ) ;
        typename Rcpp::traits::input_parameter<U8>::type x8( args[8] ) ;
        typename Rcpp::traits::input_parameter<U9>::type x9( args[9] ) ;
        typename Rcpp::traits::input_parameter<U10>::type x10( args[10] ) ;
        typename Rcpp::traits::input_parameter<U11>::type x11( args[11] ) ;
        typename Rcpp::traits::input_parameter<U12>::type x12( args[12] ) ;
        typename Rcpp::traits::input_parameter<U13>::type x13( args[13] ) ;
        typename Rcpp::traits::input_parameter<U14>::type x14( args[14] ) ;
        typename Rcpp::traits::input_parameter<U15>::type x15( args[15] ) ;
        typename Rcpp::traits::input_parameter<U16>::type x16( args[16] ) ;
        typename Rcpp::traits::input_parameter<U17>::type x17( args[17] ) ;
        typename Rcpp::traits::input_parameter<U18>::type x18( args[18] ) ;
        typename Rcpp::traits::input_parameter<U19>::type x19( args[19] ) ;
        typename Rcpp::traits::input_parameter<U20>::type x20( args[20] ) ;
        typename Rcpp::traits::input_parameter<U21>::type x21( args[21] ) ;
        typename Rcpp::traits::input_parameter<U22>::type x22( args[22] ) ;
        typename Rcpp::traits::input_parameter<U23>::type x23( args[23] ) ;
        typename Rcpp::traits::input_parameter<U24>::type x24( args[24] ) ;
        typename Rcpp::traits::input_parameter<U25>::type x25( args[25] ) ;
        typename Rcpp::traits::input_parameter<U26>::type x26( args[26] ) ;
        typename Rcpp::traits::input_parameter<U27>::type x27( args[27] ) ;
        typename Rcpp::traits::input_parameter<U28>::type x28( args[28] ) ;
        typename Rcpp::traits::input_parameter<U29>::type x29( args[29] ) ;
        typename Rcpp::traits::input_parameter<U30>::type x30( args[30] ) ;
        typename Rcpp::traits::input_parameter<U31>::type x31( args[31] ) ;
        typename Rcpp::traits::input_parameter<U32>::type x32( args[32] ) ;
        typename Rcpp::traits::input_parameter<U33>::type x33( args[33] ) ;
        typename Rcpp::traits::input_parameter<U34>::type x34( args[34] ) ;
        typename Rcpp::traits::input_parameter<U35>::type x35( args[35] ) ;
        typename Rcpp::traits::input_parameter<U36>::type x36( args[36] ) ;
        typename Rcpp::traits::input_parameter<U37>::type x37( args[37] ) ;
        typename Rcpp::traits::input_parameter<U38>::type x38( args[38] ) ;
        typename Rcpp::traits::input_parameter<U39>::type x39( args[39] ) ;
        typename Rcpp::traits::input_parameter<U40>::type x40( args[40] ) ;
        typename Rcpp::traits::input_parameter<U41>::type x41( args[41] ) ;
        typename Rcpp::traits::input_parameter<U42>::type x42( args[42] ) ;
        typename Rcpp::traits::input_parameter<U43>::type x43( args[43] ) ;
        typename Rcpp::traits::input_parameter<U44>::type x44( args[44] ) ;
        typename Rcpp::traits::input_parameter<U45>::type x45( args[45] ) ;
        typename Rcpp::traits::input_parameter<U46>::type x46( args[46] ) ;
        typename Rcpp::traits::input_parameter<U47>::type x47( args[47] ) ;
        typename Rcpp::traits::input_parameter<U48>::type x48( args[48] ) ;
        typename Rcpp::traits::input_parameter<U49>::type x49( args[49] ) ;
        typename Rcpp::traits::input_parameter<U50>::type x50( args[50] ) ;
        typename Rcpp::traits::input_parameter<U51>::type x51( args[51] ) ;
        typename Rcpp::traits::input_parameter<U52>::type x52( args[52] ) ;
        typename Rcpp::traits::input_parameter<U53>::type x53( args[53] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9, typename U10, typename U11, typename U12, typename U13, typename U14, typename U15, typename U16, typename U17, typename U18, typename U19, typename U20, typename U21, typename U22, typename U23, typename U24, typename U25, typename U26, typename U27, typename U28, typename U29, typename U30, typename U31, typename U32, typename U33, typename U34, typename U35, typename U36, typename U37, typename U38, typename U39, typename U40, typename U41, typename U42, typename U43, typename U44, typename U45, typename U46, typename U47, typename U48, typename U49, typename U50, typename U51, typename U52, typename U53, typename U54>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        typename Rcpp::traits::input_parameter<U5>::type x5( args[5] ) ;
        typename Rcpp::traits::input_parameter<U6>::type x6( args[6] ) ;
        typename Rcpp::traits::input_parameter<U7>::type x7( args[7] ) ;
        typename Rcpp::traits::input_parameter<U8>::type x8( args[8] ) ;
        typename Rcpp::traits::input_parameter<U9>::type x9( args[9] ) ;
        typename Rcpp::traits::input_parameter<U10>::type x10( args[10] ) ;
        typename Rcpp::traits::input_parameter<U11>::type x11( args[11] ) ;
        typename Rcpp::traits::input_parameter<U12>::type x12( args[12] ) ;
        typename Rcpp::traits::input_parameter<U13>::type x13( args[13] ) ;
        typename Rcpp::traits::input_parameter<U14>::type x14( args[14] ) ;
        typename Rcpp::traits::input_parameter<U15>::type x15( args[15] ) ;
        typename Rcpp::traits::input_parameter<U16>::type x16( args[16] ) ;
        typename Rcpp::traits::input_parameter<U17>::type x17( args[17] ) ;
        typename Rcpp::traits::input_parameter<U18>::type x18( args[18] ) ;
        typename Rcpp::traits::input_parameter<U19>::type x19( args[19] ) ;
        typename Rcpp::traits::input_parameter<U20>::type x20( args[20] ) ;
        typename Rcpp::traits::input_parameter<U21>::type x21( args[21] ) ;
        typename Rcpp::traits::input_parameter<U22>::type x22( args[22] ) ;
        typename Rcpp::traits::input_parameter<U23>::type x23( args[23] ) ;
        typename Rcpp::traits::input_parameter<U24>::type x24( args[24] ) ;
        typename Rcpp::traits::input_parameter<U25>::type x25( args[25] ) ;
        typename Rcpp::traits::input_parameter<U26>::type x26( args[26] ) ;
        typename Rcpp::traits::input_parameter<U27>::type x27( args[27] ) ;
        typename Rcpp::traits::input_parameter<U28>::type x28( args[28] ) ;
        typename Rcpp::traits::input_parameter<U29>::type x29( args[29] ) ;
        typename Rcpp::traits::input_parameter<U30>::type x30( args[30] ) ;
        typename Rcpp::traits::input_parameter<U31>::type x31( args[31] ) ;
        typename Rcpp::traits::input_parameter<U32>::type x32( args[32] ) ;
        typename Rcpp::traits::input_parameter<U33>::type x33( args[33] ) ;
        typename Rcpp::traits::input_parameter<U34>::type x34( args[34] ) ;
        typename Rcpp::traits::input_parameter<U35>::type x35( args[35] ) ;
        typename Rcpp::traits::input_parameter<U36>::type x36( args[36] ) ;
        typename Rcpp::traits::input_parameter<U37>::type x37( args[37] ) ;
        typename Rcpp::traits::input_parameter<U38>::type x38( args[38] ) ;
        typename Rcpp::traits::input_parameter<U39>::type x39( args[39] ) ;
        typename Rcpp::traits::input_parameter<U40>::type x40( args[40] ) ;
        typename Rcpp::traits::input_parameter<U41>::type x41( args[41] ) ;
        typename Rcpp::traits::input_parameter<U42>::type x42( args[42] ) ;
        typename Rcpp::traits::input_parameter<U43>::type x43( args[43] ) ;
        typename Rcpp::traits::input_parameter<U44>::type x44( args[44] ) ;
        typename Rcpp::traits::input_parameter<U45>::type x45( args[45] ) ;
        typename Rcpp::traits::input_parameter<U46>::type x46( args[46] ) ;
        typename Rcpp::traits::input_parameter<U47>::type x47( args[47] ) ;
        typename Rcpp::traits::input_parameter<U48>::type x48( args[48] ) ;
        typename Rcpp::traits::input_parameter<U49>::type x49( args[49] ) ;
        typename Rcpp::traits::input_parameter<U50>::type x50( args[50] ) ;
        typename Rcpp::traits::input_parameter<U51>::type x51( args[51] ) ;
        typename Rcpp::traits::input_parameter<U52>::type x52( args[52] ) ;
        typename Rcpp::traits::input_parameter<U53>::type x53( args[53] ) ;
        typename Rcpp::traits::input_parameter<U54>::type x54( args[54] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9, typename U10, typename U11, typename U12, typename U13, typename U14, typename U15, typename U16, typename U17, typename U18, typename U19, typename U20, typename U21, typename U22, typename U23, typename U24, typename U25, typename U26, typename U27, typename U28, typename U29, typename U30, typename U31, typename U32, typename U33, typename U34, typename U35, typename U36, typename U37, typename U38, typename U39, typename U40, typename U41, typename U42, typename U43, typename U44, typename U45, typename U46, typename U47, typename U48, typename U49, typename U50, typename U51, typename U52, typename U53, typename U54, typename U55>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        typename Rcpp::traits::input_parameter<U5>::type x5( args[5] ) ;
        typename Rcpp::traits::input_parameter<U6>::type x6( args[6] ) ;
        typename Rcpp::traits::input_parameter<U7>::type x7( args[7] ) ;
        typename Rcpp::traits::input_parameter<U8>::type x8( args[8] ) ;
        typename Rcpp::traits::input_parameter<U9>::type x9( args[9] ) ;
        typename Rcpp::traits::input_parameter<U10>::type x10( args[10] ) ;
        typename Rcpp::traits::input_parameter<U11>::type x11( args[11] ) ;
        typename Rcpp::traits::input_parameter<U12>::type x12( args[12] ) ;
        typename Rcpp::traits::input_parameter<U13>::type x13( args[13] ) ;
        typename Rcpp::traits::input_parameter<U14>::type x14( args[14] ) ;
        typename Rcpp::traits::input_parameter<U15>::type x15( args[15] ) ;
        typename Rcpp::traits::input_parameter<U16>::type x16( args[16] ) ;
        typename Rcpp::traits::input_parameter<U17>::type x17( args[17] ) ;
        typename Rcpp::traits::input_parameter<U18>::type x18( args[18] ) ;
        typename Rcpp::traits::input_parameter<U19>::type x19( args[19] ) ;
        typename Rcpp::traits::input_parameter<U20>::type x20( args[20] ) ;
        typename Rcpp::traits::input_parameter<U21>::type x21( args[21] ) ;
        typename Rcpp::traits::input_parameter<U22>::type x22( args[22] ) ;
        typename Rcpp::traits::input_parameter<U23>::type x23( args[23] ) ;
        typename Rcpp::traits::input_parameter<U24>::type x24( args[24] ) ;
        typename Rcpp::traits::input_parameter<U25>::type x25( args[25] ) ;
        typename Rcpp::traits::input_parameter<U26>::type x26( args[26] ) ;
        typename Rcpp::traits::input_parameter<U27>::type x27( args[27] ) ;
        typename Rcpp::traits::input_parameter<U28>::type x28( args[28] ) ;
        typename Rcpp::traits::input_parameter<U29>::type x29( args[29] ) ;
        typename Rcpp::traits::input_parameter<U30>::type x30( args[30] ) ;
        typename Rcpp::traits::input_parameter<U31>::type x31( args[31] ) ;
        typename Rcpp::traits::input_parameter<U32>::type x32( args[32] ) ;
        typename Rcpp::traits::input_parameter<U33>::type x33( args[33] ) ;
        typename Rcpp::traits::input_parameter<U34>::type x34( args[34] ) ;
        typename Rcpp::traits::input_parameter<U35>::type x35( args[35] ) ;
        typename Rcpp::traits::input_parameter<U36>::type x36( args[36] ) ;
        typename Rcpp::traits::input_parameter<U37>::type x37( args[37] ) ;
        typename Rcpp::traits::input_parameter<U38>::type x38( args[38] ) ;
        typename Rcpp::traits::input_parameter<U39>::type x39( args[39] ) ;
        typename Rcpp::traits::input_parameter<U40>::type x40( args[40] ) ;
        typename Rcpp::traits::input_parameter<U41>::type x41( args[41] ) ;
        typename Rcpp::traits::input_parameter<U42>::type x42( args[42] ) ;
        typename Rcpp::traits::input_parameter<U43>::type x43( args[43] ) ;
        typename Rcpp::traits::input_parameter<U44>::type x44( args[44] ) ;
        typename Rcpp::traits::input_parameter<U45>::type x45( args[45] ) ;
        typename Rcpp::traits::input_parameter<U46>::type x46( args[46] ) ;
        typename Rcpp::traits::input_parameter<U47>::type x47( args[47] ) ;
        typename Rcpp::traits::input_parameter<U48>::type x48( args[48] ) ;
        typename Rcpp::traits::input_parameter<U49>::type x49( args[49] ) ;
        typename Rcpp::traits::input_parameter<U50>::type x50( args[50] ) ;
        typename Rcpp::traits::input_parameter<U51>::type x51( args[51] ) ;
        typename Rcpp::traits::input_parameter<U52>::type x52( args[52] ) ;
        typename Rcpp::traits::input_parameter<U53>::type x53( args[53] ) ;
        typename Rcpp::traits::input_parameter<U54>::type x54( args[54] ) ;
        typename Rcpp::traits::input_parameter<U55>::type x55( args[55] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9, typename U10, typename U11, typename U12, typename U13, typename U14, typename U15, typename U16, typename U17, typename U18, typename U19, typename U20, typename U21, typename U22, typename U23, typename U24, typename U25, typename U26, typename U27, typename U28, typename U29, typename U30, typename U31, typename U32, typename U33, typename U34, typename U35, typename U36, typename U37, typename U38, typename U39, typename U40, typename U41, typename U42, typename U43, typename U44, typename U45, typename U46, typename U47, typename U48, typename U49, typename U50, typename U51, typename U52, typename U53, typename U54, typename U55, typename U56>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        typename Rcpp::traits::input_parameter<U5>::type x5( args[5] ) ;
        typename Rcpp::traits::input_parameter<U6>::type x6( args[6] ) ;
        typename Rcpp::traits::input_parameter<U7>::type x7( args[7] ) ;
        typename Rcpp::traits::input_parameter<U8>::type x8( args[8] ) ;
        typename Rcpp::traits::input_parameter<U9>::type x9( args[9] ) ;
        typename Rcpp::traits::input_parameter<U10>::type x10( args[10] ) ;
        typename Rcpp::traits::input_parameter<U11>::type x11( args[11] ) ;
        typename Rcpp::traits::input_parameter<U12>::type x12( args[12] ) ;
        typename Rcpp::traits::input_parameter<U13>::type x13( args[13] ) ;
        typename Rcpp::traits::input_parameter<U14>::type x14( args[14] ) ;
        typename Rcpp::traits::input_parameter<U15>::type x15( args[15] ) ;
        typename Rcpp::traits::input_parameter<U16>::type x16( args[16] ) ;
        typename Rcpp::traits::input_parameter<U17>::type x17( args[17] ) ;
        typename Rcpp::traits::input_parameter<U18>::type x18( args[18] ) ;
        typename Rcpp::traits::input_parameter<U19>::type x19( args[19] ) ;
        typename Rcpp::traits::input_parameter<U20>::type x20( args[20] ) ;
        typename Rcpp::traits::input_parameter<U21>::type x21( args[21] ) ;
        typename Rcpp::traits::input_parameter<U22>::type x22( args[22] ) ;
        typename Rcpp::traits::input_parameter<U23>::type x23( args[23] ) ;
        typename Rcpp::traits::input_parameter<U24>::type x24( args[24] ) ;
        typename Rcpp::traits::input_parameter<U25>::type x25( args[25] ) ;
        typename Rcpp::traits::input_parameter<U26>::type x26( args[26] ) ;
        typename Rcpp::traits::input_parameter<U27>::type x27( args[27] ) ;
        typename Rcpp::traits::input_parameter<U28>::type x28( args[28] ) ;
        typename Rcpp::traits::input_parameter<U29>::type x29( args[29] ) ;
        typename Rcpp::traits::input_parameter<U30>::type x30( args[30] ) ;
        typename Rcpp::traits::input_parameter<U31>::type x31( args[31] ) ;
        typename Rcpp::traits::input_parameter<U32>::type x32( args[32] ) ;
        typename Rcpp::traits::input_parameter<U33>::type x33( args[33] ) ;
        typename Rcpp::traits::input_parameter<U34>::type x34( args[34] ) ;
        typename Rcpp::traits::input_parameter<U35>::type x35( args[35] ) ;
        typename Rcpp::traits::input_parameter<U36>::type x36( args[36] ) ;
        typename Rcpp::traits::input_parameter<U37>::type x37( args[37] ) ;
        typename Rcpp::traits::input_parameter<U38>::type x38( args[38] ) ;
        typename Rcpp::traits::input_parameter<U39>::type x39( args[39] ) ;
        typename Rcpp::traits::input_parameter<U40>::type x40( args[40] ) ;
        typename Rcpp::traits::input_parameter<U41>::type x41( args[41] ) ;
        typename Rcpp::traits::input_parameter<U42>::type x42( args[42] ) ;
        typename Rcpp::traits::input_parameter<U43>::type x43( args[43] ) ;
        typename Rcpp::traits::input_parameter<U44>::type x44( args[44] ) ;
        typename Rcpp::traits::input_parameter<U45>::type x45( args[45] ) ;
        typename Rcpp::traits::input_parameter<U46>::type x46( args[46] ) ;
        typename Rcpp::traits::input_parameter<U47>::type x47( args[47] ) ;
        typename Rcpp::traits::input_parameter<U48>::type x48( args[48] ) ;
        typename Rcpp::traits::input_parameter<U49>::type x49( args[49] ) ;
        typename Rcpp::traits::input_parameter<U50>::type x50( args[50] ) ;
        typename Rcpp::traits::input_parameter<U51>::type x51( args[51] ) ;
        typename Rcpp::traits::input_parameter<U52>::type x52( args[52] ) ;
        typename Rcpp::traits::input_parameter<U53>::type x53( args[53] ) ;
        typename Rcpp::traits::input_parameter<U54>::type x54( args[54] ) ;
        typename Rcpp::traits::input_parameter<U55>::type x55( args[55] ) ;
        typename Rcpp::traits::input_parameter<U56>::type x56( args[56] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9, typename U10, typename U11, typename U12, typename U13, typename U14, typename U15, typename U16, typename U17, typename U18, typename U19, typename U20, typename U21, typename U22, typename U23, typename U24, typename U25, typename U26, typename U27, typename U28, typename U29, typename U30, typename U31, typename U32, typename U33, typename U34, typename U35, typename U36, typename U37, typename U38, typename U39, typename U40, typename U41, typename U42, typename U43, typename U44, typename U45, typename U46, typename U47, typename U48, typename U49, typename U50, typename U51, typename U52, typename U53, typename U54, typename U55, typename U56, typename U57>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        typename Rcpp::traits::input_parameter<U5>::type x5( args[5] ) ;
        typename Rcpp::traits::input_parameter<U6>::type x6( args[6] ) ;
        typename Rcpp::traits::input_parameter<U7>::type x7( args[7] ) ;
        typename Rcpp::traits::input_parameter<U8>::type x8( args[8] ) ;
        typename Rcpp::traits::input_parameter<U9>::type x9( args[9] ) ;
        typename Rcpp::traits::input_parameter<U10>::type x10( args[10] ) ;
        typename Rcpp::traits::input_parameter<U11>::type x11( args[11] ) ;
        typename Rcpp::traits::input_parameter<U12>::type x12( args[12] ) ;
        typename Rcpp::traits::input_parameter<U13>::type x13( args[13] ) ;
        typename Rcpp::traits::input_parameter<U14>::type x14( args[14] ) ;
        typename Rcpp::traits::input_parameter<U15>::type x15( args[15] ) ;
        typename Rcpp::traits::input_parameter<U16>::type x16( args[16] ) ;
        typename Rcpp::traits::input_parameter<U17>::type x17( args[17] ) ;
        typename Rcpp::traits::input_parameter<U18>::type x18( args[18] ) ;
        typename Rcpp::traits::input_parameter<U19>::type x19( args[19] ) ;
        typename Rcpp::traits::input_parameter<U20>::type x20( args[20] ) ;
        typename Rcpp::traits::input_parameter<U21>::type x21( args[21] ) ;
        typename Rcpp::traits::input_parameter<U22>::type x22( args[22] ) ;
        typename Rcpp::traits::input_parameter<U23>::type x23( args[23] ) ;
        typename Rcpp::traits::input_parameter<U24>::type x24( args[24] ) ;
        typename Rcpp::traits::input_parameter<U25>::type x25( args[25] ) ;
        typename Rcpp::traits::input_parameter<U26>::type x26( args[26] ) ;
        typename Rcpp::traits::input_parameter<U27>::type x27( args[27] ) ;
        typename Rcpp::traits::input_parameter<U28>::type x28( args[28] ) ;
        typename Rcpp::traits::input_parameter<U29>::type x29( args[29] ) ;
        typename Rcpp::traits::input_parameter<U30>::type x30( args[30] ) ;
        typename Rcpp::traits::input_parameter<U31>::type x31( args[31] ) ;
        typename Rcpp::traits::input_parameter<U32>::type x32( args[32] ) ;
        typename Rcpp::traits::input_parameter<U33>::type x33( args[33] ) ;
        typename Rcpp::traits::input_parameter<U34>::type x34( args[34] ) ;
        typename Rcpp::traits::input_parameter<U35>::type x35( args[35] ) ;
        typename Rcpp::traits::input_parameter<U36>::type x36( args[36] ) ;
        typename Rcpp::traits::input_parameter<U37>::type x37( args[37] ) ;
        typename Rcpp::traits::input_parameter<U38>::type x38( args[38] ) ;
        typename Rcpp::traits::input_parameter<U39>::type x39( args[39] ) ;
        typename Rcpp::traits::input_parameter<U40>::type x40( args[40] ) ;
        typename Rcpp::traits::input_parameter<U41>::type x41( args[41] ) ;
        typename Rcpp::traits::input_parameter<U42>::type x42( args[42] ) ;
        typename Rcpp::traits::input_parameter<U43>::type x43( args[43] ) ;
        typename Rcpp::traits::input_parameter<U44>::type x44( args[44] ) ;
        typename Rcpp::traits::input_parameter<U45>::type x45( args[45] ) ;
        typename Rcpp::traits::input_parameter<U46>::type x46( args[46] ) ;
        typename Rcpp::traits::input_parameter<U47>::type x47( args[47] ) ;
        typename Rcpp::traits::input_parameter<U48>::type x48( args[48] ) ;
        typename Rcpp::traits::input_parameter<U49>::type x49( args[49] ) ;
        typename Rcpp::traits::input_parameter<U50>::type x50( args[50] ) ;
        typename Rcpp::traits::input_parameter<U51>::type x51( args[51] ) ;
        typename Rcpp::traits::input_parameter<U52>::type x52( args[52] ) ;
        typename Rcpp::traits::input_parameter<U53>::type x53( args[53] ) ;
        typename Rcpp::traits::input_parameter<U54>::type x54( args[54] ) ;
        typename Rcpp::traits::input_parameter<U55>::type x55( args[55] ) ;
        typename Rcpp::traits::input_parameter<U56>::type x56( args[56] ) ;
        typename Rcpp::traits::input_parameter<U57>::type x57( args[57] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9, typename U10, typename U11, typename U12, typename U13, typename U14, typename U15, typename U16, typename U17, typename U18, typename U19, typename U20, typename U21, typename U22, typename U23, typename U24, typename U25, typename U26, typename U27, typename U28, typename U29, typename U30, typename U31, typename U32, typename U33, typename U34, typename U35, typename U36, typename U37, typename U38, typename U39, typename U40, typename U41, typename U42, typename U43, typename U44, typename U45, typename U46, typename U47, typename U48, typename U49, typename U50, typename U51, typename U52, typename U53, typename U54, typename U55, typename U56, typename U57, typename U58>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        typename Rcpp::traits::input_parameter<U5>::type x5( args[5] ) ;
        typename Rcpp::traits::input_parameter<U6>::type x6( args[6] ) ;
        typename Rcpp::traits::input_parameter<U7>::type x7( args[7] ) ;
        typename Rcpp::traits::input_parameter<U8>::type x8( args[8] ) ;
        typename Rcpp::traits::input_parameter<U9>::type x9( args[9] ) ;
        typename Rcpp::traits::input_parameter<U10>::type x10( args[10] ) ;
        typename Rcpp::traits::input_parameter<U11>::type x11( args[11] ) ;
        typename Rcpp::traits::input_parameter<U12>::type x12( args[12] ) ;
        typename Rcpp::traits::input_parameter<U13>::type x13( args[13] ) ;
        typename Rcpp::traits::input_parameter<U14>::type x14( args[14] ) ;
        typename Rcpp::traits::input_parameter<U15>::type x15( args[15] ) ;
        typename Rcpp::traits::input_parameter<U16>::type x16( args[16] ) ;
        typename Rcpp::traits::input_parameter<U17>::type x17( args[17] ) ;
        typename Rcpp::traits::input_parameter<U18>::type x18( args[18] ) ;
        typename Rcpp::traits::input_parameter<U19>::type x19( args[19] ) ;
        typename Rcpp::traits::input_parameter<U20>::type x20( args[20] ) ;
        typename Rcpp::traits::input_parameter<U21>::type x21( args[21] ) ;
        typename Rcpp::traits::input_parameter<U22>::type x22( args[22] ) ;
        typename Rcpp::traits::input_parameter<U23>::type x23( args[23] ) ;
        typename Rcpp::traits::input_parameter<U24>::type x24( args[24] ) ;
        typename Rcpp::traits::input_parameter<U25>::type x25( args[25] ) ;
        typename Rcpp::traits::input_parameter<U26>::type x26( args[26] ) ;
        typename Rcpp::traits::input_parameter<U27>::type x27( args[27] ) ;
        typename Rcpp::traits::input_parameter<U28>::type x28( args[28] ) ;
        typename Rcpp::traits::input_parameter<U29>::type x29( args[29] ) ;
        typename Rcpp::traits::input_parameter<U30>::type x30( args[30] ) ;
        typename Rcpp::traits::input_parameter<U31>::type x31( args[31] ) ;
        typename Rcpp::traits::input_parameter<U32>::type x32( args[32] ) ;
        typename Rcpp::traits::input_parameter<U33>::type x33( args[33] ) ;
        typename Rcpp::traits::input_parameter<U34>::type x34( args[34] ) ;
        typename Rcpp::traits::input_parameter<U35>::type x35( args[35] ) ;
        typename Rcpp::traits::input_parameter<U36>::type x36( args[36] ) ;
        typename Rcpp::traits::input_parameter<U37>::type x37( args[37] ) ;
        typename Rcpp::traits::input_parameter<U38>::type x38( args[38] ) ;
        typename Rcpp::traits::input_parameter<U39>::type x39( args[39] ) ;
        typename Rcpp::traits::input_parameter<U40>::type x40( args[40] ) ;
        typename Rcpp::traits::input_parameter<U41>::type x41( args[41] ) ;
        typename Rcpp::traits::input_parameter<U42>::type x42( args[42] ) ;
        typename Rcpp::traits::input_parameter<U43>::type x43( args[43] ) ;
        typename Rcpp::traits::input_parameter<U44>::type x44( args[44] ) ;
        typename Rcpp::traits::input_parameter<U45>::type x45( args[45] ) ;
        typename Rcpp::traits::input_parameter<U46>::type x46( args[46] ) ;
        typename Rcpp::traits::input_parameter<U47>::type x47( args[47] ) ;
        typename Rcpp::traits::input_parameter<U48>::type x48( args[48] ) ;
        typename Rcpp::traits::input_parameter<U49>::type x49( args[49] ) ;
        typename Rcpp::traits::input_parameter<U50>::type x50( args[50] ) ;
        typename Rcpp::traits::input_parameter<U51>::type x51( args[51] ) ;
        typename Rcpp::traits::input_parameter<U52>::type x52( args[52] ) ;
        typename Rcpp::traits::input_parameter<U53>::type x53( args[53] ) ;
        typename Rcpp::traits::input_parameter<U54>::type x54( args[54] ) ;
        typename Rcpp::traits::input_parameter<U55>::type x55( args[55] ) ;
        typename Rcpp::traits::input_parameter<U56>::type x56( args[56] ) ;
        typename Rcpp::traits::input_parameter<U57>::type x57( args[57] ) ;
        typename Rcpp::traits::input_parameter<U58>::type x58( args[58] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9, typename U10, typename U11, typename U12, typename U13, typename U14, typename U15, typename U16, typename U17, typename U18, typename U19, typename U20, typename U21, typename U22, typename U23, typename U24, typename U25, typename U26, typename U27, typename U28, typename U29, typename U30, typename U31, typename U32, typename U33, typename U34, typename U35, typename U36, typename U37, typename U38, typename U39, typename U40, typename U41, typename U42, typename U43, typename U44, typename U45, typename U46, typename U47, typename U48, typename U49, typename U50, typename U51, typename U52, typename U53, typename U54, typename U55, typename U56, typename U57, typename U58, typename U59>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        typename Rcpp::traits::input_parameter<U5>::type x5( args[5] ) ;
        typename Rcpp::traits::input_parameter<U6>::type x6( args[6] ) ;
        typename Rcpp::traits::input_parameter<U7>::type x7( args[7] ) ;
        typename Rcpp::traits::input_parameter<U8>::type x8( args[8] ) ;
        typename Rcpp::traits::input_parameter<U9>::type x9( args[9] ) ;
        typename Rcpp::traits::input_parameter<U10>::type x10( args[10] ) ;
        typename Rcpp::traits::input_parameter<U11>::type x11( args[11] ) ;
        typename Rcpp::traits::input_parameter<U12>::type x12( args[12] ) ;
        typename Rcpp::traits::input_parameter<U13>::type x13( args[13] ) ;
        typename Rcpp::traits::input_parameter<U14>::type x14( args[14] ) ;
        typename Rcpp::traits::input_parameter<U15>::type x15( args[15] ) ;
        typename Rcpp::traits::input_parameter<U16>::type x16( args[16] ) ;
        typename Rcpp::traits::input_parameter<U17>::type x17( args[17] ) ;
        typename Rcpp::traits::input_parameter<U18>::type x18( args[18] ) ;
        typename Rcpp::traits::input_parameter<U19>::type x19( args[19] ) ;
        typename Rcpp::traits::input_parameter<U20>::type x20( args[20] ) ;
        typename Rcpp::traits::input_parameter<U21>::type x21( args[21] ) ;
        typename Rcpp::traits::input_parameter<U22>::type x22( args[22] ) ;
        typename Rcpp::traits::input_parameter<U23>::type x23( args[23] ) ;
        typename Rcpp::traits::input_parameter<U24>::type x24( args[24] ) ;
        typename Rcpp::traits::input_parameter<U25>::type x25( args[25] ) ;
        typename Rcpp::traits::input_parameter<U26>::type x26( args[26] ) ;
        typename Rcpp::traits::input_parameter<U27>::type x27( args[27] ) ;
        typename Rcpp::traits::input_parameter<U28>::type x28( args[28] ) ;
        typename Rcpp::traits::input_parameter<U29>::type x29( args[29] ) ;
        typename Rcpp::traits::input_parameter<U30>::type x30( args[30] ) ;
        typename Rcpp::traits::input_parameter<U31>::type x31( args[31] ) ;
        typename Rcpp::traits::input_parameter<U32>::type x32( args[32] ) ;
        typename Rcpp::traits::input_parameter<U33>::type x33( args[33] ) ;
        typename Rcpp::traits::input_parameter<U34>::type x34( args[34] ) ;
        typename Rcpp::traits::input_parameter<U35>::type x35( args[35] ) ;
        typename Rcpp::traits::input_parameter<U36>::type x36( args[36] ) ;
        typename Rcpp::traits::input_parameter<U37>::type x37( args[37] ) ;
        typename Rcpp::traits::input_parameter<U38>::type x38( args[38] ) ;
        typename Rcpp::traits::input_parameter<U39>::type x39( args[39] ) ;
        typename Rcpp::traits::input_parameter<U40>::type x40( args[40] ) ;
        typename Rcpp::traits::input_parameter<U41>::type x41( args[41] ) ;
        typename Rcpp::traits::input_parameter<U42>::type x42( args[42] ) ;
        typename Rcpp::traits::input_parameter<U43>::type x43( args[43] ) ;
        typename Rcpp::traits::input_parameter<U44>::type x44( args[44] ) ;
        typename Rcpp::traits::input_parameter<U45>::type x45( args[45] ) ;
        typename Rcpp::traits::input_parameter<U46>::type x46( args[46] ) ;
        typename Rcpp::traits::input_parameter<U47>::type x47( args[47] ) ;
        typename Rcpp::traits::input_parameter<U48>::type x48( args[48] ) ;
        typename Rcpp::traits::input_parameter<U49>::type x49( args[49] ) ;
        typename Rcpp::traits::input_parameter<U50>::type x50( args[50] ) ;
        typename Rcpp::traits::input_parameter<U51>::type x51( args[51] ) ;
        typename Rcpp::traits::input_parameter<U52>::type x52( args[52] ) ;
        typename Rcpp::traits::input_parameter<U53>::type x53( args[53] ) ;
        typename Rcpp::traits::input_parameter<U54>::type x54( args[54] ) ;
        typename Rcpp::traits::input_parameter<U55>::type x55( args[55] ) ;
        typename Rcpp::traits::input_parameter<U56>::type x56( args[56] ) ;
        typename Rcpp::traits::input_parameter<U57>::type x57( args[57] ) ;
        typename Rcpp::traits::input_parameter<U58>::type x58( args[58] ) ;
        typename Rcpp::traits::input_parameter<U59>::type x59( args[59] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9, typename U10, typename U11, typename U12, typename U13, typename U14, typename U15, typename U16, typename U17, typename U18, typename U19, typename U20, typename U21, typename U22, typename U23, typename U24, typename U25, typename U26, typename U27, typename U28, typename U29, typename U30, typename U31, typename U32, typename U33, typename U34, typename U35, typename U36, typename U37, typename U38, typename U39, typename U40, typename U41, typename U42, typename U43, typename U44, typename U45, typename U46, typename U47, typename U48, typename U49, typename U50, typename U51, typename U52, typename U53, typename U54, typename U55, typename U56, typename U57, typename U58, typename U59, typename U60>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        typename Rcpp::traits::input_parameter<U5>::type x5( args[5] ) ;
        typename Rcpp::traits::input_parameter<U6>::type x6( args[6] ) ;
        typename Rcpp::traits::input_parameter<U7>::type x7( args[7] ) ;
        typename Rcpp::traits::input_parameter<U8>::type x8( args[8] ) ;
        typename Rcpp::traits::input_parameter<U9>::type x9( args[9] ) ;
        typename Rcpp::traits::input_parameter<U10>::type x10( args[10] ) ;
        typename Rcpp::traits::input_parameter<U11>::type x11( args[11] ) ;
        typename Rcpp::traits::input_parameter<U12>::type x12( args[12] ) ;
        typename Rcpp::traits::input_parameter<U13>::type x13( args[13] ) ;
        typename Rcpp::traits::input_parameter<U14>::type x14( args[14] ) ;
        typename Rcpp::traits::input_parameter<U15>::type x15( args[15] ) ;
        typename Rcpp::traits::input_parameter<U16>::type x16( args[16] ) ;
        typename Rcpp::traits::input_parameter<U17>::type x17( args[17] ) ;
        typename Rcpp::traits::input_parameter<U18>::type x18( args[18] ) ;
        typename Rcpp::traits::input_parameter<U19>::type x19( args[19] ) ;
        typename Rcpp::traits::input_parameter<U20>::type x20( args[20] ) ;
        typename Rcpp::traits::input_parameter<U21>::type x21( args[21] ) ;
        typename Rcpp::traits::input_parameter<U22>::type x22( args[22] ) ;
        typename Rcpp::traits::input_parameter<U23>::type x23( args[23] ) ;
        typename Rcpp::traits::input_parameter<U24>::type x24( args[24] ) ;
        typename Rcpp::traits::input_parameter<U25>::type x25( args[25] ) ;
        typename Rcpp::traits::input_parameter<U26>::type x26( args[26] ) ;
        typename Rcpp::traits::input_parameter<U27>::type x27( args[27] ) ;
        typename Rcpp::traits::input_parameter<U28>::type x28( args[28] ) ;
        typename Rcpp::traits::input_parameter<U29>::type x29( args[29] ) ;
        typename Rcpp::traits::input_parameter<U30>::type x30( args[30] ) ;
        typename Rcpp::traits::input_parameter<U31>::type x31( args[31] ) ;
        typename Rcpp::traits::input_parameter<U32>::type x32( args[32] ) ;
        typename Rcpp::traits::input_parameter<U33>::type x33( args[33] ) ;
        typename Rcpp::traits::input_parameter<U34>::type x34( args[34] ) ;
        typename Rcpp::traits::input_parameter<U35>::type x35( args[35] ) ;
        typename Rcpp::traits::input_parameter<U36>::type x36( args[36] ) ;
        typename Rcpp::traits::input_parameter<U37>::type x37( args[37] ) ;
        typename Rcpp::traits::input_parameter<U38>::type x38( args[38] ) ;
        typename Rcpp::traits::input_parameter<U39>::type x39( args[39] ) ;
        typename Rcpp::traits::input_parameter<U40>::type x40( args[40] ) ;
        typename Rcpp::traits::input_parameter<U41>::type x41( args[41] ) ;
        typename Rcpp::traits::input_parameter<U42>::type x42( args[42] ) ;
        typename Rcpp::traits::input_parameter<U43>::type x43( args[43] ) ;
        typename Rcpp::traits::input_parameter<U44>::type x44( args[44] ) ;
        typename Rcpp::traits::input_parameter<U45>::type x45( args[45] ) ;
        typename Rcpp::traits::input_parameter<U46>::type x46( args[46] ) ;
        typename Rcpp::traits::input_parameter<U47>::type x47( args[47] ) ;
        typename Rcpp::traits::input_parameter<U48>::type x48( args[48] ) ;
        typename Rcpp::traits::input_parameter<U49>::type x49( args[49] ) ;
        typename Rcpp::traits::input_parameter<U50>::type x50( args[50] ) ;
        typename Rcpp::traits::input_parameter<U51>::type x51( args[51] ) ;
        typename Rcpp::traits::input_parameter<U52>::type x52( args[52] ) ;
        typename Rcpp::traits::input_parameter<U53>::type x53( args[53] ) ;
        typename Rcpp::traits::input_parameter<U54>::type x54( args[54] ) ;
        typename Rcpp::traits::input_parameter<U55>::type x55( args[55] ) ;
        typename Rcpp::traits::input_parameter<U56>::type x56( args[56] ) ;
        typename Rcpp::traits::input_parameter<U57>::type x57( args[57] ) ;
        typename Rcpp::traits::input_parameter<U58>::type x58( args[58] ) ;
        typename Rcpp::traits::input_parameter<U59>::type x59( args[59] ) ;
        typename Rcpp::traits::input_parameter<U60>::type x60( args[60] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9, typename U10, typename U11, typename U12, typename U13, typename U14, typename U15, typename U16, typename U17, typename U18, typename U19, typename U20, typename U21, typename U22, typename U23, typename U24, typename U25, typename U26, typename U27, typename U28, typename U29, typename U30, typename U31, typename U32, typename U33, typename U34, typename U35, typename U36, typename U37, typename U38, typename U39, typename U40, typename U41, typename U42, typename U43, typename U44, typename U45, typename U46, typename U47, typename U48, typename U49, typename U50, typename U51, typename U52, typename U53, typename U54, typename U55, typename U56, typename U57, typename U58, typename U59, typename U60, typename U61>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        typename Rcpp::traits::input_parameter<U5>::type x5( args[5] ) ;
        typename Rcpp::traits::input_parameter<U6>::type x6( args[6] ) ;
        typename Rcpp::traits::input_parameter<U7>::type x7( args[7] ) ;
        typename Rcpp::traits::input_parameter<U8>::type x8( args[8] ) ;
        typename Rcpp::traits::input_parameter<U9>::type x9( args[9] ) ;
        typename Rcpp::traits::input_parameter<U10>::type x10( args[10] ) ;
        typename Rcpp::traits::input_parameter<U11>::type x11( args[11] ) ;
        typename Rcpp::traits::input_parameter<U12>::type x12( args[12] ) ;
        typename Rcpp::traits::input_parameter<U13>::type x13( args[13] ) ;
        typename Rcpp::traits::input_parameter<U14>::type x14( args[14] ) ;
        typename Rcpp::traits::input_parameter<U15>::type x15( args[15] ) ;
        typename Rcpp::traits::input_parameter<U16>::type x16( args[16] ) ;
        typename Rcpp::traits::input_parameter<U17>::type x17( args[17] ) ;
        typename Rcpp::traits::input_parameter<U18>::type x18( args[18] ) ;
        typename Rcpp::traits::input_parameter<U19>::type x19( args[19] ) ;
        typename Rcpp::traits::input_parameter<U20>::type x20( args[20] ) ;
        typename Rcpp::traits::input_parameter<U21>::type x21( args[21] ) ;
        typename Rcpp::traits::input_parameter<U22>::type x22( args[22] ) ;
        typename Rcpp::traits::input_parameter<U23>::type x23( args[23] ) ;
        typename Rcpp::traits::input_parameter<U24>::type x24( args[24] ) ;
        typename Rcpp::traits::input_parameter<U25>::type x25( args[25] ) ;
        typename Rcpp::traits::input_parameter<U26>::type x26( args[26] ) ;
        typename Rcpp::traits::input_parameter<U27>::type x27( args[27] ) ;
        typename Rcpp::traits::input_parameter<U28>::type x28( args[28] ) ;
        typename Rcpp::traits::input_parameter<U29>::type x29( args[29] ) ;
        typename Rcpp::traits::input_parameter<U30>::type x30( args[30] ) ;
        typename Rcpp::traits::input_parameter<U31>::type x31( args[31] ) ;
        typename Rcpp::traits::input_parameter<U32>::type x32( args[32] ) ;
        typename Rcpp::traits::input_parameter<U33>::type x33( args[33] ) ;
        typename Rcpp::traits::input_parameter<U34>::type x34( args[34] ) ;
        typename Rcpp::traits::input_parameter<U35>::type x35( args[35] ) ;
        typename Rcpp::traits::input_parameter<U36>::type x36( args[36] ) ;
        typename Rcpp::traits::input_parameter<U37>::type x37( args[37] ) ;
        typename Rcpp::traits::input_parameter<U38>::type x38( args[38] ) ;
        typename Rcpp::traits::input_parameter<U39>::type x39( args[39] ) ;
        typename Rcpp::traits::input_parameter<U40>::type x40( args[40] ) ;
        typename Rcpp::traits::input_parameter<U41>::type x41( args[41] ) ;
        typename Rcpp::traits::input_parameter<U42>::type x42( args[42] ) ;
        typename Rcpp::traits::input_parameter<U43>::type x43( args[43] ) ;
        typename Rcpp::traits::input_parameter<U44>::type x44( args[44] ) ;
        typename Rcpp::traits::input_parameter<U45>::type x45( args[45] ) ;
        typename Rcpp::traits::input_parameter<U46>::type x46( args[46] ) ;
        typename Rcpp::traits::input_parameter<U47>::type x47( args[47] ) ;
        typename Rcpp::traits::input_parameter<U48>::type x48( args[48] ) ;
        typename Rcpp::traits::input_parameter<U49>::type x49( args[49] ) ;
        typename Rcpp::traits::input_parameter<U50>::type x50( args[50] ) ;
        typename Rcpp::traits::input_parameter<U51>::type x51( args[51] ) ;
        typename Rcpp::traits::input_parameter<U52>::type x52( args[52] ) ;
        typename Rcpp::traits::input_parameter<U53>::type x53( args[53] ) ;
        typename Rcpp::traits::input_parameter<U54>::type x54( args[54] ) ;
        typename Rcpp::traits::input_parameter<U55>::type x55( args[55] ) ;
        typename Rcpp::traits::input_parameter<U56>::type x56( args[56] ) ;
        typename Rcpp::traits::input_parameter<U57>::type x57( args[57] ) ;
        typename Rcpp::traits::input_parameter<U58>::type x58( args[58] ) ;
        typename Rcpp::traits::input_parameter<U59>::type x59( args[59] ) ;
        typename Rcpp::traits::input_parameter<U60>::type x60( args[60] ) ;
        typename Rcpp::traits::input_parameter<U61>::type x61( args[61] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9, typename U10, typename U11, typename U12, typename U13, typename U14, typename U15, typename U16, typename U17, typename U18, typename U19, typename U20, typename U21, typename U22, typename U23, typename U24, typename U25, typename U26, typename U27, typename U28, typename U29, typename U30, typename U31, typename U32, typename U33, typename U34, typename U35, typename U36, typename U37, typename U38, typename U39, typename U40, typename U41, typename U42, typename U43, typename U44, typename U45, typename U46, typename U47, typename U48, typename U49, typename U50, typename U51, typename U52, typename U53, typename U54, typename U55, typename U56, typename U57, typename U58, typename U59, typename U60, typename U61, typename U62>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        typename Rcpp::traits::input_parameter<U5>::type x5( args[5] ) ;
        typename Rcpp::traits::input_parameter<U6>::type x6( args[6] ) ;
        typename Rcpp::traits::input_parameter<U7>::type x7( args[7] ) ;
        typename Rcpp::traits::input_parameter<U8>::type x8( args[8] ) ;
        typename Rcpp::traits::input_parameter<U9>::type x9( args[9] ) ;
        typename Rcpp::traits::input_parameter<U10>::type x10( args[10] ) ;
        typename Rcpp::traits::input_parameter<U11>::type x11( args[11] ) ;
        typename Rcpp::traits::input_parameter<U12>::type x12( args[12] ) ;
        typename Rcpp::traits::input_parameter<U13>::type x13( args[13] ) ;
        typename Rcpp::traits::input_parameter<U14>::type x14( args[14] ) ;
        typename Rcpp::traits::input_parameter<U15>::type x15( args[15] ) ;
        typename Rcpp::traits::input_parameter<U16>::type x16( args[16] ) ;
        typename Rcpp::traits::input_parameter<U17>::type x17( args[17] ) ;
        typename Rcpp::traits::input_parameter<U18>::type x18( args[18] ) ;
        typename Rcpp::traits::input_parameter<U19>::type x19( args[19] ) ;
        typename Rcpp::traits::input_parameter<U20>::type x20( args[20] ) ;
        typename Rcpp::traits::input_parameter<U21>::type x21( args[21] ) ;
        typename Rcpp::traits::input_parameter<U22>::type x22( args[22] ) ;
        typename Rcpp::traits::input_parameter<U23>::type x23( args[23] ) ;
        typename Rcpp::traits::input_parameter<U24>::type x24( args[24] ) ;
        typename Rcpp::traits::input_parameter<U25>::type x25( args[25] ) ;
        typename Rcpp::traits::input_parameter<U26>::type x26( args[26] ) ;
        typename Rcpp::traits::input_parameter<U27>::type x27( args[27] ) ;
        typename Rcpp::traits::input_parameter<U28>::type x28( args[28] ) ;
        typename Rcpp::traits::input_parameter<U29>::type x29( args[29] ) ;
        typename Rcpp::traits::input_parameter<U30>::type x30( args[30] ) ;
        typename Rcpp::traits::input_parameter<U31>::type x31( args[31] ) ;
        typename Rcpp::traits::input_parameter<U32>::type x32( args[32] ) ;
        typename Rcpp::traits::input_parameter<U33>::type x33( args[33] ) ;
        typename Rcpp::traits::input_parameter<U34>::type x34( args[34] ) ;
        typename Rcpp::traits::input_parameter<U35>::type x35( args[35] ) ;
        typename Rcpp::traits::input_parameter<U36>::type x36( args[36] ) ;
        typename Rcpp::traits::input_parameter<U37>::type x37( args[37] ) ;
        typename Rcpp::traits::input_parameter<U38>::type x38( args[38] ) ;
        typename Rcpp::traits::input_parameter<U39>::type x39( args[39] ) ;
        typename Rcpp::traits::input_parameter<U40>::type x40( args[40] ) ;
        typename Rcpp::traits::input_parameter<U41>::type x41( args[41] ) ;
        typename Rcpp::traits::input_parameter<U42>::type x42( args[42] ) ;
        typename Rcpp::traits::input_parameter<U43>::type x43( args[43] ) ;
        typename Rcpp::traits::input_parameter<U44>::type x44( args[44] ) ;
        typename Rcpp::traits::input_parameter<U45>::type x45( args[45] ) ;
        typename Rcpp::traits::input_parameter<U46>::type x46( args[46] ) ;
        typename Rcpp::traits::input_parameter<U47>::type x47( args[47] ) ;
        typename Rcpp::traits::input_parameter<U48>::type x48( args[48] ) ;
        typename Rcpp::traits::input_parameter<U49>::type x49( args[49] ) ;
        typename Rcpp::traits::input_parameter<U50>::type x50( args[50] ) ;
        typename Rcpp::traits::input_parameter<U51>::type x51( args[51] ) ;
        typename Rcpp::traits::input_parameter<U52>::type x52( args[52] ) ;
        typename Rcpp::traits::input_parameter<U53>::type x53( args[53] ) ;
        typename Rcpp::traits::input_parameter<U54>::type x54( args[54] ) ;
        typename Rcpp::traits::input_parameter<U55>::type x55( args[55] ) ;
        typename Rcpp::traits::input_parameter<U56>::type x56( args[56] ) ;
        typename Rcpp::traits::input_parameter<U57>::type x57( args[57] ) ;
        typename Rcpp::traits::input_parameter<U58>::type x58( args[58] ) ;
        typename Rcpp::traits::input_parameter<U59>::type x59( args[59] ) ;
        typename Rcpp::traits::input_parameter<U60>::type x60( args[60] ) ;
        typename Rcpp::traits::input_parameter<U61>::type x61( args[61] ) ;
        typename Rcpp::traits::input_parameter<U62>::type x62( args[62] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9, typename U10, typename U11, typename U12, typename U13, typename U14, typename U15, typename U16, typename U17, typename U18, typename U19, typename U20, typename U21, typename U22, typename U23, typename U24, typename U25, typename U26, typename U27, typename U28, typename U29, typename U30, typename U31, typename U32, typename U33, typename U34, typename U35, typename U36, typename U37, typename U38, typename U39, typename U40, typename U41, typename U42, typename U43, typename U44, typename U45, typename U46, typename U47, typename U48, typename U49, typename U50, typename U51, typename U52, typename U53, typename U54, typename U55, typename U56, typename U57, typename U58, typename U59, typename U60, typename U61, typename U62, typename U63>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        typename Rcpp::traits::input_parameter<U5>::type x5( args[5] ) ;
        typename Rcpp::traits::input_parameter<U6>::type x6( args[6] ) ;
        typename Rcpp::traits::input_parameter<U7>::type x7( args[7] ) ;
        typename Rcpp::traits::input_parameter<U8>::type x8( args[8] ) ;
        typename Rcpp::traits::input_parameter<U9>::type x9( args[9] ) ;
        typename Rcpp::traits::input_parameter<U10>::type x10( args[10] ) ;
        typename Rcpp::traits::input_parameter<U11>::type x11( args[11] ) ;
        typename Rcpp::traits::input_parameter<U12>::type x12( args[12] ) ;
        typename Rcpp::traits::input_parameter<U13>::type x13( args[13] ) ;
        typename Rcpp::traits::input_parameter<U14>::type x14( args[14] ) ;
        typename Rcpp::traits::input_parameter<U15>::type x15( args[15] ) ;
        typename Rcpp::traits::input_parameter<U16>::type x16( args[16] ) ;
        typename Rcpp::traits::input_parameter<U17>::type x17( args[17] ) ;
        typename Rcpp::traits::input_parameter<U18>::type x18( args[18] ) ;
        typename Rcpp::traits::input_parameter<U19>::type x19( args[19] ) ;
        typename Rcpp::traits::input_parameter<U20>::type x20( args[20] ) ;
        typename Rcpp::traits::input_parameter<U21>::type x21( args[21] ) ;
        typename Rcpp::traits::input_parameter<U22>::type x22( args[22] ) ;
        typename Rcpp::traits::input_parameter<U23>::type x23( args[23] ) ;
        typename Rcpp::traits::input_parameter<U24>::type x24( args[24] ) ;
        typename Rcpp::traits::input_parameter<U25>::type x25( args[25] ) ;
        typename Rcpp::traits::input_parameter<U26>::type x26( args[26] ) ;
        typename Rcpp::traits::input_parameter<U27>::type x27( args[27] ) ;
        typename Rcpp::traits::input_parameter<U28>::type x28( args[28] ) ;
        typename Rcpp::traits::input_parameter<U29>::type x29( args[29] ) ;
        typename Rcpp::traits::input_parameter<U30>::type x30( args[30] ) ;
        typename Rcpp::traits::input_parameter<U31>::type x31( args[31] ) ;
        typename Rcpp::traits::input_parameter<U32>::type x32( args[32] ) ;
        typename Rcpp::traits::input_parameter<U33>::type x33( args[33] ) ;
        typename Rcpp::traits::input_parameter<U34>::type x34( args[34] ) ;
        typename Rcpp::traits::input_parameter<U35>::type x35( args[35] ) ;
        typename Rcpp::traits::input_parameter<U36>::type x36( args[36] ) ;
        typename Rcpp::traits::input_parameter<U37>::type x37( args[37] ) ;
        typename Rcpp::traits::input_parameter<U38>::type x38( args[38] ) ;
        typename Rcpp::traits::input_parameter<U39>::type x39( args[39] ) ;
        typename Rcpp::traits::input_parameter<U40>::type x40( args[40] ) ;
        typename Rcpp::traits::input_parameter<U41>::type x41( args[41] ) ;
        typename Rcpp::traits::input_parameter<U42>::type x42( args[42] ) ;
        typename Rcpp::traits::input_parameter<U43>::type x43( args[43] ) ;
        typename Rcpp::traits::input_parameter<U44>::type x44( args[44] ) ;
        typename Rcpp::traits::input_parameter<U45>::type x45( args[45] ) ;
        typename Rcpp::traits::input_parameter<U46>::type x46( args[46] ) ;
        typename Rcpp::traits::input_parameter<U47>::type x47( args[47] ) ;
        typename Rcpp::traits::input_parameter<U48>::type x48( args[48] ) ;
        typename Rcpp::traits::input_parameter<U49>::type x49( args[49] ) ;
        typename Rcpp::traits::input_parameter<U50>::type x50( args[50] ) ;
        typename Rcpp::traits::input_parameter<U51>::type x51( args[51] ) ;
        typename Rcpp::traits::input_parameter<U52>::type x52( args[52] ) ;
        typename Rcpp::traits::input_parameter<U53>::type x53( args[53] ) ;
        typename Rcpp::traits::input_parameter<U54>::type x54( args[54] ) ;
        typename Rcpp::traits::input_parameter<U55>::type x55( args[55] ) ;
        typename Rcpp::traits::input_parameter<U56>::type x56( args[56] ) ;
        typename Rcpp::traits::input_parameter<U57>::type x57( args[57] ) ;
        typename Rcpp::traits::input_parameter<U58>::type x58( args[58] ) ;
        typename Rcpp::traits::input_parameter<U59>::type x59( args[59] ) ;
        typename Rcpp::traits::input_parameter<U60>::type x60( args[60] ) ;
        typename Rcpp::traits::input_parameter<U61>::type x61( args[61] ) ;
        typename Rcpp::traits::input_parameter<U62>::type x62( args[62] ) ;
        typename Rcpp::traits::input_parameter<U63>::type x63( args[63] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9, typename U10, typename U11, typename U12, typename U13, typename U14, typename U15, typename U16, typename U17, typename U18, typename U19, typename U20, typename U21, typename U22, typename U23, typename U24, typename U25, typename U26, typename U27, typename U28, typename U29, typename U30, typename U31, typename U32, typename U33, typename U34, typename U35, typename U36, typename U37, typename U38, typename U39, typename U40, typename U41, typename U42, typename U43, typename U44, typename U45, typename U46, typename U47, typename U48, typename U49, typename U50, typename U51, typename U52, typename U53, typename U54, typename U55, typename U56, typename U57, typename U58, typename U59, typename U60, typename U61, typename U62, typename U63, typename U64>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        typename Rcpp::traits::input_parameter<U5>::type x5( args[5] ) ;
        typename Rcpp::traits::input_parameter<U6>::type x6( args[6] ) ;
        typename Rcpp::traits::input_parameter<U7>::type x7( args[7] ) ;
        typename Rcpp::traits::input_parameter<U8>::type x8( args[8] ) ;
        typename Rcpp::traits::input_parameter<U9>::type x9( args[9] ) ;
        typename Rcpp::traits::input_parameter<U10>::type x10( args[10] ) ;
        typename Rcpp::traits::input_parameter<U11>::type x11( args[11] ) ;
        typename Rcpp::traits::input_parameter<U12>::type x12( args[12] ) ;
        typename Rcpp::traits::input_parameter<U13>::type x13( args[13] ) ;
        typename Rcpp::traits::input_parameter<U14>::type x14( args[14] ) ;
        typename Rcpp::traits::input_parameter<U15>::type x15( args[15] ) ;
        typename Rcpp::traits::input_parameter<U16>::type x16( args[16] ) ;
        typename Rcpp::traits::input_parameter<U17>::type x17( args[17] ) ;
        typename Rcpp::traits::input_parameter<U18>::type x18( args[18] ) ;
        typename Rcpp::traits::input_parameter<U19>::type x19( args[19] ) ;
        typename Rcpp::traits::input_parameter<U20>::type x20( args[20] ) ;
        typename Rcpp::traits::input_parameter<U21>::type x21( args[21] ) ;
        typename Rcpp::traits::input_parameter<U22>::type x22( args[22] ) ;
        typename Rcpp::traits::input_parameter<U23>::type x23( args[23] ) ;
        typename Rcpp::traits::input_parameter<U24>::type x24( args[24] ) ;
        typename Rcpp::traits::input_parameter<U25>::type x25( args[25] ) ;
        typename Rcpp::traits::input_parameter<U26>::type x26( args[26] ) ;
        typename Rcpp::traits::input_parameter<U27>::type x27( args[27] ) ;
        typename Rcpp::traits::input_parameter<U28>::type x28( args[28] ) ;
        typename Rcpp::traits::input_parameter<U29>::type x29( args[29] ) ;
        typename Rcpp::traits::input_parameter<U30>::type x30( args[30] ) ;
        typename Rcpp::traits::input_parameter<U31>::type x31( args[31] ) ;
        typename Rcpp::traits::input_parameter<U32>::type x32( args[32] ) ;
        typename Rcpp::traits::input_parameter<U33>::type x33( args[33] ) ;
        typename Rcpp::traits::input_parameter<U34>::type x34( args[34] ) ;
        typename Rcpp::traits::input_parameter<U35>::type x35( args[35] ) ;
        typename Rcpp::traits::input_parameter<U36>::type x36( args[36] ) ;
        typename Rcpp::traits::input_parameter<U37>::type x37( args[37] ) ;
        typename Rcpp::traits::input_parameter<U38>::type x38( args[38] ) ;
        typename Rcpp::traits::input_parameter<U39>::type x39( args[39] ) ;
        typename Rcpp::traits::input_parameter<U40>::type x40( args[40] ) ;
        typename Rcpp::traits::input_parameter<U41>::type x41( args[41] ) ;
        typename Rcpp::traits::input_parameter<U42>::type x42( args[42] ) ;
        typename Rcpp::traits::input_parameter<U43>::type x43( args[43] ) ;
        typename Rcpp::traits::input_parameter<U44>::type x44( args[44] ) ;
        typename Rcpp::traits::input_parameter<U45>::type x45( args[45] ) ;
        typename Rcpp::traits::input_parameter<U46>::type x46( args[46] ) ;
        typename Rcpp::traits::input_parameter<U47>::type x47( args[47] ) ;
        typename Rcpp::traits::input_parameter<U48>::type x48( args[48] ) ;
        typename Rcpp::traits::input_parameter<U49>::type x49( args[49] ) ;
        typename Rcpp::traits::input_parameter<U50>::type x50( args[50] ) ;
        typename Rcpp::traits::input_parameter<U51>::type x51( args[51] ) ;
        typename Rcpp::traits::input_parameter<U52>::type x52( args[52] ) ;
        typename Rcpp::traits::input_parameter<U53>::type x53( args[53] ) ;
        typename Rcpp::traits::input_parameter<U54>::type x54( args[54] ) ;
        typename Rcpp::traits::input_parameter<U55>::type x55( args[55] ) ;
        typename Rcpp::traits::input_parameter<U56>::type x56( args[56] ) ;
        typename Rcpp::traits::input_parameter<U57>::type x57( args[57] ) ;
        typename Rcpp::traits::input_parameter<U58>::type x58( args[58] ) ;
        typename Rcpp::traits::input_parameter<U59>::type x59( args[59] ) ;
        typename Rcpp::traits::input_parameter<U60>::type x60( args[60] ) ;
        typename Rcpp::traits::input_parameter<U61>::type x61( args[61] ) ;
        typename Rcpp::traits::input_parameter<U62>::type x62( args[62] ) ;
        typename Rcpp::traits::input_parameter<U63>::type x63( args[63] ) ;
        typename Rcpp::traits::input_parameter<U64>::type x64( args[64] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64)) ;
    }
    

    template <typename OUT, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9, typename U10, typename U11, typename U12, typename U13, typename U14, typename U15, typename U16, typename U17, typename U18, typename U19, typename U20, typename U21, typename U22, typename U23, typename U24, typename U25, typename U26, typename U27, typename U28, typename U29, typename U30, typename U31, typename U32, typename U33, typename U34, typename U35, typename U36, typename U37, typename U38, typename U39, typename U40, typename U41, typename U42, typename U43, typename U44, typename U45, typename U46, typename U47, typename U48, typename U49, typename U50, typename U51, typename U52, typename U53, typename U54, typename U55, typename U56, typename U57, typename U58, typename U59, typename U60, typename U61, typename U62, typename U63, typename U64, typename U65>
    SEXP function_invoke( OUT (*ptr_fun)(), SEXP* args ){ 
        typename Rcpp::traits::input_parameter<U1>::type x1( args[1] ) ;
        typename Rcpp::traits::input_parameter<U2>::type x2( args[2] ) ;
        typename Rcpp::traits::input_parameter<U3>::type x3( args[3] ) ;
        typename Rcpp::traits::input_parameter<U4>::type x4( args[4] ) ;
        typename Rcpp::traits::input_parameter<U5>::type x5( args[5] ) ;
        typename Rcpp::traits::input_parameter<U6>::type x6( args[6] ) ;
        typename Rcpp::traits::input_parameter<U7>::type x7( args[7] ) ;
        typename Rcpp::traits::input_parameter<U8>::type x8( args[8] ) ;
        typename Rcpp::traits::input_parameter<U9>::type x9( args[9] ) ;
        typename Rcpp::traits::input_parameter<U10>::type x10( args[10] ) ;
        typename Rcpp::traits::input_parameter<U11>::type x11( args[11] ) ;
        typename Rcpp::traits::input_parameter<U12>::type x12( args[12] ) ;
        typename Rcpp::traits::input_parameter<U13>::type x13( args[13] ) ;
        typename Rcpp::traits::input_parameter<U14>::type x14( args[14] ) ;
        typename Rcpp::traits::input_parameter<U15>::type x15( args[15] ) ;
        typename Rcpp::traits::input_parameter<U16>::type x16( args[16] ) ;
        typename Rcpp::traits::input_parameter<U17>::type x17( args[17] ) ;
        typename Rcpp::traits::input_parameter<U18>::type x18( args[18] ) ;
        typename Rcpp::traits::input_parameter<U19>::type x19( args[19] ) ;
        typename Rcpp::traits::input_parameter<U20>::type x20( args[20] ) ;
        typename Rcpp::traits::input_parameter<U21>::type x21( args[21] ) ;
        typename Rcpp::traits::input_parameter<U22>::type x22( args[22] ) ;
        typename Rcpp::traits::input_parameter<U23>::type x23( args[23] ) ;
        typename Rcpp::traits::input_parameter<U24>::type x24( args[24] ) ;
        typename Rcpp::traits::input_parameter<U25>::type x25( args[25] ) ;
        typename Rcpp::traits::input_parameter<U26>::type x26( args[26] ) ;
        typename Rcpp::traits::input_parameter<U27>::type x27( args[27] ) ;
        typename Rcpp::traits::input_parameter<U28>::type x28( args[28] ) ;
        typename Rcpp::traits::input_parameter<U29>::type x29( args[29] ) ;
        typename Rcpp::traits::input_parameter<U30>::type x30( args[30] ) ;
        typename Rcpp::traits::input_parameter<U31>::type x31( args[31] ) ;
        typename Rcpp::traits::input_parameter<U32>::type x32( args[32] ) ;
        typename Rcpp::traits::input_parameter<U33>::type x33( args[33] ) ;
        typename Rcpp::traits::input_parameter<U34>::type x34( args[34] ) ;
        typename Rcpp::traits::input_parameter<U35>::type x35( args[35] ) ;
        typename Rcpp::traits::input_parameter<U36>::type x36( args[36] ) ;
        typename Rcpp::traits::input_parameter<U37>::type x37( args[37] ) ;
        typename Rcpp::traits::input_parameter<U38>::type x38( args[38] ) ;
        typename Rcpp::traits::input_parameter<U39>::type x39( args[39] ) ;
        typename Rcpp::traits::input_parameter<U40>::type x40( args[40] ) ;
        typename Rcpp::traits::input_parameter<U41>::type x41( args[41] ) ;
        typename Rcpp::traits::input_parameter<U42>::type x42( args[42] ) ;
        typename Rcpp::traits::input_parameter<U43>::type x43( args[43] ) ;
        typename Rcpp::traits::input_parameter<U44>::type x44( args[44] ) ;
        typename Rcpp::traits::input_parameter<U45>::type x45( args[45] ) ;
        typename Rcpp::traits::input_parameter<U46>::type x46( args[46] ) ;
        typename Rcpp::traits::input_parameter<U47>::type x47( args[47] ) ;
        typename Rcpp::traits::input_parameter<U48>::type x48( args[48] ) ;
        typename Rcpp::traits::input_parameter<U49>::type x49( args[49] ) ;
        typename Rcpp::traits::input_parameter<U50>::type x50( args[50] ) ;
        typename Rcpp::traits::input_parameter<U51>::type x51( args[51] ) ;
        typename Rcpp::traits::input_parameter<U52>::type x52( args[52] ) ;
        typename Rcpp::traits::input_parameter<U53>::type x53( args[53] ) ;
        typename Rcpp::traits::input_parameter<U54>::type x54( args[54] ) ;
        typename Rcpp::traits::input_parameter<U55>::type x55( args[55] ) ;
        typename Rcpp::traits::input_parameter<U56>::type x56( args[56] ) ;
        typename Rcpp::traits::input_parameter<U57>::type x57( args[57] ) ;
        typename Rcpp::traits::input_parameter<U58>::type x58( args[58] ) ;
        typename Rcpp::traits::input_parameter<U59>::type x59( args[59] ) ;
        typename Rcpp::traits::input_parameter<U60>::type x60( args[60] ) ;
        typename Rcpp::traits::input_parameter<U61>::type x61( args[61] ) ;
        typename Rcpp::traits::input_parameter<U62>::type x62( args[62] ) ;
        typename Rcpp::traits::input_parameter<U63>::type x63( args[63] ) ;
        typename Rcpp::traits::input_parameter<U64>::type x64( args[64] ) ;
        typename Rcpp::traits::input_parameter<U65>::type x65( args[65] ) ;
        return wrap(ptr_fun(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54, x55, x56, x57, x58, x59, x60, x61, x62, x63, x64, x65)) ;
    }
    

#endif
