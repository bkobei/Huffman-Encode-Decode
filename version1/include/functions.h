#pragma once

#include "huffman_node.h"
#include <fstream>
#include <iostream>
#include <map>

// Function that creates a frequency distribution of all characters in txt file
void freq_dist_from_file(std::map<char,int>&, std::ifstream&);

// Function constructs a Huffman tree from freq distribution
void build_huffman_tree(huffman_node*&, const std::map<char,int>&);

// Function to print a table of Huffman code
void test_print_dist(const std::map<char,int>&, const huffman_node*);

