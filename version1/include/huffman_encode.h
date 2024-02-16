#pragma once

#include "huffman_node.h"

void huff_encode(const std::map<char,std::deque<bool>>&, std::ifstream&,
                 std::ofstream&);
  
