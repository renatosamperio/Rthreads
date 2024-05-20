#include "oneapi/tbb/parallel_reduce.h"
#include "oneapi/tbb/blocked_range.h"
#include <random>
#include <iostream>
#include <Rcpp.h>

#include <unistd.h>

using namespace oneapi::tbb;

// [[Rcpp::export]]
double trunc_num(double x, double precision = 1.0e10, bool debug = false);

// [[Rcpp::export]]
double oneParallelSum(Rcpp::NumericVector &v);
