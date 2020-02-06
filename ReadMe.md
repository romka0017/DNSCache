# DNS cache
Current project illustrates the example of DNS cache mechanism.
It includes "DNSCache" class which will be built as shared library
and unit tests based on "Catch" framework.

## Dependencies
Framework for unit tests [Catch] (https://github.com/catchorg/Catch2)

## Structure
"DNSCache" class includes "DNSCache.h" header file and "DNSCache.cpp" source file

**/include/DNSCache.h**

**/src/DNSCache.cpp**

Unit tests include "catch.hpp" header file and "catch_tests.cpp" source file

**/libs/catch.hpp**

**catch_tests.cpp**

## How to build
To build the project you should use cmake 3.16+ and GCC 7+.
Note. Project requires C++17. Current configuration was tested by developer.

You can build "DNSCache" as a separate shared library or you can build tests which will
use pre-built library.

To build the library only please run "cmake ~pwd" from "DNS/src" folder.
To build the tests + library please run "cmake ~pwd" from "DNS" folder.

## Tests
To run the tests please run executable file "catch_tests".

## Comlexity
If we speak about complexity of "std::unordered_map" we should understand the frequency of collisions.
In case of no collisions complexity is O(1) plus complexity of the "HASH" functions.
In case with collisions complexity is O(K), where K is the average size of bucket.
The performance of current solution is not reduced by "std::list" usage.