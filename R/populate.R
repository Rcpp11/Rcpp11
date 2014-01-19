populate <- function( module, env ){
    
    # make sure the module is loaded
    module <- Module( module, mustStart = TRUE )
    
    storage <- get( "storage", as.environment(module ) )
    symbols <- ls( storage )
    
    is_ns <- isNamespace( env )
    for( x in symbols ){
        forceAssignInNamespace( x, storage[[x]], env )
    }
}

