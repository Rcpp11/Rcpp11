#ifndef Rcpp__exceptions__h
#define Rcpp__exceptions__h

// for backtraces
#if ( defined(__GNUC__) || defined(__clang__) ) &&  !defined(_WIN32)
    #include <execinfo.h>
#endif

namespace Rcpp{

    inline std::string demangle( const std::string& name ){
        std::string real_class ;
        int status =-1 ;
        char *dem = 0;
        dem = abi::__cxa_demangle(name.c_str(), 0, 0, &status);
        if( status == 0 ){
            real_class = dem ;
            free(dem);
        } else {
            real_class = name ;
        }
        return real_class ;
    }

    class exception : public std::exception {
    public:
        explicit exception(const char* message_) : message(message_) {
            add_backtrace_information(message);
        }
        explicit exception(std::string  message_) : message(std::move(message_)) {
            add_backtrace_information(message);
        }
        exception(const char* message_, const char* file, int line ): message(message_) {
            add_backtrace_information(message);
        }
        virtual ~exception() noexcept {}
        virtual const char* what() const noexcept /* override */ { return message.c_str() ; }
    
    private:
        std::string message ;
    
        // A private function for adding backtrace information if possible
        #if ( defined(__GNUC__) || defined(__clang__) ) &&  !defined(_WIN32)
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
          for (size_t i=0; i < stack_depth-2; ++i) {
    
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
    
          for (size_t i=0; i < stack_depth-2; ++i) {
            message += demangled[i];
            message += "\n";
          }
    
          free(stack_strings); // malloc()ed by backtrace_symbols
        }
        #else
        // No-op if we can't add backtrace information
        void add_backtrace_information(std::string& message) {
          // do nothing
        }
        #endif
    } ;

    template <typename... Args>
    inline void stop(const char* fmt, Args&&... args) {
        throw Rcpp::exception( tfm::format(fmt, std::forward<Args>(args)...).c_str() );
    }
    
} // namespace Rcpp

#define DEMANGLE(__TYPE__) Rcpp::Demangler<__TYPE__>::get().c_str()

#endif
