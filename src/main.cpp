#include <iostream>
#include <string>

#include "hybridcompressor/HybridCompressor.h"

int main() {
    std::string html = "<div><p>Hello</p><span>World</span></div>";



    hc::Parser parser(html);
    auto root = parser.parse();

    //
    // const std::string input = R"(<div class="a">  hi  </div>)";
    // const std::string expected = R"(<div class="a">hi</div>)";

    // try {
    //     hc::HybridCompressor compressor;
    //     const std::string output = compressor.compress(input);
    //
    //     if (output != expected) {
    //         std::cerr << "[SMOKE TEST FAILED]\n";
    //         return 1;
    //     }
    //
    //     std::cout << "[SMOKE TEST PASSED]\n";
    //
    //     std::cout << "--- Starting Parser Test ---" << std::endl;
    //
    //     std::string html = "Hello World";
    //
    //     hc::Parser parser(html);
    //     auto root = parser.parse();
    //
    //     std::cout << "Root children: " << root->children.size() << std::endl;
    //     std::cout << "--- Parser Finished ---" << std::endl;
    //
    //     return 0;
    // } catch (std::exception &e) {
    //     std::cerr << "[SMOKE TEST EXCEPTION] " << e.what() << "\n";
    //     return 2;
    // }
}
