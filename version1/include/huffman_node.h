#pragma once

#include <fstream>
#include <iostream>
#include <map>
#include <deque>

struct huffman_node
{
  int priority;
  char letter = 0;
  huffman_node *left = nullptr, *right = nullptr;
};

struct huffman_less
{
  bool operator()(const huffman_node* A, const huffman_node* B)
  {
    return A->priority > B->priority; // least has highest priority
  }
};

// Function that creates a frequency distribution of all characters in txt file
void freq_dist_from_file(std::map<char,int>&, std::ifstream&);

// Function constructs a Huffman tree from freq distribution
void build_huffman_tree(huffman_node*&, const std::map<char,int>&);

// Function to print a table of Huffman code
void test_print_dist(const std::map<char,int>&, const huffman_node*,
                     std::map<char, std::deque<bool>>&);
