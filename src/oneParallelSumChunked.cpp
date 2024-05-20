#include "oneParallelSumChunked.h"

double oneParallelSumChunked(std::vector<double> &vec, int num_cores) {

    // Split the vector into chunks based on the number of cores
    double sum = 0.0;
    int num_elements = vec.size();
    int chunk_size = (num_elements + num_cores - 1) / num_cores;
    // std::cout << "  Chunk size of "<<chunk_size << std::endl;

    sum = oneapi::tbb::parallel_reduce(
        oneapi::tbb::blocked_range<size_t>(0, num_elements, chunk_size),
        0.0, // Initial value for the sum
        [&vec](const oneapi::tbb::blocked_range<size_t>& r, double init) -> double {
            double local_sum = init;
            for (size_t i = r.begin(); i != r.end(); ++i) {
                local_sum += vec[i];
            }
            return local_sum;
        },
        [](double x, double y) -> double {
            return x + y;
        }
    );
    return sum;
}
