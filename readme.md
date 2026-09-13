# ynodesktop-saucer

Directly inspired by and uses code from [github.com/affectioned/ynodesktop](https://github.com/affectioned/ynodesktop)

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

This project automatically fetches the following dependency via CPM (C++ Package Manager):
- **Saucer** 8.0.5 - A lightweight web framework for C++
