#ifndef RCPP__HASH__SELF_HASH_H
#define RCPP__HASH__SELF_HASH_H

namespace Rcpp{
namespace sugar{ 


    template <int RTYPE>
    class SelfHash {
    public:
        typedef typename traits::storage_type<RTYPE>::type STORAGE ;
        typedef Vector<RTYPE> VECTOR ;
              
        SelfHash( SEXP table ) : n(Rf_length(table)), m(2), k(1), 
            src( (STORAGE*)dataptr(table) ), data(), indices(), size_(0) 
        {
            int desired = n*2 ;
            while( m < desired ){ m *= 2 ; k++ ; }
            data.resize( m ) ;
            indices.resize( m ) ;
        }
       
        inline IntegerVector fill_and_self_match(){
            IntegerVector result = no_init(n) ;
            int* res = INTEGER(result) ;
            for( int i=0; i<n; i++) res[i] = add_value_get_index(i) ;
            return result ;    
        }                       
    
        inline int size() const {
            return size_ ;
        }
        
        int n, m, k ;
        STORAGE* src ;
        std::vector<int> data ;
        std::vector<int> indices ;
        int size_ ;
        
        int add_value_get_index(int i){
            STORAGE val = src[i++] ;
            int addr = get_addr(val) ;
            while (data[addr] && src[data[addr] - 1] != val) {
              addr++;
              if (addr == m) addr = 0;
            }
            if (!data[addr]) {
                data[addr] = i ;
                indices[addr] = ++size_ ;
            }
            return indices[addr] ;
        }
        
        /* NOTE: we are returning a 1-based index ! */
        int get_index(STORAGE value) const {
            int addr = get_addr(value) ;
            while (data[addr]) {
              if (src[data[addr] - 1] == value)
                return data[addr];
              addr++;
              if (addr == m) addr = 0;
            }
            return NA_INTEGER;
        }
        
        // defined below
        int get_addr(STORAGE value) const ;
    } ;
        
    template <>
    inline int SelfHash<INTSXP>::get_addr(int value) const {
        return RCPP_HASH(value) ;
    }
    template <>
    inline int SelfHash<REALSXP>::get_addr(double val) const {
      int addr;
      union dint_u {
          double d;
          unsigned int u[2];
        };
      union dint_u val_u;
      /* double is a bit tricky - we nave to normalize 0.0, NA and NaN */
      if (val == 0.0) val = 0.0;
      if (R_IsNA(val)) val = NA_REAL;
      else if (R_IsNaN(val)) val = R_NaN;
      val_u.d = val;            
      addr = RCPP_HASH(val_u.u[0] + val_u.u[1]);
      return addr ;
    }
    
    template <>
    inline int SelfHash<STRSXP>::get_addr(SEXP value) const {
        intptr_t val = (intptr_t) value;
        int addr;
        #if (defined _LP64) || (defined __LP64__) || (defined WIN64)
          addr = RCPP_HASH((val & 0xffffffff) ^ (val >> 32));
        #else
          addr = RCPP_HASH(val);
        #endif
        return addr ;
    }

} // sugar
} // Rcpp

#endif
