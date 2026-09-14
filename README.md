# ynodesktop-saucer  <small>[please use the codeberg repo](https://codeberg.org/silentclubstep/ynodesktop-saucer)</small>

Directly inspired by and uses code from [github.com/affectioned/ynodesktop](https://github.com/affectioned/ynodesktop)

this is a Desktop client for the website https://ynoproject.net/ so yeah PLEASE check the real website and support it!!!!!

this is heavily unfinished. [TO-DO list](#todo)

### Mirrors

Saucer is available on: [GitHub](https://github.com/jojo989/ynodesktop-saucer), [Codeberg](https://codeberg.org/silentclubstep/ynodesktop-saucer)

## Building

This project uses CMake to build. Follow the instructions below for your platform.

### Prerequisites

- **CMake** 3.28.0 or higher
- **C++ Compiler** supporting C++23
- **Git** (for fetching dependencies)

### Build Steps

1. **Clone the repository**
   ```bash
   git clone https://github.com/jojo989/ynodesktop-saucer.git
   cd ynodesktop-saucer
   ```

2. **Create a build directory**
   ```bash
   mkdir build
   cd build
   ```

3. **Configure the project with CMake**
   ```bash
   cmake ..
   ```

4. **Build the project**
   ```bash
   cmake --build . --config Release
   ```
and u done

## Dependencies

This project automatically fetches the following dependency via [CPM](https://github.com/cpm-cmake/cpm.cmake) which is a Cmake package manager:
- **Saucer** 8.2.0 - A lightweight web framework for C++ and itz very cool !!! ;3;

## TODO
 - [ ] cookies aka session save
 - [ ] userscript suppor
 - [ ] general code/performance improvmentz ig lol