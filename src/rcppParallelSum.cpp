#include "rcppParallelSum.h"

struct RcppSum : public RcppParallel::Worker
{
   // source vector
   const RcppParallel::RVector<double> input;

   // accumulated value
   double value;

   // constructors
   RcppSum(const Rcpp::NumericVector input) : input(input), value(0) {}
   RcppSum(const RcppSum& sum, RcppParallel::Split) : input(sum.input), value(0) {}

   // accumulate just the element of the range I've been asked to
   void operator()(std::size_t begin, std::size_t end) {
      // value += std::accumulate(input.begin() + begin, input.begin() + end, 0.0);

      for (size_t i = begin; i < end; i++) {
         value += input[i];
      }
   }

   // join my value with that of another Sum
   void join(const RcppSum& rhs) {
      value += rhs.value;
   }
};


double rcppParallelSum(Rcpp::NumericVector &input) {

   // declare the SumBody instance
   RcppSum sum(input);

   // call parallel_reduce to start the work
   RcppParallel::parallelReduce(0, input.length(), sum);

   // return the computed sum
   return sum.value;

}