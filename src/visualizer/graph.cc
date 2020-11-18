#include <visualizer/graph.h>

namespace path_finding {

namespace visualizer {

using glm::vec2;

Graph::Graph(const vec2& top_left_corner, const vec2& num_pixels_per_side,
                     const vec2& sketchpad_size, double brush_radius)
    : top_left_corner_(top_left_corner),
      num_pixels_per_side_(num_pixels_per_side),
      start_point_coords_({0,0}),
      end_point_coords_(num_pixels_per_side - vec2(1,1)),
      brush_radius_(brush_radius),
      pixel_side_length_(sketchpad_size.y / num_pixels_per_side.y) {

  for(size_t i = 0; i < num_pixels_per_side.y; i++){
    std::vector<char> temp(num_pixels_per_side.x, ' ');
    image_.emplace_back(temp);
  }
  image_[start_point_coords_.y][start_point_coords_.x] = 's';
  image_[end_point_coords_.y][end_point_coords_.x] = 'e';

}

void Graph::Draw() const {
  for (size_t row = 0; row < num_pixels_per_side_.y; ++row) {
    for (size_t col = 0; col < num_pixels_per_side_.x; ++col) {

      if (image_[row][col] == '#') {
        ci::gl::color(ci::Color::gray(0.3f));
      }else if (image_[row][col] == 's') {
        ci::gl::color(ci::Color("lime"));
      }else if (image_[row][col] == 'e') {
        ci::gl::color(ci::Color("red"));
      }else {
        ci::gl::color(ci::Color("white"));
      }

      vec2 pixel_top_left = top_left_corner_ + vec2(col * pixel_side_length_,
                                                    row * pixel_side_length_);

      vec2 pixel_bottom_right =
          pixel_top_left + vec2(pixel_side_length_);
      ci::Rectf pixel_bounding_box(pixel_top_left, pixel_bottom_right);

      ci::gl::drawSolidRect(pixel_bounding_box);

      ci::gl::color(ci::Color("black"));
      ci::gl::drawStrokedRect(pixel_bounding_box);
    }
  }
}

void Graph::HandleBrush(const vec2& brush_screen_coords, bool draw_point, bool start_point) {
  vec2 brush_sketchpad_coords =
      (brush_screen_coords - top_left_corner_) / vec2(pixel_side_length_);

  if (draw_point){
    if (start_point){
      image_[start_point_coords_.y][start_point_coords_.x] = ' ';
      image_[brush_sketchpad_coords.y][brush_sketchpad_coords.x] = 's';
      start_point_coords_ = brush_sketchpad_coords;
    } else {
      image_[end_point_coords_.y][end_point_coords_.x] = ' ';
      image_[brush_sketchpad_coords.y][brush_sketchpad_coords.x] = 'e';
      end_point_coords_ = brush_sketchpad_coords;
    }
  } else {
    for (size_t row = 0; row < num_pixels_per_side_.y; ++row) {
      for (size_t col = 0; col < num_pixels_per_side_.x; ++col) {
        vec2 pixel_center = {col + 0.5, row + 0.5};

        if (glm::distance(brush_sketchpad_coords, pixel_center) <=
            brush_radius_) {
          if ((vec2(row, col) != vec2(size_t(start_point_coords_.y), size_t(start_point_coords_.x))) && ((vec2(row, col) != vec2(size_t(end_point_coords_.y), size_t(end_point_coords_.x)))))
            image_[row][col] = '#';
        }
      }
    }
  }

}

void Graph::Clear() {
  for (auto & i : image_) {
    for (char & j : i) {
      j = ' ';
    }
  }
  start_point_coords_ = {0, 0};
  end_point_coords_ = num_pixels_per_side_ - vec2(1,1);
  image_[start_point_coords_.y][start_point_coords_.x] = 's';
  image_[end_point_coords_.y][end_point_coords_.x] = 'e';
}
std::vector<std::vector<char>> Graph::GetImage(){
  return image_;
}

}  // namespace visualizer

}  // namespace naivebayes
