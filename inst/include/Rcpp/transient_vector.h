#ifndef Rcpp_transient_vector_h
#define Rcpp_transient_vector_h

namespace Rcpp{

    template <typename T>
    class r_transient_allocator {
    public:
        typedef T value_type ;
        typedef T* pointer ;
        typedef T& reference ;
        typedef const T* const_pointer ;
        typedef const T& const_reference ;
        typedef size_t size_type ;
        typedef ptrdiff_t difference_type ;
        template <class U> struct rebind { 
            typedef r_transient_allocator<U> other; 
        };
        
        inline pointer address ( reference x ) const noexcept{
            return &x ;
        }
        inline const_pointer address ( const_reference x ) const noexcept{
            return &x ;
        }
        
        inline pointer allocate(size_type n, const void* hint = 0 ){
            return reinterpret_cast<pointer>( R_alloc(n, sizeof(T)) ) ;            
        }
        
        inline void deallocate(pointer, size_type){}
        
        inline size_type max_size() const {
            return R_LEN_T_MAX / sizeof(T) ;        
        }
        
        template <class U, class... Args>
        void construct (U* p, Args&&... args){
            new ((void*)p) U (std::forward<Args>(args)...);     
        }
        
        template <class U>
        void destroy (U* p){
            p->~U() ;    
        }
    } ;
    
    template <typename T>
    using r_transient_vector = typename std::vector<T, r_transient_allocator<T> > ;
    
}

#endif
