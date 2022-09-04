#include <iostream>
#include <cmath>
#include <cassert>
#include "aad.hpp"
#include "aad_tests.hpp"

void aad_tests::test_aad() {
    Tape t;
    auto x = t.var(9.0);
    auto y = t.var(0.5);
    auto z1 = x * y;
    auto z2 = pow(x, y);

    Grad grad1 = z1.grad();
    Grad grad2 = z2.grad();
    auto dz1dx = grad1.wrt(x);
    auto dz1dy = grad1.wrt(y);
    auto dz2dx = grad2.wrt(x);
    auto dz2dy = grad2.wrt(y);

    assert(fabs(dz1dx - y.value) < 1e-15);
    assert(fabs(dz1dy - x.value) < 1e-15);    
    assert(fabs(dz2dy - (log(x) * z2).value) < 1e-15);
    assert(fabs(dz2dx - 1 / (2 * z2.value)) < 1e-15);

    return;
}