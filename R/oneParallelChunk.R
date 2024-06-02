
one_parallel_sum_chunk <- function(vec = NULL,
                              ncpus = NULL,
                              size = 1e+5,
                              debug = FALSE) {

    if (is.null(vec)) {
        if(debug) message(paste0("Creating vector of ", size, " ..."))
        vec <- stats::runif(size)
    }

    if (is.null(ncpus)) {
        stop("Missing number of CPUs")
    }

    if(debug) message(paste0("Running parallel sum with Rcpp..."))
    RcppParallel::setThreadOptions(numThreads = ncpus)
    oneParallelSumChunked(vec, ncpus)
}
