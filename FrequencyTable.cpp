#include "FrequencyTable.hpp"


FrequencyTable::FrequencyTable(const std::vector<uint32_t> &freqs):
    frequencies(freqs) {};

void FrequencyTable::increment(uint32_t symbol){
    if(frequencies.at(symbol) == UINT32_MAX){
        throw std::overflow_error("Max range of uint32_t reached.");
    }
    frequencies.at(symbol)++;
}

CodeTree FrequencyTable::buildCodeTree() const{
    
}