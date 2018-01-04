#include <algorithm>
#include <iostream>
#include <vector>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#include <array>
#include <stack>
#include <queue> 
#endif

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

  void addChild(Node *theChild){
    this->children.push_back(theChild);
  }

  bool hasChildren(){
    if(!children.empty()){
      return true;
    }
    return false;
  }

};

std::queue<Node*> create_queues(std::queue<Node*> q){
  Node* the_node_were_looking_at;
  std::queue<Node*> children_q;
  while(!q.empty()){
    the_node_were_looking_at = q.front();
    q.pop();
    if(!the_node_were_looking_at->children.empty()){
      for(int i = 0; i < the_node_were_looking_at->children.size(); i++){
        children_q.push(the_node_were_looking_at->children[i]);
      }
    }
  }
  return children_q;
}


int main_with_large_stack_space() {
  std::ios_base::sync_with_stdio(0);
  int n;
  std::cin >> n;
  Node *root_node;
  std::vector<Node> nodes;
  nodes.resize(n);
  for (int child_index = 0; child_index < n; child_index++) {
    int parent_index;
    std::cin >> parent_index;
    if (parent_index >= 0)
      nodes[child_index].setParent(&nodes[parent_index]);
    if (parent_index == -1)
      root_node = &nodes[child_index];
    nodes[child_index].key = child_index;
  }
  // calculate tree depth
  int a_height = 1;
  Node *the_node_were_looking_at;
  std::queue<Node*> q;
  q.push(root_node);
  root_node->height = 1;
  std::queue<Node*> a_queue = create_queues(q);
  while(!a_queue.empty()){
    a_queue = create_queues(a_queue);
    a_height++;
  }
  std::cout << a_height;
  return 0;
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
