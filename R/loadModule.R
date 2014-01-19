
## the following items are to get around some insanity in the
## CMD check of packages using Rcpp11 that dies in loadModule()
## because some code somewhere can't find the methods package
isBotchedSession <- function()
    ! ("package:methods" %in% search())

.moduleNames <- function(what) {
    assignAs <- allNames(what)
    sameNames <- !nzchar(assignAs)
    assignAs[sameNames] <- what[sameNames]
    assignAs
}

.DummyModule <- function(name, what) {
    value <- new.env()
    storage <- new.env()
    assign("storage", storage, envir = value)
    assign("moduleName", name, envir = value)
    allNames <- names(.moduleNames(what))
    for(el in allNames)
        assign(el, NULL, envir = storage)
    value
}

.moduleMetaName <- function(name)
    methods::methodsPackageMetaName("Mod",name)

moduleIsLoaded <- function(name, env)
    exists(.moduleMetaName(name), envir = env, inherits = FALSE)

loadModule <- function( module, what = character(), loadNow,
                      env = topenv(parent.frame())) {

    if(is(module, "character")) {
        loadM <- NULL
        metaName <- .moduleMetaName(module)
        if(exists(metaName, envir = env, inherits = FALSE))
            loadM <- get(metaName, envir = env)
    }
    else if(is(module, "Module")) {
        loadM <- as.environment(module)
        module <- get(loadM, "moduleName")
    }
    else
        stop(gettextf("Argument \"module\" should be a module or the name of a module: got an object of class \"%s\"", class(module)))
    if(missing(loadNow)) { # test it
        if(is.null(loadM))
            loadM <- tryCatch(Module( module, mustStart = TRUE, where = env ),
                           error = function(e)e)
        loadNow <- !is(loadM, "error")
    }
    if(loadNow) {
        .botched <- isBotchedSession()
        if(is.null(loadM))
            loadM <- tryCatch(Module( module, mustStart = TRUE, where = env ),
                              error = function(e)e)
        if(is(loadM, "error")) {
            if(.botched)
               return(.DummyModule(module, what))
            stop(gettextf("Unable to load module \"%s\": %s",
                as(module, "character"), loadM$message))
        }
        if(!exists(metaName, envir = env, inherits =FALSE))
            assign(metaName, loadM, envir = env)
        if(!length(what)) #  no assignments
            return(loadM)
        env <- as.environment(env)
        ## get the storage environment, for what=TRUE
        storage <- as.environment(get( "storage", as.environment(loadM ) ))
        if(identical(what, TRUE))
            what <- objects(storage)
        missingObjs <- !sapply(what, function(symb) exists(symb, envir = storage, inherits = FALSE))
        if(any(missingObjs)) {
            if(.botched) {
                for(el in what[missingObjs])
                    assign(el, NULL, envir = storage)
            }
            else {
                warning(gettextf("%s not found in module \"%s\"",
                             paste0('"', what[missingObjs], '"', collapse = ", "),
                             as.character(module)))
                what <- what[!missingObjs]
            }
        }
        assignAs <- .moduleNames(what)
        for( i in seq_along(what) ) {
            if(.botched)
                assign(assignAs[[i]], NULL, envir = storage)
            else
                assign(assignAs[[i]], get(what[[i]], envir = storage), envir = env)
        }
        loadM
    }
    else { # create a load action to recall this function
        myCall <- match.call()
        f <- function(ns) NULL
        myCall$env <- as.name("ns")
        myCall$loadNow <- TRUE
        body(f, envir = env) <- myCall
        setLoadAction(f, where = env)
        invisible(myCall)
    }
}

