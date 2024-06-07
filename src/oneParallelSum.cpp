#include "oneParallelSum.h"

#define gettid() ((pid_t)syscall(SYS_gettid))

double trunc_num(double x, double precision, bool debug) {
    double truncated = 0.0;
    int64_t tmp = x * precision;
    truncated = tmp / precision; 

    // truncated = trunc(x*precision)/precision;

    if (debug) {
        Rcpp::Rcout << std::fixed;
        Rcpp::Rcout << std::setprecision(25);
        Rcpp::Rcout << "truncated: " << truncated << std::endl;
    }

    return truncated;
}

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

double oneParallelSum(Rcpp::NumericVector &input) {
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
