#include <visualizer/path_finding_app.h>

using path_finding::visualizer::PathFindingApp;

void prepareSettings(PathFindingApp::Settings* settings) {
  settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(PathFindingApp, ci::app::RendererGl, prepareSettings);
