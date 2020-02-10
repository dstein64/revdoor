# revdoor

`revdoor` is a single-file C++ library for generating *revolving door* combinations.
The generators visit combinations by indicating replacements for one or two items
on each iteration.

The *combinations without replacement* generator implements Algorithm R from TAOCP
7.2.1.3 [[1]](#references). The *combinations with replacement* generator implements
the same algorithm, modified to support replacement.

## Quick Start
 
1. Include the `<revdoor.hpp>` header.
2. For combinations without replacement, initialize a generator object with
   `revdoor::combinations`. For combinations with replacement, initialize a
   generator object with `revdoor::combinations_with_replacement`.
3. Use the `state()` method to get the initial state of the generator.
4. Call the `step()` method to proceed to the next combination.
   - For combinations without replacement, this takes two pointers: `out` is
     set to the element that is removed, and `in` is set to the element that
     is added.
   - For combinations without replacement, this takes four pointers: `out1`
     and `out2` are set to elements that are removed; `in1` and `in2` are set
     to elements that are added. In cases where only a single item is replaced,
     `out1 == in1`.

## Documentation

Refer to the comments in [revdoor.hpp](revdoor.hpp) for detailed information.

## License

The source code has an [MIT License](https://en.wikipedia.org/wiki/MIT_License).

See [revdoor.hpp](revdoor.hpp).

## References

[1] Donald Knuth, The Art of Computer Programming, Volume 4, Fascicle 3: Generating
All Combinations and Partitions (Addison-Wesley Professional, 2005).
