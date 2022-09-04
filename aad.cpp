/**
 * @file aad.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include "aad.hpp"

Var operator+(Var x, Var y) {
    assert(x.tape == y.tape);
    return { .tape = x.tape, .index = x.tape->push2(x.index, 1, y.index, 1), .value = x.value + y.value };
}

Var operator+(double x, Var y) {
    Var var_x = y.tape->var(x);
    return var_x + y;
}

Var operator+(Var x, double y) {
    Var var_y = x.tape->var(y);
    return x + var_y;
}

Var operator-(Var x, Var y) {
    assert(x.tape == y.tape);
    return { .tape = x.tape, .index = x.tape->push2(x.index, 1, y.index, -1), .value = x.value - y.value };
}

Var operator-(double x, Var y) {
    Var var_x = y.tape->var(x);
    return var_x - y;
}

Var operator-(Var x, double y) {
    Var var_y = x.tape->var(y);
    return x - var_y;
}

Var operator*(Var x, Var y) {
    assert(x.tape == y.tape);
    return { .tape = x.tape, .index = x.tape->push2(x.index, y.value, y.index, x.value), .value = x.value * y.value };
}

Var operator*(double x, Var y) {
    Var var_x = y.tape->var(x);
    return var_x * y;
}

Var operator*(Var x, double y) {
    Var var_y = x.tape->var(y);
    return x * var_y;
}

Var operator/(Var x, Var y) {
    assert(x.tape == y.tape);
    return { .tape = x.tape, .index = x.tape->push2(x.index, 1.0 / y.value, y.index, - x.value / (y.value * y.value)), .value = x.value / y.value };
}

Var operator/(double x, Var y) {
    Var var_x = y.tape->var(x);
    return var_x / y;
}

Var operator/(Var x, double y) {
    Var var_y = x.tape->var(y);
    return x / var_y;
}

Var exp(Var x) {
    return { .tape = x.tape, .index = x.tape->push1(x.index, std::exp(x.value)), .value = std::exp(x.value) };
}

Var log(Var x) {
    return {.tape = x.tape, .index = x.tape->push1(x.index, 1 / x.value), .value = std::log(x.value) };
}

Var pow(Var x, Var y) {
    assert(x.tape == y.tape);
    return exp(y * log(x));
}

Var pow(Var x, double y) {
    Var var_y = x.tape->var(y);
    return pow(x, var_y);
}

Var sqrt(Var x) {
    return pow(x, 0.5);
}

double Grad::wrt(const Var& var) {
    return derivs_[var.index];
}

Grad Var::grad() {
    auto len = tape->len();
    auto& nodes = tape->nodes_;
    auto derivs = std::vector<double>(len);
    derivs[index] = 1.0;

    for (size_t k = 0; k < len; k++) {
        size_t i = len - k - 1;
        auto const& node = nodes[i];
        auto deriv = derivs[i];

        for (size_t j = 0; j < 2; j++) {
            derivs[node.parents[j]] += node.weights[j] * deriv;
        }
    }

    return Grad{ std::move(derivs) };
}

Var Tape::var(double value) {
    return { .tape = this, .index = push0(), .value = value };
}

size_t Tape::push0() {
    auto l = len();
    nodes_.push_back({ .weights = {0, 0}, .parents = {1, 1} });
    return l;
}

size_t Tape::push1(size_t parent, double weight) {
    auto l = len();
    nodes_.push_back({ .weights = {weight, 0}, .parents = {parent, 1} });
    return l;
}

size_t Tape::push2(size_t parent_1, double weight_1, size_t parent_2, double weight_2) {
    auto l = len();
    nodes_.push_back({ .weights = {weight_1, weight_2}, .parents = {parent_1, parent_2} });
    return l;
}

size_t Tape::len(){ return nodes_.size(); }