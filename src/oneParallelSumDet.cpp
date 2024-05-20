#include "oneParallelSumDet.h"

double oneParallelSumDeterministic(std::vector<double> &numbers, int num_cores) {

    // Using parallel_deterministic_reduce
    double sum = 0.0;
    int num_elements = numbers.size();
    int chunk_size = (num_elements + num_cores - 1) / num_cores;

    sum = oneapi::tbb::parallel_deterministic_reduce(
        oneapi::tbb::blocked_range<size_t>(0, numbers.size(), chunk_size),
        0.0, // Initial value for the sum
        [&numbers](const oneapi::tbb::blocked_range<size_t>& r, double init) -> double {
            double local_sum = init;
            // Rcpp::Rcout << "(" << std::this_thread::get_id() << " - " << r.begin() << " : " << r.end() << ")" << std::endl;

            for (size_t i = r.begin(); i != r.end(); ++i) {
                local_sum += numbers[i];
            }

            // std::cout << "(" << std::this_thread::get_id() << "," << gettid() << " - " << r.begin() << " : " << r.end() << ")" << std::endl;
            return local_sum;
        },
        [](double x, double y) -> double {
            return x + y;
        }
    );

    return sum;
}
