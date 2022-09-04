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
        ShiftedSABR(Var forward, Var time_to_expiry, Var alpha, Var beta, Var rho, Var zeta, Var sigma0);
        Var operator()(Var strike);
        Var forward_;
        Var time_to_expiry_;

    private:
        Var alpha_;
        Var beta_;
        Var rho_;
        Var zeta_;
        Var sigma0_;
        Tape* tape_;

};