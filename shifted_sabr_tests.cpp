#include <fstream>
#include <iostream>
#include "shifted_sabr.hpp"
#include "shifted_sabr_tests.hpp"

void shifted_sabr_tests::test_shifted_sabr() {
    double forward = 2.5e-2;
    double time_to_expiry = 10.0;
    double alpha = 0.28;
    double beta = 0.36;
    double rho = 0.05;
    double sigma0 = 0.019;
    double zeta = 0.03;

    ShiftedSABR shifty(forward, time_to_expiry, alpha, beta, rho, zeta, sigma0);

    double strike_start = -2e-2;
    double strike_end = 10e-2;
    int n_strikes = 100;
    double strike_step = (strike_end - strike_start) / n_strikes;

    double this_strike = strike_start;

    std::ofstream my_file;
    my_file.open("shifted_sabr_smile.csv");

    for (int i = 0; i < n_strikes; i++) {
        Var implied_vol = shifty(this_strike);
        my_file << this_strike << "," << implied_vol.value << "\n";
        this_strike += strike_step;
    }

    my_file.close();

    return;
}
