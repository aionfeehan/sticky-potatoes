#include <iostream>

#include "aad_tests.hpp"
#include "shifted_sabr_tests.hpp"

int main() {
    aad_tests::test_aad();
    std::cout << "AAD checks passed" << "\n";
    shifted_sabr_tests::test_shifted_sabr();
    std::cout << "Shifted SABR smile written to test file" << "\n";
    return 0;
}