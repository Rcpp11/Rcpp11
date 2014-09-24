#include <string>
#include <cstdlib>

// Macros for symbol getting, etc.
#ifdef _WIN32
#include <windows.h>

#define DL_OPEN(__LIBRARY__) \
  (void*) ::LoadLibraryEx(__LIBRARY__, nullptr, 0)

#define DL_SYM(__LIBRARY__, __SYMBOL__) \
  (void*) ::GetProcAddress( (HINSTANCE) __LIBRARY__, __SYMBOL )

#define DL_CLOSE(__LIBRARY__) \
  ::FreeLibrary( (HMODULE) __LIBRARY__ )

#else

// UNIX-alikes
#include <dlfcn.h>

#define DL_OPEN(__LIBRARY__) \
  (void*) ::dlopen(__LIBRARY__, RTLD_NOW)

#define DL_SYM(__LIBRARY__, __SYMBOL__) \
  (void*) ::dlsym(__LIBRARY__, __SYMBOL__)

#define DL_CLOSE(__LIBRARY__) \
  ::dlclose(__LIBRARY__)

#endif

namespace Rcpp {

template <typename... Args>
inline void stop(const char* fmt, Args&&... args);

namespace internal {

class Library {

public:

  Library(std::string libPath):
    libPath_(std::move(libPath)),
    pLib_(nullptr) {}
  
  Library(Library const& other) = delete;

  ~Library() {
    if (pLib_ != nullptr) {
      DL_CLOSE(pLib_);
    }
  }

  inline void* operator[](std::string const& symbol) {

    // Open the library, if necessary
    if (pLib_ == nullptr) {
      pLib_ = DL_OPEN(libPath_.c_str());
      if (pLib_ == nullptr) {
        stop("Failed to open library at path: '%s'", libPath_);
      }
    }

    // Get the symbol from the library
    void* result = DL_SYM(pLib_, symbol.c_str());
    if (result == nullptr) {
      stop("Failed to find symbol: '%s'", symbol);
    }
    return result;
    
  }

private:
  std::string libPath_;
  void* pLib_;
  
};

inline std::string findLibR() {

  std::string R_HOME{std::getenv("R_HOME")};
  if (R_HOME.empty()) {
    stop("'R_HOME' environment variable not set; cannot find libR");
  }

#if defined(__APPLE__)
  return R_HOME + "/lib/libR.dylib";
#elif defined(__linux__)
  return R_HOME + "/lib/libR.so";
#elif defined(_WIN32)
    stop("Sorry -- no Windows yet!");
  return std::string();
#else
  stop("Unrecognized OS");
  return std::string();
#endif
  
}

#undef DL_OPEN
#undef DL_CLOSE
#undef DL_SYM

} // end namespace internal

static internal::Library libR{ internal::findLibR() };

} // end namespace Rcpp
