#include "huffman_decode.h"
#include <iostream>
#include <bitset>

void huffman_decode(std::ifstream& infile, const huffman_node* h_node,
                    std::ofstream& outfile)
{
  const size_t S = 8;
  std::bitset<S> buffer;
  infile.seekg(0, std::ios::beg); // Start of file
  // std::cout << "Buffer from .huf file\n"
  //          << "=====================\n";
  auto copy = h_node;
  while (infile)
  {
    infile.read((char*)&buffer, 1);

    // Check if buffer is same as before
    // std::cout << buffer;
  
    // std::cout << buffer << '\n';
    bool done = false;
    size_t a = buffer.size();
    while(!done && (a>0))
    {
      if (copy->letter == 3)
      {
        done = true;
        continue;
      }
      if (copy->letter != 0)
      {
        // std::cout << copy->letter;
        outfile << copy->letter;
        copy = h_node;
      }

    
    
      if (buffer[a-1])
      {
        copy = copy->right;
      }
      else
      {
        copy = copy->left;
      }

      --a;

    }

    buffer.set();
  }

  std::cout << '\n';
  
  infile.close();
  outfile.close();
}
