/* MIT License

Copyright (c) 2020 Daniel Steinberg

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
==============================================================================*/

#pragma once

#include <cassert>
#include <vector>

namespace revdoor {

class combinations {
  std::vector<int> c;
  int n, t, j;

 public:
  combinations(int n, int t) : c(t + 1), n(n), t(t) {
    assert(n > t);
    for (j = 0; j < t; ++j) {
      c[j] = j;
    }
    c[t] = n;
  }

  // Intended to be used infrequently (e.g., for retrieving first combination).
  const std::vector<int> data() {
    std::vector<int> output(c.begin(), c.begin() + t);
    return output;
  }

  bool step(int* out, int* in) {
R3:
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

class combinations_with_replacement {
  std::vector<int> c;
  int n, t, j;

 public:
  combinations_with_replacement(int n, int t) : c(t + 1), n(n + t - 1), t(t) {
    assert(this->n > t);
    for (j = 0; j < t; ++j) {
      c[j] = 0;
    }
    c[t] = this->n - j;
  }

  // Intended to be used infrequently (e.g., for retrieving first combination).
  const std::vector<int> data() {
    std::vector<int> output(c.begin(), c.begin() + t);
    return output;
  }

  bool step(int* out1, int* in1, int* out2, int* in2) {
    *out1 = *in1 = *out2 = *in2 = c[0];
R3:
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
