#include "CodeTree.hpp"

Node::~Node(){
    // std::cout << "Hello" << std::endl;
}

Leaf::Leaf(std::uint32_t smbl):
    symbol(smbl){}


// 这个构造函数的形参是个右值引用，函数调用时实参要传入右值（临时对象），如果是左值要move，但是在函数体里实际使用时，
// 这个右值引用的形参在使用时会变成左值（因为临时对象在传递过程中变成了命名对象）
InternalNode::InternalNode(std::unique_ptr<Node> &&left, std::unique_ptr<Node> &&right):
    leftChild(std::move(left)), 
    rightChild(std::move(right)){}

CodeTree::CodeTree(InternalNode &&treeRoot, std::uint32_t symbolLimit):
        root(std::move(treeRoot)){      // Function of constructor 1/2: filling root field
    if(symbolLimit < 2){
        throw("Too few symbols");
    }
    if(symbolLimit > SIZE_MAX){
        throw("Too many symbols");
    }

    // Init a 2D table with empty(数组的数组/vector的vector)
    // std::vector<char>是外层vector的每一个元素类型，std::vector<char>()是对外层的vector中每一个元素填充一个std::vector<char>()数组
    codesTable = std::vector<std::vector<char> >(symbolLimit, std::vector<char>());


    // Init a temp vetcor for prefix calculate
    std::vector<char> prefix;

    // Build CodeList for find codes of symbol
    // Fill codes in 2D symbol-code table
    // Function of constructor 2/2: fill symbol-code 2D table
    buildCodeTable(&root, prefix);
}

// Main algorithm
void CodeTree::buildCodeTable(Node* node, std::vector<char> &prefix){
    if(dynamic_cast<InternalNode*>(node) != nullptr){
        // Process InternalNode
        const InternalNode* internalNode = dynamic_cast<InternalNode*>(node);

        // left
        prefix.push_back(0);
        buildCodeTable(internalNode->leftChild.get(), prefix);      // carefully use .get() of unique_ptr, the object which pointer point to will be destoryed when unique_ptr be free
        prefix.pop_back();

        // right
        prefix.push_back(1);
        buildCodeTable(internalNode->rightChild.get(), prefix);
        prefix.pop_back();

    }else if(dynamic_cast<Leaf*>(node) != nullptr){
        // Process Leaf
        const Leaf* leaf = dynamic_cast<Leaf*>(node);

        codesTable.at(leaf->symbol) = prefix;       // copy between vectors
    }else{
        throw("Illegal Node Type", __LINE__);
    }
}


const std::vector<char>& CodeTree::getCode(std::uint32_t symbol) const{
    if(codesTable.at(symbol).empty()){
        throw("No codes for given symbol.");
    }else{
        return codesTable.at(symbol);
    }
}