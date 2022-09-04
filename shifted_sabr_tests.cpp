#include <fstream>
#include <iostream>
#include "shifted_sabr.hpp"
#include "shifted_sabr_tests.hpp"

void shifted_sabr_tests::test_shifted_sabr() {
    Tape t;
    Var forward = t.var(2.5e-2);
    Var time_to_expiry = t.var(10.0);
    Var alpha = t.var(0.28);
    Var beta = t.var(0.36);
    Var rho = t.var(0.05);
    Var sigma0 = t.var(0.019);
    Var zeta = t.var(0.03);

    ShiftedSABR shifty(forward, time_to_expiry, alpha, beta, rho, zeta, sigma0);

    double strike_start = -2e-2;
    double strike_end = 10e-2;
    int n_strikes = 100;
    double strike_step = (strike_end - strike_start) / n_strikes;

    double this_strike = strike_start;

    std::ofstream my_file;
    my_file.open("release/shifted_sabr_smile.csv");

    for (int i = 0; i < n_strikes; i++) {
        Var implied_vol = shifty(t.var(this_strike));
        my_file << this_strike << "," << implied_vol.value << "\n";
        this_strike += strike_step;
    }

    my_file.close();

    return;
}
