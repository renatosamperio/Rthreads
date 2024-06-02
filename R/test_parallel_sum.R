# Sys.setenv(MKL_CBWR = "AVX2,STRICT")
# Sys.setenv(MKL_CBWR = "COMPATIBLE")
# Sys.setenv(MKL_NUM_THREADS = "4")
# options(digits=20)

if (FALSE) {
    message(paste0("MKL_CBWR: ", Sys.getenv("MKL_CBWR")))
}

.rotate_ncpus <- \(out_vector, input_vec, func, ncpus = NA) {
    vec_size <- length(out_vector)

    if (is.na(ncpus)) {
        ncpus <- ((vec_size %% 4) + 1) * 2
    }
    
    c(out_vector, func(input_vec, ncpus))
}

.stats <- \(input) {
    list(
        data = sort(input),
        avg = mean(input),
        stdev = sd(input),
        max = max(input),
        min = min(input),
        range = max(input) - min(input)
    )
}

test_parallel_sum <- function(
    vec = NA,
    times = 50, 
    ncpus = NA, 
    v_size = 1e05) {

    if (any(is.na(vec))) {
        vec <- runif(v_size, min = 1000.0, max = 1.0e6)
    }
    
    out_rcpp <- c()
    out_one <- c()
    out_one_chu <- c()
    out_one_det <- c()


    res_benchmark <- microbenchmark::microbenchmark(
        out_rcpp    <- .rotate_ncpus(out_rcpp,    vec, rcpp_parallel_sum,      ncpus = ncpus),
        out_one     <- .rotate_ncpus(out_one,     vec, one_parallel_sum,       ncpus = ncpus),
        out_one_chu <- .rotate_ncpus(out_one_chu, vec, one_parallel_sum_chunk, ncpus = ncpus),
        out_one_det <- .rotate_ncpus(out_one_det, vec, one_parallel_det_sum,   ncpus = ncpus),
        times = times
    )

    # result output
    res <- list(
        rcpp = .stats(out_rcpp),
        one = .stats(out_one),
        chunk = .stats(out_one_chu),
        det = .stats(out_one_det),
        benchmark = res_benchmark
    )

    sum_bench <- summary(res_benchmark)

    # preparing short report
    ndig <- 3
    report <- data.frame(matrix(ncol = 3, nrow = 0))
    colnames(report) <- c("style", "stdev", "duration")
    report[nrow(report) + 1, ] <- c(
        "rcpp", format(res$rcpp$stdev, digits = ndig), sum_bench$mean[[1]])
    report[nrow(report) + 1, ] <- c(
        "one", format(res$one$stdev, digits = ndig), sum_bench$mean[[2]])
    report[nrow(report) + 1, ] <- c(
        "chunk", format(res$chunk$stdev, digits = ndig), sum_bench$mean[[3]])
    report[nrow(report) + 1, ] <- c(
        "det",   format(res$det$stdev, digits = ndig), sum_bench$mean[[4]])
    print(report)

    res
}

