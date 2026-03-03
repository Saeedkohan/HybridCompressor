#include <iostream>
#include <string>

#include "hybridcompressor/HybridCompressor.h"

int main() {
    const std::string input = R"(<div class="a">  hi  </div>)";
    const std::string expected = R"(<div class="a">hi</div>)";

    try {
        hc::HybridCompressor compressor;
        const std::string output = compressor.compress(input);
        if (output != expected) {
            std::cerr << "[SMOKE TEST FAILED]\n"
                      << "Input:    " << input << "\n"
                      << "Expected: " << expected << "\n"
                      << "Got:      " << output << "\n";
            return 1;
        }
        std::cout << "[SMOKE TEST PASSED]\n";
        return 0;

    }catch (std::exception& e) {
        std::cerr << "[SMOKE TEST EXCEPTION] " << e.what() << "\n";
        return 2;
    }
}