[![Actions Status](https://github.com/riiy/acquire-money/workflows/MacOS/badge.svg)](https://github.com/riiy/acquire-money/actions)
[![Actions Status](https://github.com/riiy/acquire-money/workflows/Ubuntu/badge.svg)](https://github.com/riiy/acquire-money/actions)
[![Actions Status](https://github.com/riiy/acquire-money/workflows/Style/badge.svg)](https://github.com/riiy/acquire-money/actions)
[![Actions Status](https://github.com/riiy/acquire-money/workflows/Install/badge.svg)](https://github.com/riiy/acquire-money/actions)
[![codecov](https://codecov.io/gh/riiy/acquire-money/branch/master/graph/badge.svg)](https://codecov.io/gh/riiy/acquire-money)

# AcquireMoney

Setting up a new C++ project usually requires a significant amount of preparation and boilerplate code, even more so for modern C++ projects with tests, executables and continuous integration.
This template is the result of learnings from many previous projects and should help reduce the work required to setup up a modern C++ project.

## Features

- Integrated test suite
- Code coverage via [codecov](https://codecov.io)
- Automatic [documentation](https://thelartians.github.io/AcquireMoney) and deployment with [Doxygen](https://www.doxygen.nl) and [GitHub Pages](https://pages.github.com)

## Usage

### Build and run test suite

Use the following commands from the project's root directory to run the test suite.

```bash
cmake -S test -B build/test
cmake --build build/test
CTEST_OUTPUT_ON_FAILURE=1 cmake --build build/test --target test

# or simply call the executable: 
./build/test/AcquireMoneyTests
```

To collect code coverage information, run CMake with the `-DENABLE_TEST_COVERAGE=1` option.

### Run clang-format

Use the following commands from the project's root directory to check and fix C++ and CMake source style.
This requires _clang-format_, _cmake-format_ and _pyyaml_ to be installed on the current system.

```bash
cmake -S test -B build/test

# view changes
cmake --build build/test --target format

# apply changes
cmake --build build/test --target fix-format
```

See [Format.cmake](https://github.com/TheLartians/Format.cmake) for details.
These dependencies can be easily installed using pip.

```bash
pip install clang-format==14.0.6 cmake_format==0.6.11 pyyaml
```

### Build the documentation

The documentation is automatically built and [published](https://riiy.github.io/acquire-money) whenever a [GitHub Release](https://help.github.com/en/github/administering-a-repository/managing-releases-in-a-repository) is created.
To manually build documentation, call the following command.

```bash
cmake -S documentation -B build/doc
cmake --build build/doc --target GenerateDocs
# view the docs
open build/doc/doxygen/html/index.html
```
