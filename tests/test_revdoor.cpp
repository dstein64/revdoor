#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

#include <revdoor.hpp>
#include <utility>
#include <vector>

using namespace std;

BOOST_AUTO_TEST_CASE(test_combinations) {
  int n = 5;
  int t = 3;
  revdoor::combinations combs(n, t);
  vector<int> init_state = combs.state();
  vector<int> expected_init_state = {0, 1, 2};
  BOOST_CHECK_EQUAL_COLLECTIONS(
      init_state.begin(),
      init_state.end(),
      expected_init_state.begin(),
      expected_init_state.end());
  vector<pair<int,int>> swaps;
  vector<pair<int,int>> expected_swaps = {
    {1, 3}, {0, 1}, {2, 0}, {1, 4}, {0, 1},
    {1, 2}, {3, 0}, {0, 1}, {2, 0}
  };
  int out, in;
  while (combs.step(&out, &in)) {
    swaps.push_back({out, in});
  }
  BOOST_REQUIRE_EQUAL(swaps.size(), expected_swaps.size());
  for (int i = 0; i < (int)swaps.size(); ++i) {
    BOOST_CHECK_EQUAL(swaps[i].first, expected_swaps[i].first);
    BOOST_CHECK_EQUAL(swaps[i].second, expected_swaps[i].second);
  }
  vector<int> end_state = combs.state();
  vector<int> expected_end_state = {0, 1, 4};
  BOOST_CHECK_EQUAL_COLLECTIONS(
      end_state.begin(),
      end_state.end(),
      expected_end_state.begin(),
      expected_end_state.end());
}

BOOST_AUTO_TEST_CASE(test_combinations_with_replacement) {
  int n = 5;
  int t = 3;
  revdoor::combinations_with_replacement combs(n, t);
  vector<int> init_state = combs.state();
  vector<int> expected_init_state = {0, 0, 0};
  BOOST_CHECK_EQUAL_COLLECTIONS(
      init_state.begin(),
      init_state.end(),
      expected_init_state.begin(),
      expected_init_state.end());
  vector<vector<int>> swaps;
  vector<vector<int>> expected_swaps = {
    {0, 1, 0, 1}, {0, 1}, {1, 0, 1, 0}, {0, 2, 1, 2}, {0, 1},
    {1, 2}, {2, 1, 2, 0}, {0, 1}, {1, 0, 1, 0}, {0, 3, 2, 3},
    {0, 1}, {1, 2}, {2, 3}, {3, 2, 3, 0}, {0, 1}, {1, 2},
    {2, 1, 2, 0}, {0, 1}, {1, 0, 1, 0}, {0, 4, 3, 4}, {0, 1},
    {1, 2}, {2, 3}, {3, 4}, {4, 3, 4, 0}, {0, 1}, {1, 2},
    {2, 3}, {3, 2, 3, 0}, {0, 1}, {1, 2}, {2, 1, 2, 0}, {0, 1},
    {1, 0, 1, 0}
  };
  int out1, in1, out2, in2;
  while (combs.step(&out1, &in1, &out2, &in2)) {
    vector<int> v;
    if (out1 != in1) {
      v.push_back(out1);
      v.push_back(in1);
    }
    v.push_back(out2);
    v.push_back(in2);
    swaps.push_back(v);
  }
  BOOST_REQUIRE_EQUAL(swaps.size(), expected_swaps.size());
  for (int i = 0; i < (int)swaps.size(); ++i) {
    BOOST_CHECK_EQUAL_COLLECTIONS(
        swaps[i].begin(),
        swaps[i].end(),
        expected_swaps[i].begin(),
        expected_swaps[i].end());
  }
  vector<int> end_state = combs.state();
  vector<int> expected_end_state = {0, 0, 4};
  BOOST_CHECK_EQUAL_COLLECTIONS(
      end_state.begin(),
      end_state.end(),
      expected_end_state.begin(),
      expected_end_state.end());
}
