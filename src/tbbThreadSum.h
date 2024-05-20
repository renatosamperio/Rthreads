#include <iostream>
#include <vector>
#include <tbb/tbb.h>
#include <thread>
#include <math.h>
#include <random>
#include <Rcpp.h>

using namespace Rcpp;

const int NUM_ELEMENTS = 1e7; // Change this to the size of your vector

double abs_diff(double a, double b);

void generateRandomNumber(std::vector<double> &data);

double sum_parallel(std::vector<double> &vec, int num_cores);

double run_sum_parallel(std::vector<double> &vec, int base_num_cores, int num_cores, bool debug = false);

int parallelTbbVectorSum(Rcpp::NumericVector x, int numThreads);