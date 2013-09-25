generators <- setdiff( list.files( "generators", full = TRUE ), "generators/all.R" )
for( f in generators){
    cat( "using generator : ", f, "\n" )
    source(f)    
}

