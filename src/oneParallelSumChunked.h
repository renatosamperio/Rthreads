#include "oneapi/tbb/parallel_reduce.h"
#include "oneapi/tbb/blocked_range.h"
#include <random>
#include <iostream>
#include <unistd.h>

using namespace oneapi::tbb;

// [[Rcpp::export]]
double oneParallelSumChunked(std::vector<double> &v, int num_cores);
