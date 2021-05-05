#pragma once

#include "cinder/gl/gl.h"
#include "core/AStarAlgorithm.h"

using glm::vec2;

namespace path_finding {

namespace visualizer {

class Graph {
 public:

  /**
   * Creates a graph
   * @param top_left_corner top left position relative to the window
   * @param num_pixels_per_side how large graph should be
   * @param graph_size How large graph will be in real pixels
   */
  Graph(const vec2& top_left_corner, const vec2& num_pixels_per_side,
            const vec2& graph_size);

  /**
   * Draws the graph as a visual representation
   * @param array which graph to draw
   */
  void Draw(std::vector<std::vector<char>> array) const;

  /**
   * Colors cells on the graph if clicked on
   * @param brush_screen_coords coordinates of the mouse
   * @param draw_point whether to draw a point or obstacle
   * @param start_point whether to draw the start or end point
   */
  void HandleBrush(const glm::vec2& brush_screen_coords, bool draw_point, bool start_point);

  /**
   * Set all of the sketchpad pixels to an unshaded state.
   */
  void Clear();

  /**
   * Runs the path finding algorithm and finds a path between the 2 points
   */
  void DrawPath();

  /**
   * Toggles show path boolean
   */
  void ToggleShowPath();

  /**
   * Calls Draw on either the graph or solved graph
   */
  void DrawHelper() const;

  friend std::ostream& operator<<(std::ostream& os, Graph& graph);

  friend std::istream &operator>>(std::istream &is, Graph &graph);

  /**
   * For testing purposes, returns the drawing
   * @return drawing
   */
  std::vector<std::vector<char>> GetImage();

private:
  vec2 top_left_corner_; //top left position relative to the window
  vec2 num_pixels_per_side_; //size of sketchpad in sketchpad pixels
  size_t pixel_side_length_; //Number of screen pixels in the width/height of one sketchpad pixel
  vec2 start_point_coords_; //coordinates of starting point in sketchpad coordinates
  vec2 end_point_coords_; //coordinates of ending point in sketchpad coordinates
  std::vector<std::vector<char>> drawing_; //represents the graph as 2D list of chars
  std::vector<std::vector<char>> solved_drawing_; //image_ but with the solved path
  bool show_path = false; //toggles showing the path or not

};

}  // namespace visualizer

}  // namespace naivebayes
