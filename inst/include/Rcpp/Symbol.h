#ifndef Rcpp_Symbol_h
#define Rcpp_Symbol_h

namespace Rcpp{ 

    template <typename Storage>
    class Symbol_Impl {
        RCPP_API_IMPL(Symbol_Impl) 
        
        inline void set(SEXP x){
            int type = TYPEOF(x) ;
            switch( type ){
            case SYMSXP:
                data = x ;
                break; /* nothing to do */
            case CHARSXP: {
                data = Rf_install(CHAR(x));     
                break ;
            }
            case STRSXP: {
                /* FIXME: check that there is at least one element */
                data = Rf_install( CHAR(STRING_ELT(x, 0 )) ); 
                break ;
            }
            default:
                stop("cannot convert to symbol (SYMSXP)") ;
            }       
        }
        
        Symbol_Impl(const std::string& symbol) :    
            data(Rf_install(symbol.c_str())) {}
    
        Symbol_Impl(const char* symbol) :    
            data(Rf_install(symbol)) {}
    
        inline const char* c_str() const { 
            return CHAR(PRINTNAME(data)) ;
        }
        
        inline bool operator==(const char* other) const { 
            return ! strcmp(other, c_str() );
        }
        
    };

} // namespace Rcpp

#endif
