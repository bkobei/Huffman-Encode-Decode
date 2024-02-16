#include "huffman_encode.h"
#include <bitset>
#include <iostream>
#include <queue>

void huff_encode(const std::map<char,std::deque<bool>>& encoding_map,
                 std::ifstream& infile, std::ofstream& outfile)
{
  // How to add table/tree to file
  const size_t S = 8;
  // std::ofstream outfile("Hello.huf");
  infile.clear(); // clear fail and eof bits
  infile.seekg(0, std::ios::beg); // back to start
  std::bitset<S> buffer;
  char c;
  size_t i=0;

  // Read each character in input text file and move it's encoding into buffer
  while (infile >> std::noskipws >> c)
  {
    for (auto a: encoding_map.at(c))
    {
      buffer[0] = a;
      
      ++i;
      // If buffer is full: write buffer to binary file, clear buffer, and set i=0
      if (i >= buffer.size())
      {
        outfile.write((char*)&buffer, 1);
        i=0;
        buffer.set();
      }
      else
      {
        buffer <<= 1;
      } 
    }
  }

  // Add eof to end of binary file
  for (auto a: encoding_map.at(3))
  {
    buffer[0] = a;
    ++i;
    if (i >= buffer.size())
    {
      outfile.write((char*)&buffer, 1);
      i=0;
      buffer.set();
    }
    else
    {
      buffer <<= 1;
    }
    
  }

  if (i != S)
  {
    buffer <<= S-1-i;

    outfile.write((char*)&buffer, 1);
  }

  infile.close(); // Close the original text file
  
  //return outfile;
  /*
  
  */  
}
