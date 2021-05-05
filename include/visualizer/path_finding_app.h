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

  /**
   * creates app
   */
  PathFindingApp();

  /**
   * draws everything on the app
   */
  void draw() override;

  /**
   * called when mouse press id detected
   * @param event information about the press
   */
  void mouseDown(ci::app::MouseEvent event) override;

  /**
   * called when mouse is dragged
   * @param event information about the drag
   */
  void mouseDrag(ci::app::MouseEvent event) override;

private:
  const size_t kWindowSize = 800;
  const size_t kMargin = 100; //how far from (0,0) graph should start
  const vec2 kImageDimension = vec2(20,30); //size of sketchpad in sketchpad coordinates
  bool is_start = true; //whether start or end button is selected
  bool show_path = false; //whether to show path or not

  Graph graph_; //graph that you can draw on

  void drawButtons() const;
};

}  // namespace visualizer

}  // namespace naivebayes
