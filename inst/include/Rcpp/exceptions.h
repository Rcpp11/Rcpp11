#ifndef Rcpp__exceptions__h
#define Rcpp__exceptions__h

#define R_NO_REMAP
#include <Rinternals.h>
#include <sstream>

// for backtraces
#if defined(__GCC__) || defined(__clang__)
#include <execinfo.h>
#endif

#define GET_STACKTRACE() stack_trace( __FILE__, __LINE__ )

namespace Rcpp{

class exception : public std::exception {
public:
    explicit exception(const char* message_) : message(message_) {
      add_backtrace_information(message);
    }
    explicit exception(const std::string& message_) : message(message_) {
      add_backtrace_information(message);
    }
    exception(const char* message_, const char* file, int line ): message(message_){
        rcpp_set_stack_trace( stack_trace(file,line) ) ;
    }
    virtual ~exception() noexcept {}
    virtual const char* what() const noexcept { return message.c_str() ; }
private:
    std::string message ;
    
    // A private function for adding backtrace information if possible
    #if defined(__GCC__) || defined(__clang__)
    void add_backtrace_information(std::string& message) {
      const size_t max_depth = 100;
      size_t stack_depth;
      void *stack_addrs[max_depth];
      char **stack_strings;

      stack_depth = backtrace(stack_addrs, max_depth);
      stack_strings = backtrace_symbols(stack_addrs, stack_depth);
      std::vector<std::string> demangled;
      demangled.reserve(stack_depth);

      // demangle the lines and add back in
      for (int i=0; i < stack_depth-2; ++i) {

        std::string buffer( stack_strings[i] );
        std::string buffer2(stack_strings[i] );

        std::string to_add;

        size_t demangle_end = buffer.find_last_of('+') - 1;
        buffer.resize( buffer.find_last_of('+') - 1 ) ;
        size_t demangle_begin = buffer.find_last_of(' ');
        to_add += std::string( buffer.begin(), buffer.begin() + demangle_begin + 1 );
        buffer.erase(
          buffer.begin(),
          buffer.begin() + buffer.find_last_of(' ') + 1
        ) ;
        to_add += Rcpp::demangle(buffer);
        to_add += std::string( buffer2.begin() + demangle_end, buffer2.end() );
        demangled.emplace_back(to_add);
      }

      message += "\n\nTraceback (most recent call first):\n";

      for (int i=0; i < stack_depth-2; ++i) {
        message += demangled[i];
        message += "\n";
      }

      free(stack_strings); // malloc()ed by backtrace_symbols
    }
    #else
    // No-op if we can't add backtrace information
    #define add_backtrace_information
    #endif
} ;

class no_such_env : public exception {
public:
    no_such_env( const std::string& name ) noexcept: 
      exception( std::string("No such environment: '") + name + "'" ){}
      
    no_such_env( int pos ) noexcept:
      exception( "No environment in given position '" + std::to_string(pos) + "'") {}
} ;

class file_io_error : public exception {
public:
    file_io_error(const std::string& file_) noexcept:
      exception( std::string("File IO error: '") + file_ + "'" ), file(file_) {}
      
    file_io_error(int code, const std::string& file_) noexcept:
      exception( "File IO error " + std::to_string(code) + ": '" + file_ + "'"), file(file_) {}
      
    file_io_error(const std::string& msg, const std::string& file_) noexcept:
      exception( msg + ": '" + file_ + "'"), file(file_) {}
      
    std::string filePath() const noexcept{ return file ; }
private:
    std::string file;
} ;

class file_not_found : public file_io_error {
public:
    file_not_found(const std::string& file) noexcept: 
      file_io_error("File not found", file) {}
};

class file_exists : public file_io_error {
public:
    file_exists(const std::string& file) noexcept: 
      file_io_error("File already exists", file) {}
};

#define RCPP_EXCEPTION_CLASS(__CLASS__,__WHAT__)                               \
class __CLASS__ : public exception{                                            \
public:                                                                        \
	explicit __CLASS__( const std::string& msg ) noexcept: exception( __WHAT__ ) \
  {}                                                                           \
  explicit __CLASS__( const char* msg ) noexcept: exception( __WHAT__ ){}      \
};                                                                             

#define RCPP_SIMPLE_EXCEPTION_CLASS(__CLASS__,__MESSAGE__)                     \
class __CLASS__ : public exception{                                            \
public:                                                                        \
	__CLASS__() noexcept: exception(__MESSAGE__) {}                              \
};                                                                             

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
    throw Rcpp::exception( tfm::format(fmt, args...).c_str() );
  }
} // namespace Rcpp

#endif
