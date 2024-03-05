#include <bits/stdc++.h>
#include <sstream>
#include <iomanip>

using namespace std;

std::tuple<int, int, int> hexToRgb(const std::string &hex) {
    std::istringstream iss(hex.substr(1));  // Skip the '#' character
    int r, g, b;
    iss >> std::hex >> r >> g >> b;
    return std::make_tuple(r, g, b);
}

int main() {

    std::string hexColor = "#1A2B3C";
    auto rgb = hexToRgb(hexColor);

    std::cout << "Hex: " << hexColor << std::endl;
    std::cout << "RGB: (" << std::get<0>(rgb) << ", " << std::get<1>(rgb) << ", " << std::get<2>(rgb) << ")"
              << std::endl;
    return 0;
}
