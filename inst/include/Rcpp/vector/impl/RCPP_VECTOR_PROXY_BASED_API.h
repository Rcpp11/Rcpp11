    // don't add include guards here; I'm included multiple times

    inline iterator begin() { 
        return iterator( Proxy(*this, 0) ); 
    }
    inline iterator end() { 
        return iterator( Proxy(*this, size() ) ); 
    }
    
    inline const iterator begin() const{ 
        return iterator( Proxy(const_cast<Vector&>(*this), 0) );
    }
    inline iterator end() const{ 
        return iterator( Proxy(const_cast<Vector&>(*this), size()) );
    }
    
    inline Proxy operator[](R_xlen_t i){
        RCPP_CHECK_BOUNDS(i)
        return Proxy(*this, i ) ;
    }
    inline const Proxy operator[](R_xlen_t i) const {
        RCPP_CHECK_BOUNDS(i)
        return Proxy(const_cast<Vector&>(*this), i ) ; 
    }
        
