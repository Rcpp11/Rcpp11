setGeneric( ".DollarNames" )
.DollarNames.Module <- function(x, pattern){    
    pointer <- .getModulePointer( x )
    if(identical(pointer, .badModulePointer)) {
        stop( "unitialized module" )
    }
    grep( pattern , .Call( Module__complete, pointer), value = TRUE )	
}
setMethod( ".DollarNames", "Module", .DollarNames.Module )

# completion for C++ objects
# do we actually need this or do we get it for free via setRefClass, etc ...
setGeneric( "complete", function(x) standardGeneric("complete") )
setMethod( "complete", "C++Object", function(x){
    xp <- get(".cppclass", envir = as.environment(x))
    # FIXME: implement another test  
    #    if(identical(xp, .emptyPointer))
    #        stop("C++ object with unset pointer to C++ class")
    .Call( CppClass__complete , xp )
} )

".DollarNames.C++Object" <- function( x, pattern ){
	grep( pattern, complete(x), value = TRUE )
}
setMethod( ".DollarNames", "C++Object", `.DollarNames.C++Object` )

