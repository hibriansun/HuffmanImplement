#include <vector>
#include "CodeTree.hpp"

class FrequencyTable{
    // Frequency Table
    private: std::vector<uint32_t> frequencies;

    // Constructor
    public: explicit FrequencyTable(const std::vector<std::uint32_t> &freqs);

    // Filling Frequency Table
    void increment(std::uint32_t symbol);

    // Construct a huffman tree and its Symbol-Code 2D table which are contained in CodeTree instance
    CodeTree buildCodeTree() const;
    // 这里的const是强行将调用对象指针转成const指针，再赋值给this指针（this指针是个const指针，你不能让const指针指向一个非const对象）
};