#include <catch2/catch.hpp>
#include "core/AStarAlgorithm.h"

TEST_CASE("Algorithm Tests"){
  vector<vector<char>> test_graph = {{'s','#','#'},
                                     {'w','#','#'},
                                     {'w','w','e'}};

  vector<vector<char>> solved_test_graph = {{'s','#','#'},
                                            {'b','#','#'},
                                            {'b','b','e'}};

  vec2 start = vec2(0,0);
  vec2 end = vec2(2,2);

  path_finding::AStarAlgorithm algo(test_graph, start, end);

  SECTION("Unsolved Graph Test"){
    vector<vector<char>> unsolved = algo.GetMap();

    REQUIRE(unsolved == test_graph);
  }

  SECTION("Solved Graph Test"){
    algo.SolveAStar();

    vector<vector<char>> solved = algo.GetMap();

    REQUIRE(solved == solved_test_graph);

  }

}