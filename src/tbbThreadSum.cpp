#include "tbbThreadSum.h"

// Function to find the shortest distance between 2 numbers
double abs_diff(double a, double b)
{
	double diff = 0;
    if (a>b) { 
        diff = abs(a-b);
    } else if (b>a) {
        diff = abs(b-a);
    } else if (a==b) {
        diff = 0;
    } else {
        std::cout << "Error: Sum is weird!"<<std::endl;
    }

	return diff;
}

// Function to generate a random decimal number between min and max
void generateRandomNumber(std::vector<double> &data) {

    double min = 0.0;
    double max = 1.0;
    int num_elements = data.size();

    static std::random_device rd;
    static std::mt19937 gen(rd());

    // Generate a vector of random decimal numbers
    for (int i = 0; i < num_elements; ++i) {
        std::uniform_real_distribution<> dis(min, max);
        data[i] = dis(gen);
    }

}

// [[Rcpp::export]]
double sum_parallel(std::vector<double> &vec, int num_cores) {

    // Split the vector into chunks based on the number of cores
    int num_elements = vec.size();
    int chunk_size = (num_elements + num_cores - 1) / num_cores;

    // Parallel summation using oneTBB
    double sum = tbb::parallel_reduce(
        tbb::blocked_range<double>(0, num_elements, chunk_size),
        0,
        [&](const tbb::blocked_range<double>& r, double init) {
            double local_sum = init;
            for (int i = r.begin(); i < r.end(); ++i) {
                local_sum += vec[i];
                // if (local_sum>1) local_sum --;
            }
            return local_sum;
        },
        std::plus<double>()
    );

    std::cout << std::fixed;
    std::cout << std::setprecision(25);
    std::cout << sum << std::endl;
    return sum ;
}

double run_sum_parallel(std::vector<double> &vec, int base_num_cores, int num_cores, bool debug) {

    double base_sum = sum_parallel(vec, base_num_cores);
    double sum = sum_parallel(vec, num_cores);
    double aDiffs = abs_diff(base_sum, sum);
    if (debug) {
        int chunk_size = (vec.size() + num_cores - 1) / num_cores;
        std::cout << "Running with "<<num_cores << " cores"<<std::endl;
        std::cout << "  Chunk size of "<< chunk_size << std::endl;
        std::cout << "    Sum with "<<base_num_cores <<" threads: " << base_sum << std::endl;
        std::cout << "    Sum with "<<num_cores <<" threads: " << sum << std::endl;
        std::string is_zero = (aDiffs == 0) ? "equal" : "different";
        std::cout << "    Diff "<< base_num_cores <<" vs "<< num_cores<<": " 
              << aDiffs << ", runs are "<<is_zero<< std::endl;
    }
    return sum;



}

int parallelTbbVectorSum(std::vector<double> vec) {
  
    // Convert R vector into STD
    // std::vector<double> vec(x.begin(),x.end());

    // Get hardware capabilities
    int base_num_cores = std::thread::hardware_concurrency();
    if (base_num_cores == 0) {
        std::cerr << "Unable to determine the number of CPU cores.\n";
        return 1;
    }

    bool debug = true;
    run_sum_parallel(vec, base_num_cores, 4, debug);
    run_sum_parallel(vec, base_num_cores, 2, debug);
    run_sum_parallel(vec, base_num_cores, 4, debug);

    return 0;
}