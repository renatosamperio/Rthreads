#include "oneParallelSumWorker.h"

#define gettid() ((pid_t)syscall(SYS_gettid))

struct oneSum {
    double value;
    oneSum() : value(0) {}
    oneSum( oneSum& s, split ) {value = 0;}

    void operator()( const blocked_range<double*>& input ) {
        double temp = value;
        // Rcpp::Rcout << "(" << std::this_thread::get_id() << " - " << r.begin() << " : " 
        //           << r.end() << "): " << std::endl;
        
        // value += std::accumulate(
        //     input.begin(), input.begin(), 0.0);

        for( double* a = input.begin(); a != input.end(); ++a ) {
            temp += *a;
        }
        
        value = temp;
    }
    void join( oneSum& rhs ) {value += rhs.value;}
};

double oneParallelSumWorker(Rcpp::NumericVector &input) {
    int num_elements = input.size();
    std::vector<double> vec( input.begin(), input.end() ) ; 
    double* array = vec.data();

    // Parallel summation using oneTBB
    oneSum total;

    // call threaded reduce part
    oneapi::tbb::parallel_reduce(
        oneapi::tbb::blocked_range<double*>( array, array+num_elements ),
        total 
    );

    return total.value;
}
