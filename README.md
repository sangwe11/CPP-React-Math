# CPP-React-Math
A templated header-only C++ vector and matrix math library. Simply include the header files and start using types such as vec3f, mat4f and quatf.

## Build example and unit tests
Build a simple example implementing a 'transform' class and the unit tests.
```bash
git clone https://git.vfk.io/gary/CPP-React-Math.git
mkdir build && cd build
cmake ../
make
./tests/test_unit # run unit tests
./example/example # run example
```