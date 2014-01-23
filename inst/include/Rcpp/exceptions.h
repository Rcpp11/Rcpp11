#ifndef Rcpp__exceptions__h
#define Rcpp__exceptions__h

#define R_NO_REMAP
#include <Rinternals.h>
#include <sstream>

#define GET_STACKTRACE() stack_trace( __FILE__, __LINE__ )

namespace Rcpp{

class exception : public std::exception {
public:
    explicit exception(const char* message_) : message(message_){}
    exception(const char* message_, const char* file, int line ): message(message_){
        rcpp_set_stack_trace( stack_trace(file,line) ) ;
    }
    virtual ~exception() noexcept {}
    virtual const char* what() const noexcept { return message.c_str() ; }
private:
    std::string message ;
} ;

// simple helper
static std::string toString(const int i) {
    std::ostringstream ostr;
    ostr << i;
    return ostr.str();
}

class no_such_env : public std::exception{
public:
    no_such_env( const std::string& name ) throw() : message( std::string("no such environment: '") + name + "'" ){}
    no_such_env( int pos ) throw() : message( "no environment in given position '" + toString(pos) + "'") {}
    virtual ~no_such_env() throw(){}
    virtual const char* what() const throw(){ return message.c_str() ; }
private:
    std::string message ;
} ;

class file_io_error : public std::exception {
public:
    file_io_error(const std::string& file_) throw() : message( std::string("file io error: '") + file_ + "'" ), file(file_) {}
    file_io_error(int code, const std::string& file_) throw() : message( "file io error " + toString(code) + ": '" + file_ + "'"), file(file_) {}
    file_io_error(const std::string& msg, const std::string& file_) throw() : message( msg + ": '" + file_ + "'"), file(file_) {}
    virtual ~file_io_error() throw(){}
    virtual const char* what() const throw(){ return message.c_str() ; }
    std::string filePath() const throw(){ return file ; }
private:
    std::string message ;
    std::string file;
} ;

class file_not_found : public file_io_error {
public:
    file_not_found(const std::string& file) throw() : file_io_error("file not found", file) {}
};

class file_exists : public file_io_error {
public:
    file_exists(const std::string& file) throw() : file_io_error("file already exists", file) {}
};

#define RCPP_EXCEPTION_CLASS(__CLASS__,__WHAT__)                               \
class __CLASS__ : public std::exception{                                       \
public:                                                                        \
	__CLASS__( const std::string& msg ) noexcept : message( __WHAT__ ){}  \
	virtual ~__CLASS__() noexcept{}                                            \
	virtual const char* what() const noexcept { return message.c_str() ; }     \
private:                                                                       \
	std::string message ;                                                      \
} ;

#define RCPP_SIMPLE_EXCEPTION_CLASS(__CLASS__,__MESSAGE__)                     \
class __CLASS__ : public std::exception{                                       \
public:                                                                        \
	__CLASS__() noexcept {}                                                    \
	virtual ~__CLASS__() noexcept {}                                           \
	virtual const char* what() const noexcept{ return __MESSAGE__ ; }          \
} ;

RCPP_SIMPLE_EXCEPTION_CLASS(not_a_matrix, "not a matrix")
RCPP_SIMPLE_EXCEPTION_CLASS(index_out_of_bounds, "index out of bounds")
RCPP_SIMPLE_EXCEPTION_CLASS(parse_error, "parse error")
RCPP_SIMPLE_EXCEPTION_CLASS(not_s4, "not an S4 object")
RCPP_SIMPLE_EXCEPTION_CLASS(not_reference, "not an S4 object of a reference class")
RCPP_SIMPLE_EXCEPTION_CLASS(not_initialized, "C++ object not initialized (missing default constructor?)")
RCPP_SIMPLE_EXCEPTION_CLASS(no_such_slot, "no such slot")
RCPP_SIMPLE_EXCEPTION_CLASS(no_such_field, "no such field")
RCPP_SIMPLE_EXCEPTION_CLASS(not_a_closure, "not a closure")
RCPP_SIMPLE_EXCEPTION_CLASS(no_such_function, "no such function")
RCPP_SIMPLE_EXCEPTION_CLASS(unevaluated_promise, "promise not yet evaluated")

RCPP_EXCEPTION_CLASS(not_compatible, msg )
RCPP_EXCEPTION_CLASS(S4_creation_error, std::string("error creating object of S4 class : ") + msg )
RCPP_EXCEPTION_CLASS(reference_creation_error, std::string("error creating object of reference class : ") + msg )
RCPP_EXCEPTION_CLASS(no_such_binding, std::string("no such binding : '") + msg + "'" )
RCPP_EXCEPTION_CLASS(binding_not_found, std::string("binding not found: '") + msg + "'" )
RCPP_EXCEPTION_CLASS(binding_is_locked, std::string("binding is locked: '") + msg + "'" )
RCPP_EXCEPTION_CLASS(no_such_namespace, std::string("no such namespace: '") + msg + "'" )
RCPP_EXCEPTION_CLASS(function_not_exported, std::string("function not exported: ") + msg)
RCPP_EXCEPTION_CLASS(eval_error, msg )

#undef RCPP_EXCEPTION_CLASS
#undef RCPP_SIMPLE_EXCEPTION_CLASS
} // namespace Rcpp

#define DEMANGLE(__TYPE__) Rcpp::Demangler<__TYPE__>::get().c_str()

#include <Rcpp/utils/tinyformat.h>

namespace Rcpp {
  template <typename... Args>
  inline void stop(const char* fmt, Args... args) {
    if (sizeof...(args)) {
      throw Rcpp::exception( tfm::format(fmt, args...).c_str() );
    } else {
      throw Rcpp::exception(fmt);
    }
  }
} // namespace Rcpp

#endif
