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

#include <array>
#include <cassert>
#include <cmath>


struct Node {
    double weights[2];
    size_t parents[2];
};

struct Var;

const size_t TAPE_SIZE = 100;

class Grad {

public:
    explicit Grad(std::array<double, TAPE_SIZE>&& derivs) : derivs_{ derivs } {};
    double wrt(const Var& var);

private:
    std::array<double, TAPE_SIZE> derivs_;
};


Var operator+(const Var& x, const Var& y);
Var operator+(double x, const Var& y);
Var operator+(const Var& x, double y);

Var operator-(const Var& x, const Var& y);
Var operator-(double x, const Var& y);
Var operator-(const Var& x, double y);

Var operator*(const Var& x, const Var& y);
Var operator*(double x, const Var& y);
Var operator*(const Var& x, double y);

Var operator/(const Var& x, const Var& y);
Var operator/(double x, const Var& y);
Var operator/(const Var& x, double y);

Var exp(const Var& x);
Var log(const Var& x);
Var pow(const Var& x, const Var& y);
Var pow(const Var& x, double y);
Var sqrt(const Var& x);


class Tape {

public:
    Tape() { node_index_ = 0; }
    Var var(double value);
    size_t push0();
    size_t push1(size_t parent, double weight);
    size_t push2(size_t parent_1, double weight_1, size_t parent_2, double weight_2);
    size_t len();

private:
    friend struct Var;
    std::array<Node, TAPE_SIZE> nodes_{};
    size_t node_index_;

};

struct Var {
    Tape* tape;
    size_t index;
    double value;
    Grad grad();
};

