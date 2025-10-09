#pragma once

#include "Parser.h"
#include "ASTNode.h"
#include <string>

namespace hc {
    class HybridCompressor {
    public:
        HybridCompressor() = default;


        std::string compress(const std::string &input_html);
    };
}
