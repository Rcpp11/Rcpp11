Rcpp.plugin.maker <- function(
	include.before = "",
	include.after = "",
	LinkingTo     = unique( c( package, "Rcpp11" ) ),
	Depends       = unique( c( package, "Rcpp11" ) ),
	libs          = "",
	Makevars      = NULL,
	Makevars.win  = NULL,
	package       = "Rcpp11"
){
	function( ... ){
includes <- sprintf( "%s
#include <Rcpp.h>
%s

#ifndef BEGIN_RCPP
#define BEGIN_RCPP
#endif

#ifndef END_RCPP
#define END_RCPP
#endif

using namespace Rcpp;
", include.before, include.after )

	list(
		env = list( PKG_LIBS = libs ),
		includes = includes,
		LinkingTo = LinkingTo ,
		body = function( x ){
			sprintf( "BEGIN_RCPP\n%s\nEND_RCPP", x )
		},
		Depends = Depends,
		Makevars = Makevars,
		Makevars.win = Makevars.win
	)
}
}

inlineCxxPlugin <- Rcpp.plugin.maker()

