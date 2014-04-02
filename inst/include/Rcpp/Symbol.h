#ifndef Rcpp_Symbol_h
#define Rcpp_Symbol_h

namespace Rcpp{ 

    template < template <class> class StoragePolicy >
    class Symbol_Impl : 
        public StoragePolicy<Symbol_Impl<StoragePolicy>>, 
        public RObjectMethods<Symbol_Impl<StoragePolicy>>
    {
    public:
    
        RCPP_GENERATE_CTOR_ASSIGN(Symbol_Impl) 
        
        /**
         * wraps the SEXP into a Symbol object. 
         * 
         * @param m_sexp Accepted SEXP types are SYMSXP, CHARSXP and STRSXP
         * in the last case, the first element of the character vector 
         * is silently used
         */
        Symbol_Impl(SEXP x){
            if( x != R_NilValue ){
                int type = TYPEOF(x) ;
                switch( type ){
                case SYMSXP:
                    Storage::set__( x ) ;
                    break; /* nothing to do */
                case CHARSXP: {
                    SEXP charSym = Rf_install(CHAR(x));     
                    Storage::set__( charSym ) ;
                    break ;
                }
                case STRSXP: {
                    /* FIXME: check that there is at least one element */
                    SEXP charSym = Rf_install( CHAR(STRING_ELT(x, 0 )) ); 
                    Storage::set__( charSym );
                    break ;
                }
                default:
                    throw not_compatible("cannot convert to symbol (SYMSXP)") ;
                }
            } 
        }
    
        /**
         *
         */
        Symbol_Impl(const std::string& symbol){
            Storage::set__(Rf_install(symbol.c_str()));
        }
    
        inline const char* c_str() const { 
            return CHAR(PRINTNAME(Storage::get__())) ;
        }
        
        inline bool operator==(const char* other) const { 
            return ! strcmp(other, c_str() );
        }
        
    };

} // namespace Rcpp

#endif
