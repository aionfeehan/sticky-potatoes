
#include <cmath>
#include "shifted_sabr.hpp"

ShiftedSABR::ShiftedSABR(Var forward, Var time_to_expiry, Var alpha, Var beta, Var rho, Var zeta, Var sigma0):
    forward_(forward),
    time_to_expiry_(time_to_expiry),
    alpha_(alpha),
    beta_(beta),
    rho_(rho),
    zeta_(zeta),
    sigma0_(sigma0),
    tape_(alpha.tape)
    {}


Var ShiftedSABR::operator()(Var strike) {
    Var moneyness = forward_ - strike;
    Var s = forward_ + zeta_;
    Var shifted_strike = strike + zeta_;
    Var I0;
    Var z;
    if (fabs(moneyness.value) < 1e-15) {
        I0 = sigma0_ * pow(s, beta_);
    }
    else {
        if (beta_.value > 1 - 1e-14) {
            z = alpha_ * moneyness / sigma0_;
    }
        else {
            z = alpha_ / sigma0_ * (pow(s, 1.0 - beta_) - pow(shifted_strike, 1.0 - beta_)) / (1.0 - beta_);
        }
        Var in_sqrt = 1.0 - 2.0 * rho_ * z + z * z;
        I0 = moneyness * alpha_ / log((sqrt(in_sqrt) + z - rho_) / (1.0 - rho_));
    }
    
    
    Var I1_term_1 = ((beta_ * beta_ - 2.0 * beta_) * sigma0_ * sigma0_) / (24.0 * pow((shifted_strike + s) / 2.0, 2.0 * (1.0 - beta_)));
    Var I1_term_2 = (rho_ * alpha_ * sigma0_ * beta_) / (4.0 * pow((shifted_strike + s) / 2.0, 1.0 - beta_));
    Var I1_term_3 = ((2.0 - 3.0 * rho_ * rho_) * alpha_ * alpha_) / 24.0;

    Var I1 = I1_term_1 + I1_term_2 + I1_term_3;

    return I0 * (1.0 + I1 * time_to_expiry_);

}

