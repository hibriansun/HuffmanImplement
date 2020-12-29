#include <queue>
#include "FrequencyTable.hpp"


FrequencyTable::FrequencyTable(const std::vector<uint32_t> &freqs):
    frequencies(freqs) {};

void FrequencyTable::increment(uint32_t symbol){
    if(frequencies.at(symbol) == UINT32_MAX){
        throw std::overflow_error("Max range of uint32_t reached.");
    }
    frequencies.at(symbol)++;
}


// 内部类的构造方法 -- helper of buildCodeTree
FrequencyTable::NodeWithFrequency::NodeWithFrequency(Node* node, std::uint32_t lowestSymbol, std::uint32_t frequency):
    node(std::unique_ptr<Node>(node)),
    lowestSymbol(lowestSymbol),
    frequency(frequency){}


// 自定义优先队列排序方法：先看权重(frequency)，小者在前，当权重相同时比较lowestsymbol值，小者在前
// 默认的less比较法：first > second 返回 true
bool FrequencyTable::NodeWithFrequency::operator<(const NodeWithFrequency &other) const{
    if(frequency > other.frequency){
        return true;
    } else if (frequency < other.frequency)
		return false;
	else if (lowestSymbol > other.lowestSymbol)
		return true;
	else if (lowestSymbol < other.lowestSymbol)
		return false;
	else
		return false;
}


// Main algorithm
CodeTree FrequencyTable::buildCodeTree() const{
    // 建立优先队列， 对frequency table 扫描入队备用
    std::priority_queue<NodeWithFrequency> queue;

    // 入队非0
    uint32_t i = 0;
    for(std::uint32_t tmp: frequencies){
        if(tmp > 0){
            // 在栈上创建一个NodeWithFrequency对象，这个对象成员Node* node是在堆上new出来的
            queue.push(NodeWithFrequency(new Leaf(i), i, tmp));     // Tip new出来的对象在堆上，需要手动管理，其返回一个指向对象的指针，直接定义对象是在栈上
        }
        i++;
    }

    // 当队中元素<2补frequency为0节点以满足建树所需的两两合并
    if(queue.size() < 2){
        uint32_t j = 0;
        for(std::uint32_t tmp: frequencies){
            if(queue.size() == 2){
                break;
            }
            if(tmp == 0){
                queue.push(NodeWithFrequency(new Leaf(j), j, tmp));
            }
            j++;
        }
    }

    // 利用刚建好的优先队列，辅助NodeWithFrequency，建立哈夫曼树
    while(queue.size() > 1){        // 队列中留下一个root
        // 坑：queue、priority_queue的pop都是void pop();不返回被pop出元素
        NodeWithFrequency a = myPop(queue);
        NodeWithFrequency b = myPop(queue);

        queue.push(NodeWithFrequency(new InternalNode(std::move(a.node), std::move(b.node)), std::min(a.lowestSymbol, b.lowestSymbol), a.frequency+b.frequency));
    }

    // 传入相关参数让CodeTree构造器构造内含symbol-code表和树root，释放临时建的NodeWithFrequency为节点的树，返回CodeTree对象
    NodeWithFrequency root = myPop(queue);
    InternalNode* rootNode = dynamic_cast<InternalNode*>(root.node.release());
    CodeTree rst(std::move(*rootNode), frequencies.size());
    delete rootNode;    // 手动处理裸指针,不delete不会自动释放QAQ
    return rst;
}


FrequencyTable::NodeWithFrequency FrequencyTable::myPop(std::priority_queue<FrequencyTable::NodeWithFrequency> &queue){
    FrequencyTable::NodeWithFrequency tmp = std::move(const_cast<FrequencyTable::NodeWithFrequency&&>(queue.top()));     // 去除const
    queue.pop();
    return tmp;
}
