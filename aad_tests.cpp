#include <iostream>
#include <cmath>
#include <cassert>
#include "aad.hpp"

void test_aad() {
    Tape t;
    auto x = t.var(0.5);
    auto y = t.var(4.0);
    auto z1 = x * y;
    auto z2 = pow(y, x);

    Grad grad1 = z1.grad();
    Grad grad2 = z2.grad();
    auto dz1dx = grad1.wrt(x);
    auto dz1dy = grad1.wrt(y);
    auto dz2dx = grad2.wrt(x);
    auto dz2dy = grad2.wrt(y);

    assert(fabs(dz1dx - 4.0) < 1e-15);
    assert(fabs(dz1dy - 0.5) < 1e-15);
    assert(fabs(dz2dy - 1 / (2 * sqrt(y.value))) < 1e-15);
    assert(fabs(dz2dx - (log(x) * z2).value) < 1e-15);

    return;
}

int main() {
    test_aad();
    std::cout << "Test passed" << "\n";
    return 0;
}