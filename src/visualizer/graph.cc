#include <visualizer/graph.h>

namespace path_finding {

namespace visualizer {

using glm::vec2;

Graph::Graph(const vec2& top_left_corner, const vec2& num_pixels_per_side,
                     const vec2& graph_size)
    : top_left_corner_(top_left_corner),
      num_pixels_per_side_(num_pixels_per_side),
      pixel_side_length_(graph_size.y / num_pixels_per_side.y),
      start_point_coords_({0,0}),
      end_point_coords_(num_pixels_per_side - vec2(1,1)){

  //fills in an empty graph
  for(size_t i = 0; i < num_pixels_per_side.y; i++){
    std::vector<char> temp(num_pixels_per_side.x, 'w');
    drawing_.emplace_back(temp);
  }

  //sets start and end points
  drawing_[start_point_coords_.y][start_point_coords_.x] = 's';
  drawing_[end_point_coords_.y][end_point_coords_.x] = 'e';
  //creates the solved drawing
  solved_drawing_ = drawing_;
  DrawPath();
}

void Graph::DrawHelper() const {
  if (show_path)
    Draw(solved_drawing_);
  else
    Draw(drawing_);
}

void Graph::Draw(std::vector<std::vector<char>> array) const{
  for (size_t row = 0; row < num_pixels_per_side_.y; ++row) {
    for (size_t col = 0; col < num_pixels_per_side_.x; ++col) {

      //sets color depending on the character
      switch (array[row][col]) {
        case '#':
          //make walls gray
          ci::gl::color(ci::Color::gray(0.3f));
          break;
        case 's':
          //make start point green
          ci::gl::color(ci::Color("lime"));
          break;
        case 'e':
          //make end point red
          ci::gl::color(ci::Color("red"));
          break;
        case 'b':
          //make the path blue
          ci::gl::color(ci::Color("blue"));
          break;
        default:
          //make empty cells white
          ci::gl::color(ci::Color("white"));
      }

      //draws each individual cell
      vec2 pixel_top_left = top_left_corner_ + vec2(col * pixel_side_length_,
                                                    row * pixel_side_length_);

      vec2 pixel_bottom_right =
          pixel_top_left + vec2(pixel_side_length_);
      ci::Rectf pixel_bounding_box(pixel_top_left, pixel_bottom_right);

      ci::gl::drawSolidRect(pixel_bounding_box);

      ci::gl::color(ci::Color::gray(0.7f));
      ci::gl::drawStrokedRect(pixel_bounding_box);
    }
  }
}

void Graph::HandleBrush(const vec2& brush_screen_coords, bool draw_point, bool start_point) {
  double brush_radius = .5;
  //converts from screen coordinates to sketchpad coordinates
  vec2 brush_sketchpad_coords =
      (brush_screen_coords - top_left_corner_) / vec2(pixel_side_length_);

  if (draw_point){
    //changes position of start or end point and updates variable
    if (start_point){
      drawing_[start_point_coords_.y][start_point_coords_.x] = 'w';
      drawing_[brush_sketchpad_coords.y][brush_sketchpad_coords.x] = 's';
      start_point_coords_ = vec2((size_t)brush_sketchpad_coords.x, (size_t)brush_sketchpad_coords.y);
    } else {
      drawing_[end_point_coords_.y][end_point_coords_.x] = 'w';
      drawing_[brush_sketchpad_coords.y][brush_sketchpad_coords.x] = 'e';
      end_point_coords_ = vec2((size_t)brush_sketchpad_coords.x, (size_t)brush_sketchpad_coords.y);
    }
  } else {
    //draws obstacles
    for (size_t row = 0; row < num_pixels_per_side_.y; ++row) {
      for (size_t col = 0; col < num_pixels_per_side_.x; ++col) {
        vec2 pixel_center = {col + 0.5, row + 0.5};

        if (glm::distance(brush_sketchpad_coords, pixel_center) <=
            brush_radius) {
          if ((vec2(row, col) != vec2(size_t(start_point_coords_.y), size_t(start_point_coords_.x))) && ((vec2(row, col) != vec2(size_t(end_point_coords_.y), size_t(end_point_coords_.x)))))
            drawing_[row][col] = drawing_[row][col] == '#' ? 'w':'#';
        }
      }
    }
  }
  DrawPath();
}

void Graph::Clear() {
  //sets each character to a white space
  for (auto & i : drawing_) {
    for (char & j : i) {
      j = 'w';
    }
  }
  //reset start and end points
  start_point_coords_ = {0, 0};
  end_point_coords_ = num_pixels_per_side_ - vec2(1,1);
  drawing_[start_point_coords_.y][start_point_coords_.x] = 's';
  drawing_[end_point_coords_.y][end_point_coords_.x] = 'e';
}

std::vector<std::vector<char>> Graph::GetImage(){
  return drawing_;
}

void Graph::DrawPath(){
  //runs AStar Algorithm on this graph
  AStarAlgorithm algo(drawing_, start_point_coords_, end_point_coords_);
  algo.SolveAStar();
  solved_drawing_ = algo.GetMap();
}

void Graph::ToggleShowPath() {
  show_path = !show_path;
}

std::ostream &operator<<(std::ostream &os, Graph &graph) {
  os << graph.start_point_coords_.x << " " <<  graph.start_point_coords_.y << std::endl;
  os << graph.end_point_coords_.x << " " <<  graph.end_point_coords_.y << std::endl;
  os << graph.num_pixels_per_side_.x << " " <<  graph.num_pixels_per_side_.y << std::endl;

  for (auto & i : graph.drawing_) {
    for (char & j : i) {
      os << std::to_string(j) + ' ';
    }
    os << "\n";
  }
  return os;
}

std::istream &operator>>(std::istream &is, Graph &graph) {
  std::vector<std::vector<char>> image;
  std::string::size_type sz;  // keeps track of what number the line is on
  std::string line;

  getline(is, line);
  double x = std::stoi(line, &sz);
  line = line.substr(sz);
  double y = std::stoi(line, &sz);
  graph.start_point_coords_ = vec2(x, y);

  getline(is, line);
  x = std::stoi(line, &sz);
  line = line.substr(sz);
  y = std::stoi(line, &sz);
  graph.end_point_coords_ = vec2(x, y);

  getline(is, line);
  x = std::stoi(line, &sz);
  line = line.substr(sz);
  y = std::stoi(line, &sz);
  graph.pixel_side_length_ = graph.pixel_side_length_ * graph.num_pixels_per_side_.y/y; //resizes the graph
  graph.num_pixels_per_side_ = vec2(x, y);

  for(size_t i = 0; i < y; i++){
    std::vector<char> temp(x, 'w');
    image.emplace_back(temp);
  }

  for(size_t i = 0; i < y; i++){
    getline(is, line);
    for (size_t j = 0; j < x; ++j) {
      image[i][j] = std::stoi(line, &sz);
      line = line.substr(sz);
    }
  }

  graph.drawing_ = image;
  graph.solved_drawing_ = image;
  graph.show_path = false;
  graph.DrawPath();

  return is;
}

}  // namespace visualizer

}  // namespace naivebayes
