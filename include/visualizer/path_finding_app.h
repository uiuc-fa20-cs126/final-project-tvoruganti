#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "graph.h"

using namespace ci;

namespace path_finding {

namespace visualizer {

/**
 * Allows a user to draw a digit on a sketchpad and uses Naive Bayes to
 * classify it.
 */
class PathFindingApp : public ci::app::App {
 public:
  PathFindingApp();

  void draw() override;
  void mouseDown(ci::app::MouseEvent event) override;
  void mouseDrag(ci::app::MouseEvent event) override;
  void keyDown(ci::app::KeyEvent event) override;

 private:
  const size_t kWindowSize = 800;
  const size_t kMargin = 100;
  const vec2 kImageDimension = vec2(30,20);
  bool is_start = false;
  Graph sketchpad_;

  void drawButtons() const;
};

}  // namespace visualizer

}  // namespace naivebayes
