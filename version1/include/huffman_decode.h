#pragma once

#include "huffman_node.h"
#include <fstream>

void huffman_decode(std::ifstream&, const huffman_node*, std::ofstream&);
