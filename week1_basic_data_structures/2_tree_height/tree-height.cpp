#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

//#define DEBUG ;

class Node;

class Node {
public:
    int key;
    Node *parent;
    std::vector<Node *> children;

    Node() {
      this->parent = NULL;
    }

    void setParent(Node *theParent) {
      parent = theParent;
      parent->children.push_back(this);
    }
};


void test_solution(){
  std::ios_base::sync_with_stdio(0);
  int root; // To store the index corresponding to the root
  int n = 100;
/*  int inputarray[] = {96,61,95,34,12,26,48,42,69,74,90,67,8,53,65,0,14,47,88,8,49,4,93,75,6,29,-1,
                      62,87,12,42,52,1,46,4,83,14,75,72,95,15,86,29,53,85,78,65,31,5,96,6,74,87,24,
                      15,90,22,85,20,46,78,97,50,97,69,19,21,61,92,5,22,47,63,1,93,28,20,34,52,21,72,
                      88,67,0,86,49,63,48,28,25,50,83,31,19,62,24,64,64,92,25};*/
  int inputarray[] = {3,57,29,54,29,94,88,57,40,16,72,16,80,63,89,4,77,77,16,65,72,14,94,82,80,49,69,54,
                      1,99,50,18,52,36,49,50,80,42,89,31,4,52,52,77,88,42,97,73,73,82,88,37,69,63,40,99,
                      36,76,1,37,28,57,82,93,54,63,76,14,18,-1,76,42,14,72,97,28,37,65,99,29,97,3,3,93,
                      65,93,89,40,31,36,73,18,4,49,28,69,1,50,31,94};
/*  int n = 5;
  int inputarray[] = {-1, 0, 4, 0, 3};*/

  std::vector<Node> nodes;
  nodes.resize(n);
  for (int child_index = 0; child_index < n; child_index++) {
    int parent_index = inputarray[child_index];
    if (parent_index >= 0)
      nodes[child_index].setParent(&nodes[parent_index]);
    else
      root = child_index;
    nodes[child_index].key = child_index;
  }

  int maxHeight = 1;
  std::stack<Node*> parents_stack;
  parents_stack.push(&nodes[root]);
  if(parents_stack.top()->children.size() == 0){  // in case there is only one node
    std::cout << maxHeight << std::endl;
    return;
  }

  bool termination_condition;
  do{
    Node* current_node = parents_stack.top();
    static std::vector<int> node_children_counter(n,0);
    if (node_children_counter[current_node->key] == current_node->children.size()){
      parents_stack.pop();
      node_children_counter[parents_stack.top()->key]++;
    }
    else{
      Node* current_children = current_node->children[node_children_counter[current_node->key]];
      if (current_children->children.size() != 0 && parents_stack.top()!=current_children){  // the children itself has children
        parents_stack.push(current_children);
      }
      else{ // if no children then evaluate the height
        int height = parents_stack.size() + 1;
        if (height > maxHeight)
          maxHeight = height;
        node_children_counter[current_node->key] ++;
        if (node_children_counter[current_node->key] == current_node->children.size()){
          if (current_node->key != root)
            parents_stack.pop();
          else
            break;
          node_children_counter[parents_stack.top()->key]++;
        }
      }
    }
    termination_condition = node_children_counter[root] < nodes[root].children.size();
    //std::cout << maxHeight << std::endl;
  }while(termination_condition); //parents_stack.size()>1 ||

  std::cout << maxHeight << std::endl;
}


int main_with_large_stack_space() {
#ifdef DEBUG
  test_solution();
#else
  std::ios_base::sync_with_stdio(0);
  int n;
  std::cin >> n;
  int root; // To store the index corresponding to the root

  std::vector<Node> nodes;
  nodes.resize(n);
  for (int child_index = 0; child_index < n; child_index++) {
    int parent_index;
    std::cin >> parent_index;
    if (parent_index >= 0)
      nodes[child_index].setParent(&nodes[parent_index]);
    else
      root = child_index;
    nodes[child_index].key = child_index;
  }

  /*/ Replace this code with a faster implementation
  int maxHeight = 0;
  for (int leaf_index = 0; leaf_index < n; leaf_index++) {
    int height = 0;
    for (Node *v = &nodes[leaf_index]; v != NULL; v = v->parent)
      height++;
    maxHeight = std::max(maxHeight, height);
  }
  */// Own implementation
  int maxHeight = 1;
  std::stack<Node*> parents_stack;
  parents_stack.push(&nodes[root]);
  if(parents_stack.top()->children.size() == 0){  // in case there is only one node
    std::cout << maxHeight << std::endl;
    return 0;
  }

  bool termination_condition;
  do{
    Node* current_node = parents_stack.top();
    static std::vector<int> node_children_counter(n,0);
    if (node_children_counter[current_node->key] == current_node->children.size()){
      parents_stack.pop();
      node_children_counter[parents_stack.top()->key]++;
    }
    else{
      Node* current_children = current_node->children[node_children_counter[current_node->key]];
      if (current_children->children.size() != 0 && parents_stack.top()!=current_children){  // the children itself has children
        parents_stack.push(current_children);
      }
      else{ // if no children then evaluate the height
        int height = parents_stack.size() + 1;
        if (height > maxHeight)
          maxHeight = height;
        node_children_counter[current_node->key] ++;
        if (node_children_counter[current_node->key] == current_node->children.size()){
          if (current_node->key != root)
            parents_stack.pop();
          else
            break;
          node_children_counter[parents_stack.top()->key]++;
        }
      }
    }
    termination_condition = node_children_counter[root] < nodes[root].children.size();
    //std::cout << maxHeight << std::endl;
  }while(termination_condition); //parents_stack.size()>1 ||

  std::cout << maxHeight << std::endl;
  return 0;
#endif
}

int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0)
  {
      if (rl.rlim_cur < kStackSize)
      {
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if (result != 0)
          {
              std::cerr << "setrlimit returned result = " << result << std::endl;
          }
      }
  }

#endif
  return main_with_large_stack_space();
}
