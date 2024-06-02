#       vec <- stats::runif(1e+8)
#       one_parallel_det_sum(vec, ncpus = 4)
one_parallel_det_sum <- function(vec = NULL,
                                 ncpus = NULL,
                                 size = 1e+8,
                                 debug = FALSE) {

    if (is.null(vec)) {
        if(debug) message(paste0("Creating vector of ", size, " ..."))
        vec <- stats::runif(size)
    }

    if (is.null(ncpus)) {
        stop("Missing number of CPUs")
    }

    if(debug) message(paste0("Running parallel deterministic sum with oneTBB..."))
    RcppParallel::setThreadOptions(numThreads = ncpus)
    oneParallelSumDeterministic(vec, ncpus)
}