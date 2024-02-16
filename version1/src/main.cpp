#include "huffman_node.h"
#include "huffman_encode.h"
#include "huffman_decode.h"
#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <deque>
#include <bitset>

int main()
{
  std::ifstream infile("../text/Hello.txt");

  std::string file_name = "Hello";
  if (!infile.is_open())
  {
    std::cout << "File could not be opened!\n";
  }
  else
  {
    std::map<char,int> freq_dist;
    freq_dist_from_file(freq_dist, infile);

    huffman_node* A = new huffman_node {-1}; // Assuming that A is nullptr
    build_huffman_tree(A, freq_dist); // Not sure if works

    std::map<char, std::deque<bool>> encoding_storage;

    test_print_dist(freq_dist, A, encoding_storage);

    std::ofstream outfile("Hello.huf");

    huff_encode(encoding_storage, infile, outfile);
    outfile.close();
    std::ifstream new_infile("Hello.huf");
    if (!new_infile.is_open())
      std::cout << "File could not be opened!\n";
    else
    {
      std::ofstream copy_infile("../text/Hello_copy.txt");

      huffman_decode(new_infile, A, copy_infile);
      // Test writing bitset to output
      /*std::bitset<8> buffer;
    
        for (size_t i=0; i<buffer.size(); ++i)
        std::cout << "buffer[" << i << "]: " << buffer[i] << '\n';

        buffer[0] = true;
        buffer <<= 1;
        std::cout << "buffer is now " << buffer << '\n';*/
    }
  }
}
