#include <random>
#include <iostream>
#include <Rcpp.h>
#include <RcppParallel.h>

#include <unistd.h>

// [[Rcpp::export]]
double rcppParallelSum(Rcpp::NumericVector &v);
