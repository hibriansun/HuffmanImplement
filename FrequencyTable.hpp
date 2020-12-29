#pragma once
#include <vector>
#include <queue>
#include "CodeTree.hpp"

class FrequencyTable{
    // Frequency Table
    public: std::vector<uint32_t> frequencies;

    // Constructor
    public: explicit FrequencyTable(const std::vector<std::uint32_t> &freqs);

    // Filling Frequency Table
    public: void increment(std::uint32_t symbol);

    // Construct a huffman tree and its Symbol-Code 2D table which are contained in CodeTree instance
    public: CodeTree buildCodeTree() const;
    // 这里的const是强行将调用对象指针转成const指针，再赋值给this指针（this指针是个const指针，你不能让const指针指向一个非const对象）

    class NodeWithFrequency{
        public: std::unique_ptr<Node> node;
        public: std::uint32_t lowestSymbol;
        public: std::uint32_t frequency;

        public: explicit NodeWithFrequency(Node* node, std::uint32_t lowestSymbol, std::uint32_t frequency);

        // 重载运算操作符 -- 优先队列默认走less小于运算符,默认降序
        public: bool operator<(const NodeWithFrequency &other) const;
    };


    // 坑：queue、priorty_queue的pop都是void pop();不返回被pop出元素
    // 写一个返回被出队元素的pop方法
    // 这是一个类方法 -- static method
    public: static FrequencyTable::NodeWithFrequency myPop(std::priority_queue<NodeWithFrequency> &queue);
};