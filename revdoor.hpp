/**
 * @file
 * @author  Daniel Steinberg - https://www.dannyadam.com
 * @version 1.0.1
 *
 * @section LICENSE
 *
 * MIT License
 *
 * Copyright (c) 2020 Daniel Steinberg
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 * @section DESCRIPTION
 *
 * A single-file C++ library for visiting revolving door combinations.
 */

#pragma once

#include <cassert>
#include <vector>

namespace revdoor {

/**
 * A generator for revolving door combinations without replacement. This is an
 * implementation of Algorithm R from TAOCP 7.2.1.3 (Knuth). A single item is
 * swapped out on each subsequent combination visited.
 */
class combinations {
  std::vector<int> c;
  int t, n;

 public:
  /**
   * Constructor for revolving door combinations without replacement.
   * 
   * There are (n choose t) total combinations. The implementation assumes
   * n > t > 1.
   *
   * @param n is the number of elements.
   * @param t is the length of each combination.
   */
  combinations(int n, int t) : c(t + 1), t(t), n(n) {
    assert(n > t);
    assert(t > 1);
    for (int j = 0; j < t; ++j) {
      c[j] = j;
    }
    c[t] = n;
  }

  /**
   * Get the current combination.
   *
   * This can be used specifically for getting the initial combination.
   * This is intended to be used infrequently, as it creates a copy and can
   * also defeat the purpose of using a loopless combination generator.
   *
   * @return A vector representing the current state.
   */
  const std::vector<int> state() {
    std::vector<int> output(c.begin(), c.begin() + t);
    return output;
  }

  /**
   * Set the current combination state.
   *
   * @param state is a combination state.
   */
  void set_state(const std::vector<int>& state) {
    assert((int)state.size() == t);
    std::vector<bool> present(t, false);
    for (int i = 0; i < (int)state.size(); ++i) {
      assert(!present[state[i]]);
      present[state[i]] = true;
      assert(state[i] >= 0);
      assert(state[i] < n);
      c[i] = state[i];
    }
  }

  /**
   * Visit the next combination.
   *
   * @param out's dereference is set to the element that is removed.
   * @param in's dereference is set to the element that is added.
   * @return A boolean that is false when all combinations have already been
   * visited.
   */
  bool step(int* out, int* in) {
    int j;
    if (t & 1) {
      if (c[0] + 1 < c[1]) {
        *out = c[0];
        *in = ++(c[0]);
        goto R2;
      }
      j = 1;
      goto R4;
    }
    if (c[0] > 0) {
      *out = c[0];
      *in = --(c[0]);
      goto R2;
    }
    j = 1;
    goto R5;
R4:
    if (c[j] > j) {
      *out = c[j];
      c[j] = c[j - 1];
      *in = c[j - 1] = j - 1;
      goto R2;
    }
    ++j;
R5:
    if (c[j] + 1 < c[j + 1]) {
      *out = c[j - 1];
      c[j - 1] = c[j];
      *in = ++(c[j]);
      goto R2;
    }
    if (++j < t) goto R4;
    return false;
R2:
    return true;
  }
};

/**
 * A generator for revolving door combinations with replacement. This is an
 * implementation of Algorithm R from TAOCP 7.2.1.3 (Knuth), modified to
 * support replacement. At most two items are swapped out on each subsequent
 * combination visited.
 */
class combinations_with_replacement {
  std::vector<int> c;
  int t, n;

 public:
  /**
   * Constructor for revolving door combinations with replacement.
   *
   * There are (n+t-1 choose t) total combinations. The implementation assumes
   * n+t-1 > t > 1.
   *
   * @param n is the number of elements.
   * @param t is the length of each combination.
   */
  combinations_with_replacement(int n, int t) : c(t + 1), t(t) {
    n += t - 1;
    assert(n > t);
    assert(t > 1);
    for (int j = 0; j < t; ++j) {
      c[j] = 0;
    }
    c[t] = n - t;
    this->n = n;
  }

  /**
   * Get the current combination.
   *
   * This can be used specifically for getting the initial combination.
   * This is intended to be used infrequently, as it creates a copy and can
   * also defeat the purpose of using a loopless combination generator.
   *
   * @return A vector representing the current state.
   */
  const std::vector<int> state() {
    std::vector<int> output(c.begin(), c.begin() + t);
    return output;
  }

  /**
   * Set the current combination state.
   *
   * @param state is a combination state.
   */
  void set_state(const std::vector<int>& state) {
    assert((int)state.size() == t);
    for (int i = 0; i < (int)state.size(); ++i) {
      assert(state[i] >= 0);
      assert(state[i] < n - t + 1);
      c[i] = state[i];
    }
  }

  /**
   * Visit the next combination. In cases where there is only a single item
   * swapped out, *out1 == *in1.
   *
   * @param out1's dereference is set to an element that is removed.
   * @param in1's dereference is set to an element that is added.
   * @param out2's dereference is set to an element that is removed.
   * @param in2's dereference is set to an element that is added.
   * @return A boolean that is false when all combinations have already been
   * visited.
   */
  bool step(int* out1, int* in1, int* out2, int* in2) {
    *out1 = *in1 = *out2 = *in2 = c[0];
    int j;
    if (t & 1) {
      if (c[0] < c[1]) {
        *out2 = c[0];
        *in2 = ++(c[0]);
        goto R2;
      }
      j = 1;
      goto R4;
    }
    if (c[0] > 0) {
      *out2 = c[0];
      *in2 = --(c[0]);
      goto R2;
    }
    j = 1;
    goto R5;
R4:
    if (c[j] > 0) {
      *out1 = c[j];
      *in1 = c[j] = c[j - 1] - 1;
      *out2 = c[j - 1];
      *in2 = c[j - 1] = 0;
      goto R2;
    }
    ++j;
R5:
    if (c[j] < c[j + 1]) {
      *out1 = c[j - 1];
      *in1 = c[j - 1] = c[j] + 1;
      *out2 = c[j];
      *in2 = ++(c[j]);
      goto R2;
    }
    if (++j < t) goto R4;
    return false;
R2:
    return true;
  }
};

}  // namespace revdoor
