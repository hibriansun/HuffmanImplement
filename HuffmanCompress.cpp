/**
 * I. 建树
 * 1. 统计输入文本字符频率：建立FrequencyTable对象，利用桶排思想对该对象的的frequencies频率统计表进行填充<注意手动填充EOF>
 * 2. 建成一棵哈夫曼树：使用FrequencyTable对象的buildCodeTree方法，返回一个CodeTree对象'code'<CodeTree字段：二维寻码表&哈夫曼树根>
 * 3. 根据哈夫曼树和字符范围转化成一棵范式哈夫曼树：先根据2中返回的CodeTree对象code建立最终要写入文件的CanonicalCode对象的Symbol-Length表，
 *    再调用该类中toCodeTree方法构造出一棵类型为CodeTree的范式哈夫曼树替换原有'code'
 * 
 * II. 压缩：存树（实际存Symbol-Length表解压时再构造）编码写入文件
 * 1. 存储Symbol-Length表<根据CanonicalCode对象>
 * 2. 传入范式哈夫曼树以构造编码器Encoder，对正文字符编码并存储
 * 
*/

#include <iostream>
#include <fstream>
#include "HuffmanCompress.hpp"
#include "FrequencyTable.hpp"

int main(int argc, char** argv){
    // Handle illegal arguments
    if(argc != 3){
        std::cerr << "Usage:" << argv[0] << " InputFile OutputFile" << std::endl; 
        exit(0);
    }

    char* inputFile = argv[1];
    char* outputFile = argv[2];

    // Initailze file stream
    std::ifstream in(inputFile, std::ios::binary);
    std::ofstream out(outputFile, std::ios::binary);

    // Counting frequency of symbols
    FrequencyTable freqs(std::vector<uint32_t>(257, 0));
    while(true){
        int tmpChar = in.get();     // Mention: ifstream::get() returns int value not char value
        if(tmpChar == EOF){
            freqs.increment(256);
            break;
        }
    }

    // Build Huffman code tree


}