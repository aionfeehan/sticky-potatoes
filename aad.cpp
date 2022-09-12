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

Var operator+(const Var& x, const Var& y) {
    assert(x.tape == y.tape);
    return { .tape = x.tape, .index = x.tape->push2(x.index, 1, y.index, 1), .value = x.value + y.value };
}

Var operator+(double x, const Var& y) {
    Var var_x = y.tape->var(x);
    return var_x + y;
}

Var operator+(const Var& x, double y) {
    Var var_y = x.tape->var(y);
    return x + var_y;
}

Var operator-(const Var& x, const Var& y) {
    assert(x.tape == y.tape);
    return { .tape = x.tape, .index = x.tape->push2(x.index, 1, y.index, -1), .value = x.value - y.value };
}

Var operator-(double x, const Var& y) {
    Var var_x = y.tape->var(x);
    return var_x - y;
}

Var operator-(const Var& x, double y) {
    Var var_y = x.tape->var(y);
    return x - var_y;
}

Var operator*(const Var& x, const Var& y) {
    assert(x.tape == y.tape);
    return { .tape = x.tape, .index = x.tape->push2(x.index, y.value, y.index, x.value), .value = x.value * y.value };
}

Var operator*(double x, const Var& y) {
    Var var_x = y.tape->var(x);
    return var_x * y;
}

Var operator*(const Var& x, double y) {
    Var var_y = x.tape->var(y);
    return x * var_y;
}

Var operator/(const Var& x, const Var& y) {
    assert(x.tape == y.tape);
    return { .tape = x.tape, .index = x.tape->push2(x.index, 1.0 / y.value, y.index, - x.value / (y.value * y.value)), .value = x.value / y.value };
}

Var operator/(double x, const Var& y) {
    Var var_x = y.tape->var(x);
    return var_x / y;
}

Var operator/(const Var& x, double y) {
    Var var_y = x.tape->var(y);
    return x / var_y;
}

Var exp(const Var& x) {
    return { .tape = x.tape, .index = x.tape->push1(x.index, std::exp(x.value)), .value = std::exp(x.value) };
}

Var log(const Var& x) {
    return {.tape = x.tape, .index = x.tape->push1(x.index, 1 / x.value), .value = std::log(x.value) };
}

Var pow(const Var& x, const Var& y) {
    assert(x.tape == y.tape);
    return exp(y * log(x));
}

Var pow(const Var& x, double y) {
    Var var_y = x.tape->var(y);
    return pow(x, var_y);
}

Var sqrt(const Var& x) {
    return pow(x, 0.5);
}

double Grad::wrt(const Var& var) {
    return derivs_[var.index];
}

Grad Var::grad() {
    auto& nodes = tape->nodes_;
    std::array<double, TAPE_SIZE> derivs = { 0 };
    derivs[index] = 1.0;

    for (size_t k = 0; k <= index; k++) {
        size_t i = index - k;
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
    node_index_++;
    nodes_[node_index_] = std::move(Node({0, 0}, {1, 1}));
    return node_index_;
}

size_t Tape::push1(size_t parent, double weight) {
    node_index_++;
    nodes_[node_index_] = std::move(Node({ weight, 0 }, { parent, 1 }));
    return node_index_;
}

size_t Tape::push2(size_t parent_1, double weight_1, size_t parent_2, double weight_2) {
    node_index_++;
    nodes_[node_index_] = std::move(Node({ weight_1, weight_2 }, { parent_1, parent_2 }));
    return node_index_;
}

size_t Tape::len(){ return node_index_; }