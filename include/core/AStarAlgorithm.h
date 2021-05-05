//
// Created by Tarun Voruganti on 11/24/20.
//

#ifndef PATH_FINDING_ASTARALGORITHM_H
#define PATH_FINDING_ASTARALGORITHM_H

#include "cinder/gl/gl.h"
#include <vector>

using ci::vec2;
using std::vector;

namespace path_finding {

class AStarAlgorithm {

public:
  AStarAlgorithm() = default;

  AStarAlgorithm(const vector<vector<char>> &graph, const vec2 &start_pos,
                 const vec2 &end_pos);

  void SolveAStar();

  void UpdateMap();

  vector<vector<char>> GetMap() const;

private:
  struct Node {
    bool obstacle = false; // Is the node an obstruction?
    bool visited = false;  // Have we searched this node before?
    float_t global_dist;   // Distance to goal so far
    float_t local_dist;    // Distance to goal if we took the alternative route
    float_t x;              // x position
    float_t y;              // y position
    vector<Node *> neighbors; // Connections to neighbours
    Node *parent; // Node connecting to this node that offers shortest parent
  };

  Node *nodes_ = nullptr;
  size_t graph_height_;
  size_t graph_width_;
  Node *start_node_ = nullptr;
  Node *end_node_ = nullptr;
  vector<vector<char>> map;
};

} // namespace path_finding

#endif // PATH_FINDING_ASTARALGORITHM_H
