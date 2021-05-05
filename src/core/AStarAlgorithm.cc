//
// Created by Tarun Voruganti on 11/24/20.
//

#include "core/AStarAlgorithm.h"

namespace path_finding {

AStarAlgorithm::AStarAlgorithm(const vector<vector<char>> &graph, const vec2& start_pos, const vec2& end_pos)
    : graph_height_(graph.size()),
      graph_width_(graph[0].size()),
      map(graph){

  //creates array of nodes and creates 1 for each point in the graph
  nodes_ = new Node[graph_height_ * graph_width_];
  for (size_t x = 0; x < graph_width_; x++)
    for (size_t y = 0; y < graph_height_; y++) {
      nodes_[y * graph_width_ + x].x = x;
      nodes_[y * graph_width_ + x].y = y;
      nodes_[y * graph_width_ + x].parent = nullptr;
      nodes_[y * graph_width_ + x].visited = false;
      nodes_[y * graph_width_ + x].global_dist = INFINITY;
      nodes_[y * graph_width_ + x].local_dist = INFINITY;
      nodes_[y * graph_width_ + x].obstacle = graph[y][x] == '#';

      //sets the start node pointer
      if (vec2(x,y) == start_pos)
        start_node_ = &nodes_[y * graph_width_ + x];

      //sets the end node pointer
      if (vec2(x,y) == end_pos)
        end_node_ = &nodes_[y * graph_width_ + x];
    }

  //creates connections for each node
  for (int x = 0; x < graph_width_; x++)
    for (int y = 0; y < graph_height_; y++) {
      if (y > 0)
        nodes_[y * graph_width_ + x].neighbors.push_back(&nodes_[(y - 1) * graph_width_ + (x + 0)]);
      if (y < graph_height_ - 1)
        nodes_[y * graph_width_ + x].neighbors.push_back(&nodes_[(y + 1) * graph_width_ + (x + 0)]);
      if (x > 0)
        nodes_[y * graph_width_ + x].neighbors.push_back(&nodes_[(y + 0) * graph_width_ + (x - 1)]);
      if (x < graph_width_ - 1)
        nodes_[y * graph_width_ + x].neighbors.push_back(&nodes_[(y + 0) * graph_width_ + (x + 1)]);
    }
}

void AStarAlgorithm::SolveAStar() {

  //starting conditions
  Node *current = start_node_;
  start_node_->local_dist = 0.0f;
  start_node_->global_dist = glm::distance(vec2(start_node_->x, start_node_->y), vec2(end_node_->x, end_node_->y));

  //list of nodes to test, add start node to begin and will add more as algorithm progresses
  std::list<Node*> not_tested_nodes_list;
  not_tested_nodes_list.push_back(start_node_);

  //checks all paths not just the first one found
  //while there are still nodes to test and the current node is not the end goal
  while (!not_tested_nodes_list.empty() && current != end_node_){

    // Sort Untested nodes by global distance, so lowest is first
    not_tested_nodes_list.sort([](const Node* lhs, const Node* rhs){ return lhs->global_dist < rhs->global_dist; });

    //Removes nodes that have already been visited
    while(!not_tested_nodes_list.empty() && not_tested_nodes_list.front()->visited)
      not_tested_nodes_list.pop_front();

    //If the list is empty now then break to save time
    if (not_tested_nodes_list.empty())
      break;

    current = not_tested_nodes_list.front();
    current->visited = true;

    //Check each of the node's neighbours
    for (auto node_neighbor : current->neighbors)
    {
      //Test a node if it isn't obstacle and not visited
      if (!node_neighbor->visited && !node_neighbor->obstacle)
        not_tested_nodes_list.push_back(node_neighbor);

      //Calculate the neighbours potential lowest parent distance
      float_t possible_lower_goal = current->local_dist + glm::distance(vec2(current->x, current->y), vec2(node_neighbor->x, node_neighbor->y));

      // If going through this node is shorter than the neighbor's current path, update the neighbor to use this node
      if (possible_lower_goal < node_neighbor->local_dist)
      {
        node_neighbor->parent = current;
        node_neighbor->local_dist = possible_lower_goal;

        //update the neighbour's global distance
        node_neighbor->global_dist = node_neighbor->local_dist + glm::distance(vec2(end_node_->x, end_node_->y), vec2(node_neighbor->x, node_neighbor->y));

      }
    }
  }
  UpdateMap();
}

void AStarAlgorithm::UpdateMap(){
  Node* iterator = end_node_;
  //go through the parent chain and make each node blue so it is shown on the UI
  while (iterator->parent != nullptr){
    if (iterator != end_node_ && iterator != start_node_){
      map[iterator->y][iterator->x] = 'b';
    }
    iterator = iterator->parent;
  }
}

vector<vector<char>> AStarAlgorithm::GetMap() const {
  return map;
}

} // namespace path_finding