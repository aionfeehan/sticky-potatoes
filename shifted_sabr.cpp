
#include <cmath>
#include "shifted_sabr.hpp"

ShiftedSABR::ShiftedSABR(double forward, double time_to_expiry, double alpha, double beta, double rho, double zeta, double sigma0):
    forward_(forward),
    time_to_expiry_(time_to_expiry),
    alpha_(alpha),
    beta_(beta),
    rho_(rho),
    zeta_(zeta),
    sigma0_(sigma0)
    {}


Var ShiftedSABR::operator()(double strike) {
    Tape t;
    var_forward_ = t.var(forward_);
    var_sigma0_ = t.var(sigma0_);
    var_alpha_ = t.var(alpha_);
    var_beta_ = t.var(beta_);
    var_rho_ = t.var(rho_);
    var_zeta_ = t.var(zeta_);
    Var moneyness = var_forward_ - strike;
    Var s = var_forward_ + var_zeta_;
    Var shifted_strike = strike + var_zeta_;
    Var I0;
    Var z;
    if (fabs(moneyness.value) < 1e-15) {
        I0 = var_sigma0_ * pow(s, var_beta_);
    }
    else {
        if (var_beta_.value > 1 - 1e-14) {
            z = var_alpha_ * moneyness / var_sigma0_;
    }
        else {
            z = var_alpha_ / var_sigma0_ * (pow(s, 1.0 - var_beta_) - pow(shifted_strike, 1.0 - var_beta_)) / (1.0 - var_beta_);
        }
        Var in_sqrt = 1.0 - 2.0 * var_rho_ * z + z * z;
        I0 = moneyness * var_alpha_ / log((sqrt(in_sqrt) + z - var_rho_) / (1.0 - var_rho_));
    }
    
    
    Var I1_term_1 = ((var_beta_ * var_beta_ - 2.0 * var_beta_) * var_sigma0_ * var_sigma0_) / (24.0 * pow((shifted_strike + s) / 2.0, 2.0 * (1.0 - var_beta_)));
    Var I1_term_2 = (var_rho_ * var_alpha_ * var_sigma0_ * var_beta_) / (4.0 * pow((shifted_strike + s) / 2.0, 1.0 - var_beta_));
    Var I1_term_3 = ((2.0 - 3.0 * var_rho_ * var_rho_) * var_alpha_ * var_alpha_) / 24.0;

    Var I1 = I1_term_1 + I1_term_2 + I1_term_3;

    return I0 * (1.0 + I1 * time_to_expiry_);

}

