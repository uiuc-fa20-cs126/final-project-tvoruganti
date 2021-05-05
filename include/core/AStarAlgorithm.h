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

  /**
   * Creates An array of nodes given a 2D vector of characters
   * @param graph       2D Vector of Chars
   * @param start_pos   Position of start point in the graph
   * @param end_pos     Position of end point in the graph
   */
  AStarAlgorithm(const vector<vector<char>> &graph, const vec2 &start_pos,
                 const vec2 &end_pos);

  /**
   * Finds a path from the start point to end point
   */
  void SolveAStar();

  /**
   * Returns the map held by the algorithm, whether solved or unsolved
   * @return the map
   */
  vector<vector<char>> GetMap() const;

private:
  struct Node {
    bool obstacle = false;  // Is the node an obstruction?
    bool visited = false;   // Have we searched this node before?
    float_t global_dist;    // Distance to goal so far
    float_t local_dist;     // Distance to goal if we took the alternative route
    float_t x;              // x position
    float_t y;              // y position
    vector<Node *> neighbors; // Connections to neighbours
    Node *parent; // Node connecting to this node that offers shortest parent
  };

  Node *nodes_ = nullptr; //array of nodes
  size_t graph_height_;
  size_t graph_width_;
  Node *start_node_ = nullptr; //points to starting node in array
  Node *end_node_ = nullptr; //points to end node in array
  vector<vector<char>> map; //2D vector of chars that represents the maze

  /**
   * After Solving the algorithm, it updates the 2D vector of chars to show the path found by the algo
   */
  void UpdateMap();

};

} // namespace path_finding

#endif // PATH_FINDING_ASTARALGORITHM_H
