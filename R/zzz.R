.dummyInstancePointer <- new.env() # just something permanent

.classes_map <- new.env()

.onLoad <- function(libname, pkgname){
    minimum_svn_rev <- packageDescription( pkgname )[["MinimumSvnRev"]]
    # if( as.integer(R.version[["svn rev"]]) < as.integer(minimum_svn_rev)){
    #     packageStartupMessage(gettextf(paste("R version (%s) older than minimum required (%s)",
    #                                          "for full use of reference methods"),
    #                                    R.version[["svn rev"]], minimum_svn_rev))
    # }
    new_dummyObject(.dummyInstancePointer)
}


