#include "huffman_node.h"
#include "huffman_encode.h"
#include <queue>
#include <algorithm>
#include <vector>
#include <deque>
#include <string>
#include <cstdio>

// Function forms a frequency distribution map 
void freq_dist_from_file(std::map<char,int>& frequency,
                         std::ifstream& input_file)
{
  char c;
  // Read characters in input_file and store frequency of characters in map
  while (input_file >> std::noskipws >> c) // Read the text file
  {
    frequency[c]++;
  }

  // For edge case when there is 1 character in the file
  char end_of_file = 3;
  frequency[end_of_file] = 1;
}

// Function that joins two trees into one with priority of sum of frequency of two trees
huffman_node* join(huffman_node* L, huffman_node* R)
{
  huffman_node* A = new huffman_node {L->priority + R->priority};
  A->left = L;
  A->right = R;
  return A;
}

// Function builds a huffman tree from the frequency map
void build_huffman_tree(huffman_node*& my_tree, const std::map<char,int>& freq_dist)
{
  // Priority queue for pushing nodes with higher priority to front
  //   (higher priority == low frequency)
  std::priority_queue<huffman_node*, std::vector<huffman_node*>, huffman_less> Q;
  
  for (auto p: freq_dist)
  {
    huffman_node* N = new huffman_node {p.second, p.first};
    Q.push(N);
  }

  std::cout << std::endl;

  // Create the tree
  while (!(Q.size() == 1))
  {
    auto A = Q.top();
    Q.pop();
    auto B = Q.top();
    Q.pop();
    huffman_node* N = join(A,B);
    Q.push(N);
  }

  my_tree = Q.top();
}

// Recursive function that stores the encoding for each leaf node in a map
// using postorder traversal
void store_encoding(const huffman_node* h_node, std::deque<bool>& deq,
                    std::map<char, std::deque<bool>>& encoding)
{
  // Idea: Create a recursive function that visits all nodes and
  //       stores encoding of its corresponding leaf node
  // =========== This idea used in the recursive function ============
  /* recursive store(const huffman_node* h_node, map<char,
   * string>& encoding_map, deque deq)
   * {
   *   if (h_node == NULL) return;
   *   push 0 to back of deq when visit left tree
   *   store(h_node->left, encoding_map, deq);
   *   pop_back 0 from deq then push 1 to back of deq when visiti right tree
   *   store(h_node->right, encoding_map, deq);
   *   // if L and R of h_node are NULL, store encoding of h_node in map
   *   if (h_node->letter != 0)
   *     store encoding in the encoding map
   *     // Needs loop for this version of the code
   *     encoding_map[h_node->letter] = encoding;
   */
  
  if (h_node == nullptr) return; // Return to leaf when null

  // Visit left subtree
  deq.push_back(0);
  store_encoding(h_node->left, deq, encoding);
  deq.pop_back();

  // Visit right subtree
  deq.push_back(1);
  store_encoding(h_node->right, deq, encoding);
  deq.pop_back();

  // If char != 0, store string of encoding to corresponding char
  if (h_node->letter != 0)
  {
    std::deque<bool> d;
    // 
    for (auto i: deq)
    {
      d.push_back(i);
    }

    // Save encoding to corresponding symbol
    encoding[h_node->letter] = d;
  }
}
  
// Function prints a table displaying the frequency and encoding of each character
void test_print_dist(const std::map<char,int>& freq, const huffman_node* h_node,
                     std::map<char, std::deque<bool>>& encoding_storage)
{
  std::cout << "Characters\t\tFrequency\t\tEncoding\n";
  std::cout << "===================================\n";
  
  std::deque<bool> deq;
  
  store_encoding(h_node, deq, encoding_storage); // Recursive function
  // This works, postorder recursive print also works

  // The following is for printing the table
  for (auto i: freq)
  {
    if (i.first == 3)
      std::cout << "end_of_file\t\t";
    else if (i.first == 10)
      std::cout << "new_line\t\t\t";
    else if (i.first == 32)
      std::cout << "space\t\t\t\t\t";
    else
      std::cout << i.first << "\t\t\t\t\t\t\t";

    
    if (i.second < 10)
      std::printf("%d\t\t\t\t\t\t", i.second);
    else if (i.second < 1000)
      std::printf("%d\t\t\t\t\t", i.second);
    else
      std::printf("%d\t\t\t\t", i.second);

    for (auto j: encoding_storage[i.first])
      std::cout << j;

    std::cout << '\n';
    // std::cout << encoding_storage[i.first] << '\n';
    
  }
}
