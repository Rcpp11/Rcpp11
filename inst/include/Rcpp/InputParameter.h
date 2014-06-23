#ifndef Rcpp__InputParameter__h
#define Rcpp__InputParameter__h

namespace Rcpp { 
    
    template <typename T>
    class InputParameter {
    public:
        InputParameter(SEXP x_) : 
            x(x_){}
        
        inline operator T() { 
            return as<T>(x) ; 
        }
        
        SEXP x ;
    } ;
    
    template <typename T>
    class InputParameter<const T> {
    public:
        InputParameter(SEXP x_) : 
            x(x_){}
        
        inline operator const T() { 
            return as<T>(x) ; 
        }
        
        SEXP x ;
    } ;
    
    template <typename T>
    class InputParameter<T&> {
    public:
        InputParameter(SEXP x) : 
            obj( as<T>(x) ) {}
        
        inline operator T&() { 
            return obj ; 
        }
        
        T obj ; 
    } ;

    template <typename T>
    class InputParameter<const T&> {
    public:
        InputParameter(SEXP x) : 
            obj( as<T>(x) ){}
        
        inline operator const T&() { 
            return obj ; 
        }
        
    private:
        T obj ;
    } ;
    
    namespace traits{
        template <typename T>
        struct input_parameter {
            typedef typename Rcpp::InputParameter<T> type ;
        } ;
    }

}

#endif
