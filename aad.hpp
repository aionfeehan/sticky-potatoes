/**
 * @file aad.hpp
 * @author your name (you@domain.com)
 * @brief Basic implementation of auto-diff for some standard mathematical operations.
 * @version 0.1
 * @date 2022-09-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include <vector>
#include <cmath>
#include <cassert>

struct Node {
    double weights[2];
    size_t parents[2];
};

struct Var;

class Grad {

    public:
        explicit Grad(std::vector<double>&& derivs): derivs_{derivs}{};
        double wrt(const Var& var);

    private:
        std::vector<double> derivs_;
};


Var operator+(Var x, Var y);
Var operator+(double x, Var y);
Var operator+(Var x, double y);

Var operator-(Var x, Var y);
Var operator-(double x, Var y);
Var operator-(Var x, double y);

Var operator*(Var x, Var y);
Var operator*(double x, Var y);
Var operator*(Var x, double y);

Var operator/(Var x, Var y);
Var operator/(double x, Var y);
Var operator/(Var x, double y);

Var exp(Var x);
Var log(Var x);
Var pow(Var x, Var y);
Var pow(Var x, double y);
Var sqrt(Var x);


class Tape {

    public:
        Tape() {}
        Var var(double value);
        size_t push0();
        size_t push1(size_t parent, double weight);
        size_t push2(size_t parent_1, double weight_1, size_t parent_2, double weight_2);
        size_t len();

    private:
        friend struct Var;
        std::vector<Node> nodes_;

};

struct Var {
    Tape* tape;
    size_t index;
    double value;
    Grad grad();
};
