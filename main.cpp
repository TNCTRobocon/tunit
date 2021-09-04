#include "inc/tunit.hpp"
#include <iostream>
using namespace std;

int main() {

    // using namespace tunit::units;
    using namespace tunit;
    auto x = 1000.0 * values::rad / values::s*values::k;
    // sec<float> y(4);
    // rad_per_sec<float> z = x / y;
    // cout << z.rank::e0 << endl;
    // auto z = x++;
    cout << x << endl;
    return 0;
}