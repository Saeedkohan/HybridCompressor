# HybridCompressor

![HybridCompressor Banner](/gen?prompt=futuristic+abstract+data+compression+banner+with+c%2B%2B+and+python+logos+merging+dark+blue+and+neon+green+lighting+tech+style&aspect=16:9)

**High-Performance Next-Gen HTML Parser & Minifier Engine**
*Powered by Modern C++ Core with Seamless Python Bindings via Pybind11*

![C++](https://img.shields.io/badge/C%2B%2B-20-blue.svg?style=for-the-badge&logo=c%2B%2B)
![Python](https://img.shields.io/badge/Python-3.8%2B-yellow.svg?style=for-the-badge&logo=python)
![CMake](https://img.shields.io/badge/Build-CMake-green.svg?style=for-the-badge&logo=cmake)
![License](https://img.shields.io/badge/License-MIT-orange.svg?style=for-the-badge)

---

## 📖 About The Project
**HybridCompressor** is a dual-layer library designed to bridge the raw performance and memory management control of **C++** with the flexibility of **Python**.
It aims to solve the performance bottlenecks of pure Python parsers (like BeautifulSoup) by offloading the heavy lifting—lexical analysis, parsing, and DOM manipulation—to a highly optimized native engine.

Currently, it features a robust **Recursive Descent Parser** that builds a custom Abstract Syntax Tree (AST) and performs efficient text minification.

## 🏗 System Architecture
The project follows a classic compiler design pipeline, ensuring modularity and ease of debugging.

![Architecture Diagram](/gen?prompt=minimalist+diagram+flowchart+of+compiler+design+showing+lexer+to+parser+to+ast+tree+to+output+on+dark+background&aspect=16:9)

*   **Lexer (Tokenizer):** Reads the raw input stream and generates atomic `Token` objects (StartTag, EndTag, Text, Attributes). It handles state transitions internally.
*   **Parser:** Consumes tokens and constructs the **AST** (Abstract Syntax Tree) using the Recursive Descent algorithm. It validates the HTML structure on the fly.
*   **AST (DOM):** A hierarchical tree structure where each node (Element, Text, Comment) is managed via `std::shared_ptr` for automatic memory management.
*   **Compressor (Facade):** The high-level interface that coordinates the parsing and traversing process to produce minified output.
*   **Python Native Interface:** Exposed via `pybind11`, allowing Python code to interact with C++ objects directly.

## ✨ Current Features
*   🚀 **Custom Tokenizer:** Handles HTML5 specific tags, self-closing tags, and attributes.
*   🌳 **Memory-Safe AST:** Uses smart pointers to prevent memory leaks during complex tree manipulations.
*   📄 **Text Minification:** Intelligent whitespace collapsing within text nodes.
*   🐍 **Direct Python Bindings:** No intermediate file I/O; data passes directly from Python memory to C++ engine.
*   🛡️ **Robust Error Handling:** Gracefully handles unexpected tokens (currently in strict mode).

## 🔮 Future Roadmap (Planned)
We are actively working on version 2.0 with these advanced capabilities:

![Multithreading](/gen?prompt=abstract+visualization+of+multi-threaded+cpu+processing+glowing+parallel+lines+speed+motion+blur+cyberpunk+style&aspect=16:9)

*   **Multithreading Support:** Releasing the Python GIL to allow parallel parsing of multiple documents on multi-core CPUs.
*   **Binary Serialization:** Ability to save/load the parsed AST to a binary format (e.g., FlatBuffers) for caching.
*   **Streaming API:** Processing massive HTML files (GB+) without loading the entire document into RAM.

## 🚀 Installation & Usage

### Prerequisites
*   C++ Compiler supporting C++17 or later.
*   CMake 3.15+
*   Python 3.8+

### Building from Source
```bash
git clone https://github.com/YourUsername/HybridCompressor.git
cd HybridCompressor
pip install .
```

### Python Usage Example
```python
import hybridcompressor as hc

html_content = """
<div class="container">
    <h1>  Hello   World  </h1>
    <!-- This is a comment -->
</div>
"""

# Initialize the C++ engine
compressor = hc.HybridCompressor()

# Compress HTML (Parsing -> Minifying -> Stringifying)
minified = compressor.compress(html_content)

print(minified)
# Output: <div class="container"><h1>Hello World</h1></div>
```

## 📂 Project Structure
```text
HybridCompressor/
├── include/              # Header files (Core API)
│   └── hybridcompressor/
│       ├── ASTNode.h     # Tree Data Structure
│       ├── Lexer.h       # Tokenization Logic
│       ├── Parser.h      # Recursive Descent Parser
│       └── Token.h       # Atomic Units
├── src/                  # C++ Implementation (.cpp)
├── python/               # Pybind11 bindings & module setup
└── CMakeLists.txt        # Build configuration
```
