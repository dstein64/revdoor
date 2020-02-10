[![Build Status](https://travis-ci.org/dstein64/revdoor.svg?branch=master)](https://travis-ci.org/dstein64/revdoor)

# revdoor

`revdoor` is a single-file C++ library for visiting *revolving door*
combinations.

The *combinations without replacement* generator implements Algorithm R from
TAOCP 7.2.1.3 [[1]](#references). The *combinations with replacement* generator
implements the same algorithm, modified to support replacement.

The algorithms visit combinations by indicating `in` and `out` swap values for
one or two items on each iteration.

## Quick Start
 
1. Include the `revdoor.hpp` header.
2. For combinations without replacement, initialize a generator object with
   `revdoor::combinations`. For combinations with replacement, initialize a
   generator object with `revdoor::combinations_with_replacement`.
3. Use the `state()` method to get the initial state of the generator.
4. Call the `step()` method to proceed to the next combination.
   - For combinations without replacement, this takes two `int` pointers:
     `out`'s dereference is set to the element that is removed, and `in`'s
     dereference is set to the element that is added.
   - For combinations without replacement, this takes four `int` pointers:
     `out1`'s and `out2`'s dereferences are set to elements that are removed;
     `in1`'s and `in2`'s dereferences are set to elements that are added.
     In cases where only a single item is swapped out, `*out1 == *in1`.

### Example 1: combinations without replacement

```c++
#include <revdoor.hpp>
#include <vector>

void process_init_state(const std::vector<int> init_state) { /* ... */ }
void process_change(int out, int in) { /* ... */ }

int main(int argc, char* argv[]) {
  int n = 5;
  int t = 3;
  revdoor::combinations combs(n, t);
  std::vector<int> init_state = combs.state();
  process_init_state(init_state);
  int out, in;
  while (combs.step(&out, &in)) {
    process_change(out, in);
  }
  return 0;
}
```

### Example 2: combinations with replacement

```c++
#include <revdoor.hpp>
#include <vector>

void process_init_state(const std::vector<int> init_state) { /* ... */ }
void process_change(int out, int in) { /* ... */ }

int main(int argc, char* argv[]) {
  int n = 5;
  int t = 3;
  revdoor::combinations_with_replacement combs_rep(n, t);
  std::vector<int> init_state = combs_rep.state();
  process_init_state(init_state);
  int out1, in1, out2, in2;
  while (combs_rep.step(&out1, &in1, &out2, &in2)) {
    if (out1 != in1)
      process_change(out1, in1);
    process_change(out2, in2);
  }
  return 0;
}
```

## Documentation

Refer to the comments in [revdoor.hpp](revdoor.hpp) for detailed information.

## License

The source code has an [MIT License](https://en.wikipedia.org/wiki/MIT_License).

See [revdoor.hpp](revdoor.hpp).

## References

[1] Donald Knuth, The Art of Computer Programming, Volume 4, Fascicle 3: Generating
All Combinations and Partitions (Addison-Wesley Professional, 2005).
