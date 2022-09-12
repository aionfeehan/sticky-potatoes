/**
 * @file shifted_sabr.hpp
 * @author Aion Feehan (aionfeehan@gmail.com)
 * @brief Auto-diff compatible implementation of Berestycki's shifted SABR approximation
 * @version 0.1
 * @date 2022-09-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include "aad.hpp"

class ShiftedSABR {

    public:
        ShiftedSABR(double forward, double time_to_expiry, double alpha, double beta, double rho, double zeta, double sigma0);
        Var operator()(double strike);
        double forward_;
        double time_to_expiry_;
        Var var_forward_;
        Var var_sigma0_;
        Var var_alpha_;
        Var var_beta_;
        Var var_rho_;
        Var var_zeta_;

    private:
        double alpha_;
        double beta_;
        double rho_;
        double zeta_;
        double sigma0_;

};