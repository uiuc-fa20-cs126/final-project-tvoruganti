#pragma once

#include "cinder/gl/gl.h"

using glm::vec2;

namespace path_finding {

namespace visualizer {

class Graph {
 public:

  Graph(const vec2& top_left_corner, const vec2& num_pixels_per_side,
            const vec2& sketchpad_size, double brush_radius = .5);

  /**
   * Displays the current state of the sketchpad in the Cinder application.
   */
  void Draw() const;

  void HandleBrush(const glm::vec2& brush_screen_coords, bool draw_point, bool start_point);

  /**
   * Set all of the sketchpad pixels to an unshaded state.
   */
  void Clear();

  std::vector<std::vector<char>> GetImage();

  void DrawPath() const;
  void ShowPath();

 private:
  vec2 top_left_corner_;
  vec2 num_pixels_per_side_;
  vec2 start_point_coords_;
  vec2 end_point_coords_;
  double brush_radius_;
  bool draw_path = false;
  size_t pixel_side_length_; //Number of screen pixels in the width/height of one sketchpad pixel
  std::vector<std::vector<char>> image_;
};

}  // namespace visualizer

}  // namespace naivebayes
