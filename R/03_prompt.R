setGeneric( "functions", function(object, ...) standardGeneric( "functions" ) )
setMethod( "functions", "Module", function(object, ...){
    pointer <- .getModulePointer(object)
    if(identical(pointer, .badModulePointer))
        stop(gettextf("Module \"%s\" has not been intialized:  try Module(object)",
                      get("moduleName", envir = as.environment(object))), domain = NA)
    else
	.Call( Module__functions_arity, pointer )
} )

setGeneric( "prompt" )
setMethod( "prompt", "Module", function(object, filename = NULL, name = NULL, ...){
	lines <- readLines( system.file( "prompt", "module.Rd", package = "Rcpp11" ) )
        pointer <- .getModulePointer(object)
	if( is.null(name) )
            name <- .Call( Module__name, pointer )
	if( is.null(filename) ) filename <- sprintf( "%s-module.Rd", name )
	lines <- gsub( "NAME", name, lines )
	
	info <- functions( object )
	f.txt <- if( length( info ) ){
		sprintf( "functions: \\\\describe{
%s
		}", paste( sprintf( "        \\\\item{%s}{ ~~ description of function %s ~~ }", names(info), names(info) ), collapse = "\n" ) )
	} else {
		"" 
	}
	lines <- sub( "FUNCTIONS", f.txt, lines )

        ## at this point functions() would have failed if the
        ## pointer in object was not valid
	
	classes <- .Call( Module__classes_info, pointer )
	c.txt <- if( length( classes ) ){
		sprintf( "classes: \\\\describe{
%s
		}", paste( sprintf( "        \\\\item{%s}{ ~~ description of class %s ~~ }", names(classes), names(classes) ), collapse = "\n" ) )
	} else {
		"" 
	}
	lines <- sub( "CLASSES", c.txt, lines )
	
	writeLines( lines, filename )
	invisible(NULL)
} )

