/**
 * class Node{};    abstruct class
 * 
 * class Leaf{};    inherit Node class
 * 
 * class InternalNode{};    inherit Node class
 * 
 * class CodeTree{
 * Functions:
 * 1. Constructor: construct a 'tree' which contains 1.) root of tree and 2.)Symbol-Code 2D table for find code of character
 * 2. buildCodeList: Implement function of buliding Symbol-Code 2D table
 * 3. getCode: Get code of symbol which return by vector<char>  
 * } 
*/

#include <vector>
#include <memory>


// pure virtaul function -- if you don't want implement any meaningful content in the virtal funcion but implement content in inherit class: 
// virtual func() = 0;
class Node{
    public: virtual ~Node() = 0;
};


// final: 1.类名后表示该类无法继承 2.方法名后表示方法无法被重写override
class Leaf final : public Node {
    // data field -- symbol
    public: std::uint32_t symbol;

    // constructor
    public: explicit Leaf(std::uint32_t smbl);
};

class InternalNode final : public Node{
    // data field -- child pointer
    public: std::unique_ptr<Node> leftChild;
    public: std::unique_ptr<Node> rightChild;

    // Constructor -- filling pointer on children of InternalNode data field
    public: explicit InternalNode(std::unique_ptr<Node> &&left, std::unique_ptr<Node> &&right);
};

class CodeTree final{
    // data field
    public: InternalNode root;
    private: std::vector<std::vector<char> > codesTable;      // 2D symbol-code table

    // Constructor
    public: explicit CodeTree(InternalNode &&treeRoot, std::uint32_t symbolLimit);        // type of tree root is InternalNode

    // fill codes into 2D symbol-codes table by travels the whole tree <Mention: travels by recursion>
    public: CodeTree buildCodeTable(Node* node, std::vector<char> &prefix);


    // get codes of symbol
    public: const std::vector<char>& getCode(std::uint32_t symbol) const;
};


// 成员函数形参后的const：
// this指针本来就是const指针（常量指针），指向不能被再次修改，但是this指向对象没做const要求，此时this指针不能指向const对象，
// 因为this指向对象要求是非const(可更改的)，但const对象不能更改。但如果按照作者文中给形参后加const表示this指向对象也要求是const对象，
// 这时this指针可以指向非const对象，此时把非const对象看做是const对象。指向const对象的指针本来就是把指向对象当成const常量的一种指针，
// 是他的一种“自以为是”
// 如果是指向非const对象的指针指向了const对象，那么操作这个指针不断修改指向这个const对象的值不是与const对象const的要求冲突了吗

// const int v = 10;
// int *p1 = &v;   // 不合法
// const *p2 = &v;  // 合法

// 使用效果：
// 1. 如果成员函数形参后不加const，则不能使用const对象调用该方法，加上const后，既可以使用const对象调用该方法，也可以使用非const对象调用
// 2. 同时告诉编译器：该方法不应该改变成员变量
// 除了一种情况不适用于上述规则：使用了mutable关键字，形参后有const的函数可以修改成员变量

// Ref:
// https://www.cnblogs.com/yongdaimi/p/9565996.html
// https://stackoverflow.com/questions/2157458/using-const-in-classs-functions