Rcpp.package.skeleton <- function(
	name = "anRpackage", list = character(), environment = .GlobalEnv,
	path = ".", force = FALSE,
	code_files = character(), cpp_files = character(),
	example_code = TRUE,
	attributes = TRUE,
	module = FALSE,
	author = "Who wrote it",
	maintainer = if(missing( author)) "Who to complain to" else author,
	email = "yourfault@somewhere.net",
	license = "What Licence is it under ?"
	){
	
	if (!is.character(cpp_files)) 
		stop("'cpp_files' must be a character vector")
	# set example_code if attributes is set
	if( isTRUE(attributes) )
	    example_code <- TRUE
	env <- parent.frame(1)

	if( !length(list) ){
		fake <- TRUE
		assign( "Rcpp.fake.fun", function(){}, envir = env )
		if( example_code && !isTRUE(attributes)){ 
			assign( "rcpp_hello_world", function(){}, envir = env )
			remove_hello_world <- TRUE
		} else {
		    remove_hello_world <- FALSE
		}
	} else {
		if( ! "rcpp_hello_world" %in% list ){
			call[["list"]] <- c( "rcpp_hello_world", call[["list"]] )
			remove_hello_world <- TRUE
		} else{
			remove_hello_world <- FALSE
		}
		fake <- FALSE
	}

	# first let the traditional version do its business
	call <- match.call()
	call[[1]] <- as.name("package.skeleton")
	# remove Rcpp specific arguments

	call <- call[ c( 1L, which( names(call) %in% names(formals(package.skeleton)))) ]

	if( fake ){
		call[["list"]] <- c( if( isTRUE(example_code) && !isTRUE(attributes)) "rcpp_hello_world" , "Rcpp.fake.fun" )
	}

	tryCatch( eval( call, envir = env ), error = function(e){
		stop( sprintf( "error while calling `package.skeleton` : %s", conditionMessage(e) ) )
	} )

	message( "\nAdding Rcpp11 settings" )

	# now pick things up
	root <- file.path( path, name )

	# Add Rcpp to the DESCRIPTION
	DESCRIPTION <- file.path( root, "DESCRIPTION" )
	if( file.exists( DESCRIPTION ) ){
		depends <- c(
			if( isTRUE(module) ) "methods",
			sprintf( "Rcpp11 (>= %s)", packageDescription("Rcpp11")[["Version"]] )
		)
		x <- cbind( read.dcf( DESCRIPTION ),
			"Depends" = paste( depends, collapse = ", ") ,
			"LinkingTo" = "Rcpp11"
		)
		if( isTRUE( module ) ){
		    x <- cbind( x, "RcppModules" = "yada, stdVector, NumEx" )
		    message( " >> added RcppModules: yada" )
		}
		x[, "Author" ] <- author
		x[, "Maintainer" ] <- sprintf( "%s <%s>", maintainer, email )
		x[, "License"] <- license
		message( " >> added Depends: Rcpp11" )
		message( " >> added LinkingTo: Rcpp11" )
		write.dcf( x, file = DESCRIPTION )

	}

	# if there is a NAMESPACE, add a useDynLib
	NAMESPACE <- file.path( root, "NAMESPACE")
	if( file.exists( NAMESPACE ) ){
		lines <- readLines( NAMESPACE )
		ns <- file( NAMESPACE, open = "w" )
		if( ! grepl( "useDynLib", lines ) ){
			lines <- c( sprintf( "useDynLib(%s)", name), lines)
			writeLines( lines, con = ns )
			message( " >> added useDynLib directive to NAMESPACE" )
		}

		if(isTRUE(module)){
			writeLines( 'import( Rcpp11 )', ns )
		}
		close( ns )
	}
	
	# update the package description help page
	package_help_page <- file.path( root, "man", sprintf( "%s-package.Rd", name ) )
	if( file.exists(package_help_page) ){
	    lines <- readLines(package_help_page)
	    lines <- gsub( "What license is it under?", license, lines, fixed = TRUE )
	    lines <- gsub( "Who to complain to <yourfault@somewhere.net>", 
	        sprintf( "%s <%s>", maintainer, email),  
	        lines, 
	        fixed = TRUE
	        )
	    lines <- gsub( "Who wrote it", author, lines, fixed = TRUE )
	    writeLines( lines, package_help_page )
	}

	# lay things out in the src directory
	src <- file.path( root, "src")
	if( !file.exists( src )){
		dir.create( src )
	}
	skeleton <- system.file( "skeleton", package = "Rcpp11" )
	if ( length(cpp_files) > 0L ) {
		for (file in cpp_files) {
			file.copy(file, src)
			message( " >> copied ", file, " to src directory" )
		}
		compileAttributes(root)
	}
	
	if( example_code ){
		if ( isTRUE( attributes ) ) {
			file.copy( file.path( skeleton, "rcpp_hello_world_attributes.cpp" ), 
								 file.path( src, "rcpp_hello_world.cpp" ) )
			message( " >> added example src file using Rcpp attributes")
			compileAttributes(root)
			message( " >> compiled Rcpp attributes")
		} else {
			header <- readLines( file.path( skeleton, "rcpp_hello_world.h" ) )
			header <- gsub( "@PKG@", name, header, fixed = TRUE )
			writeLines( header , file.path( src, "rcpp_hello_world.h" ) )
			message( " >> added example header file using Rcpp classes")
			
			file.copy( file.path( skeleton, "rcpp_hello_world.cpp" ), src )
			message( " >> added example src file using Rcpp classes")
			
			rcode <- readLines( file.path( skeleton, "rcpp_hello_world.R" ) )
			rcode <- gsub( "@PKG@", name, rcode, fixed = TRUE )
			writeLines( rcode , file.path( root, "R", "rcpp_hello_world.R" ) )
			message( " >> added example R file calling the C++ example")
		}
		
		hello.Rd <- file.path( root, "man", "rcpp_hello_world.Rd")
		unlink( hello.Rd )
		file.copy(
			system.file("skeleton", "rcpp_hello_world.Rd", package = "Rcpp11" ),
			hello.Rd
			)
		message( " >> added Rd file for rcpp_hello_world")

	}

	if( isTRUE( module ) ){
		file.copy(system.file( "skeleton", "rcpp_module.cpp", package = "Rcpp11" ), file.path( root, "src" ))
		file.copy(system.file( "skeleton", "Num.cpp", package = "Rcpp11" ), file.path( root, "src" ))
		file.copy(system.file( "skeleton", "stdVector.cpp", package = "Rcpp11" ), file.path( root, "src" ))
		file.copy(system.file( "skeleton", "zzz.R", package = "Rcpp11" ), file.path( root, "R" ))
		message( " >> copied the example module file " )

	}

	lines <- readLines( package.doc <- file.path( root, "man", sprintf( "%s-package.Rd", name ) ) )
	lines <- sub( "~~ simple examples", "%% ~~ simple examples", lines )

	lines <- lines[ !grepl( "~~ package title", lines) ]
	lines <- lines[ !grepl( "~~ The author and", lines) ]
	lines <- sub( "Who wrote it", author, lines )
	lines <- sub( "Who to complain to.*", sprintf( "%s <%s>", maintainer, email), lines )

	writeLines( lines, package.doc )

	if( fake ){
		rm( "Rcpp.fake.fun", envir = env )
		unlink( file.path( root, "R"  , "Rcpp.fake.fun.R" ) )
		unlink( file.path( root, "man", "Rcpp.fake.fun.Rd" ) )
	}

	if( isTRUE(remove_hello_world) ){
		rm( "rcpp_hello_world", envir = env )
	}

	invisible( NULL )
}

