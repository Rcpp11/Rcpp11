
# anticipating a change in R 2.16.0
setClass( "refClassGeneratorFunction" )
setClassUnion("refGenerator", c("refObjectGenerator", "refClassGeneratorFunction")) 

## "Module" class as an environment with "pointer", "moduleName",
##  "packageName" and "refClassGenerators"
## Stands in for a reference class with those fields.
setClass( "Module",  contains = "environment" )

setRefClass( "C++Field", 
    fields = list( 
        pointer       = "externalptr", 
        cpp_class     = "character", 
        read_only     = "logical", 
        class_pointer = "externalptr", 
        docstring     = "character"
    )
)

setRefClass( "C++OverloadedMethods", 
    fields = list( 
        pointer       = "externalptr", 
        class_pointer = "externalptr", 
        size          = "integer", 
        void          = "logical",
        const         = "logical", 
        docstrings    = "character", 
        signatures    = "character", 
        nargs         = "integer"
    ), 
    methods = list( 
        info = function(prefix = "    " ){
             paste( 
                paste( prefix, signatures, ifelse(const, " const", "" ), "\n", prefix, prefix, 
                    ifelse( nchar(docstrings), paste( "docstring :", docstrings) , "" ) 
                ) , collapse = "\n" )   
        }
    )
)

setRefClass( "C++Constructor", 
    fields = list( 
        pointer       = "externalptr", 
        class_pointer = "externalptr", 
        nargs         = "integer", 
        signature     = "character", 
        docstring     = "character"
    )
)

setClass( "C++Class", 
	representation( 
	    pointer      = "externalptr", 
	    module       = "externalptr", 
	    fields       = "list",
	    methods      = "list",
	    constructors = "list",
	    generator    = "refGenerator", 
	    docstring    = "character", 
	    typeid       = "character", 
	    enums        = "list", 
	    parents      = "character"
	), 
	contains = "character"
	)
	
setClass( "C++Object")

setClass( "C++Function", 
	representation( 
	    pointer   = "externalptr", 
	    docstring = "character", 
	    signature = "character"
	), 
	contains = "function"
)

.cppfunction_formals_gets <- function (fun, envir = environment(fun), value) {
    bd <- body(fun)
    b2 <- bd[[2L]]
    for( i in seq_along(value) ){
        b2[[3L+i]] <- as.name( names(value)[i] )
    }
    bd[[2]] <- b2
    f <- fun@.Data
    formals(f) <- value
    body(f) <- bd
    fun@.Data <- f
    fun
}
setGeneric( "formals<-" )
setMethod( "formals<-", "C++Function", .cppfunction_formals_gets )
