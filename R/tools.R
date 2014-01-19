externalptr_address <- function(xp){
    .Call( as_character_externalptr, xp )
}

# just like assignInNamespace but first checks that the binding exists
forceAssignInNamespace <- function( x, value, env ){
    is_ns <- isNamespace( env )
    unlocker <- get( "unlockBinding", baseenv() )
    if( is_ns && exists( x, env ) && bindingIsLocked(x, env ) ){
        unlocker( x, env )
    }
    assign( x, value, env )
    if( is_ns ){
        lockBinding( x, env )
    }
}

# Transform a path for passing to the build system on the command line.
# Leave paths alone for posix. For Windows, mirror the behavior of the 
# R package build system by starting with the fully resolved absolute path,
# transforming it to a short path name if it contains spaces, and then 
# converting backslashes to forward slashes
asBuildPath <- function(path) {
    
    if (.Platform$OS.type == "windows") {
        path <- normalizePath(path)
        if (grepl(' ', path, fixed=TRUE))
            path <- utils::shortPathName(path)
        path <- gsub("\\\\", "/", path)
    }
    
    return(path)
}
