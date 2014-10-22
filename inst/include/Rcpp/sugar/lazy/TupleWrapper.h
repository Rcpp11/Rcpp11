#ifndef Rcpp__sugar_lazy_TupleWrapper_h
#define Rcpp__sugar_lazy_TupleWrapper_h

namespace Rcpp{
    
    template <typename... Args>
    class TupleWrapper_NoNames : public LazyVector<VECSXP, TupleWrapper_NoNames<Args...>> {
    public:
        using Tuple = std::tuple<Args...> ;
    
        TupleWrapper_NoNames( const Tuple& data_ ) : data(data_) {}
        
        inline R_xlen_t size() const {
            return sizeof...(Args) ;    
        }
        
        template <typename Target>
        inline void apply( Target& target ) const {
            auto it = target.begin() ;
            set_value<0, typename Target::iterator, Target >( it, 
                typename std::integral_constant< bool, (sizeof...(Args) > 0) >::type()
            ) ;            
        }
        
    private:
        
        const Tuple& data ;
        
        template <int INDEX, typename Iterator, typename Target>
        inline void set_value( Iterator& it, std::true_type ) const {
            *it = wrap( std::get<INDEX>(data) ) ; ++it ;
            
            set_value<INDEX+1, Iterator, Target>( it, 
                typename std::integral_constant<bool, (INDEX+1 < sizeof...(Args)) >::type()
            ) ;
        }
        
        template <int INDEX, typename Iterator, typename Target>
        inline void set_value( Iterator& it, std::false_type ) const {}
            
    } ;  
    
    template <typename... Args>
    class TupleWrapper_WithNames : public LazyVector<VECSXP, TupleWrapper_WithNames<Args...>>{
        using Tuple = std::tuple<Args...> ;
        
        public:
            TupleWrapper_WithNames( const Tuple& data_ ) : data(data_) {}
            
            inline R_xlen_t size() const {
                return sizeof...(Args) ;    
            }
            
            template <typename Target>
            inline void apply( Target& target ) const {
                auto it = target.begin() ;
                Shield<SEXP> names_ = Rf_allocVector( STRSXP, sizeof...(Args) ) ;
                set_value<0, typename Target::iterator, Target >( names_, it, 
                    typename std::integral_constant< bool, (sizeof...(Args) > 0)  >::type() 
                ) ;    
                names(target) = names_ ;
            }
            
        private:
            
            template <int INDEX, typename Iterator, typename Target>
            inline void set_value( Shield<SEXP>& names_, Iterator& it, std::true_type ) const {
                typedef typename traits::r_vector_element_converter<Target::r_type::value>::type converter_type ;
        
                auto val = std::get<INDEX>(data) ;
                *it = converter_type::get(val) ; ++it ;
                SET_STRING_ELT(names_, INDEX, Rf_mkChar( internal::get_object_name(val) ) );
                
                set_value<INDEX+1,Iterator, Target>( names_, it, 
                    typename std::integral_constant<bool, (INDEX+1 < sizeof...(Args)) >::type() 
                    ) ;
            }
            
            template <int INDEX, typename Iterator, typename Target>
            inline void set_value( Shield<SEXP>& names_, Iterator& it, std::false_type ) const {}
            
            Tuple data ;
            
    } ;  
    
    template <typename... Args>
    struct tuple_wrapper_type {
        using type = typename std::conditional<
            traits::any_named< typename std::decay<Args>::type ...>::type::value, 
            TupleWrapper_WithNames<Args...>,
            TupleWrapper_NoNames<Args...>
        >::type ;
    } ;
    
}
#endif
