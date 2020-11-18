#include <visualizer/path_finding_app.h>

namespace path_finding {

namespace visualizer {

PathFindingApp::PathFindingApp()
    : sketchpad_(glm::vec2(kMargin, kMargin), kImageDimension,
                 vec2(kWindowSize - kMargin, kWindowSize - 2 * kMargin)) {
  app::setWindowSize(kWindowSize + 6 * kMargin, (int)kWindowSize);
}

void PathFindingApp::draw() {
  Color8u background_color(0, 0, 0);  // light yellow
  gl::clear(background_color);

  sketchpad_.Draw();

  gl::drawStringCentered(
      "Path Finding Simulator",
      glm::vec2((kWindowSize + 6 * kMargin) / 2, kMargin / 2), Color("white"));

  gl::drawStringCentered(
      "Points",
      glm::vec2(kWindowSize + 4 * kMargin, kMargin), Color("white"));

  gl::drawStringCentered(
      "Choose Starting Point",
      glm::vec2(kWindowSize + 4 * kMargin, kMargin + 20), Color("white"));

  gl::drawStringCentered(
      "Choose Ending Point",
      glm::vec2(kWindowSize + 4 * kMargin, 3*kMargin/2 + 50), Color("white"));

  gl::color(Color("white"));
  vec2 top_left_start_outline(kWindowSize + 4 * kMargin - kMargin/2, kMargin + 30);
  vec2 bottom_right_start_outline = top_left_start_outline + vec2(kMargin,kMargin/2);
  Rectf start_point_outline(top_left_start_outline, bottom_right_start_outline);
  gl::drawStrokedRect(start_point_outline);

  gl::color(Color("lime"));
  vec2 top_left_start = (top_left_start_outline + bottom_right_start_outline)/vec2(2,2) - vec2(kMargin/7,kMargin/7);
  vec2 bottom_right_start = top_left_start + vec2(2*kMargin/7,2*kMargin/7);
  Rectf start_point_pic(top_left_start, bottom_right_start);
  gl::drawSolidRect(start_point_pic);

  gl::color(Color("white"));
  vec2 top_left_end_outline(kWindowSize + 4 * kMargin - kMargin/2, 3*kMargin/2 + 60);
  vec2 bottom_right_end_outline = top_left_end_outline + vec2(kMargin,kMargin/2);
  Rectf end_point_outline(top_left_end_outline, bottom_right_end_outline);
  gl::drawStrokedRect(end_point_outline);

  gl::color(Color("red"));
  vec2 top_left_end = (top_left_end_outline + bottom_right_end_outline)/vec2(2,2) - vec2(kMargin/7,kMargin/7);
  vec2 bottom_right_end = top_left_end + vec2(2*kMargin/7,2*kMargin/7);
  Rectf end_point_pic(top_left_end, bottom_right_end);
  gl::drawSolidRect(end_point_pic);

}

void PathFindingApp::mouseDown(app::MouseEvent event) {
  if (event.isLeftDown())
    sketchpad_.HandleBrush(event.getPos(), false, false);
  else
    sketchpad_.HandleBrush(event.getPos(), true, false);


}

void PathFindingApp::mouseDrag(app::MouseEvent event) {
  if (event.isLeftDown())
    sketchpad_.HandleBrush(event.getPos(), false, false);
  else
    sketchpad_.HandleBrush(event.getPos(), true, true);


}

void PathFindingApp::keyDown(app::KeyEvent event) {
  switch (event.getCode()) {
    case app::KeyEvent::KEY_RETURN:
      sketchpad_.Clear();
      break;
  }
}

}  // namespace visualizer

}  // namespace naivebayes
