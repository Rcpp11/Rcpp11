#ifndef Rcpp_Internal_Interrupt_h
#define Rcpp_Internal_Interrupt_h

#include <Rinterface.h>

namespace Rcpp {

    // Internal functions used in the implementation of checkUserInterrupt
    namespace internal {

        // Sentinel class for communicating interrupts to the top-level END_RCPP macro
        class InterruptedException {};

        // Sentinel object of class "interrupted-error" which is used for
        // communicating interrupts across module boundaries without an
        // exception (which would crash on windows). This is identical to
        // the existing "try-error" sentinel object used for communicating
        // errors accross module boundaries.
        inline SEXP interruptedError() {
            Rcpp::Shield<SEXP> interruptedError( Rf_mkString("") );
            Rf_setAttrib( interruptedError, R_ClassSymbol, Rf_mkString("interrupted-error") ) ;
            return interruptedError;
        }

    } // namespace internal

    // Helper function to check for interrupts. This is invoked within
    // R_ToplevelExec so it doesn't longjmp
    namespace {

        inline void checkInterruptFn(void *dummy) {
            R_CheckUserInterrupt();
        }

    } // anonymous namespace

    // Check for interrupts and throw the sentinel exception if one is pending
    inline void checkUserInterrupt() {
        if (R_ToplevelExec(checkInterruptFn, NULL) == FALSE)
            throw internal::InterruptedException();
    }

} // namespace Rcpp

#endif
