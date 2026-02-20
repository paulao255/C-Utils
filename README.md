# C-Utils

**C-Utils** is a repository with header(s) to make C/C++ more easy/fast to create projects and big applications, it have the most common features, like `clear_stdout()`, `clear_stdin()`, `paktc()`, etc... works in **C89/C++98 Standard** or **^** and have some **compatibility features** too.

Compatible with:

- [x] Windows.
- [x] Linux.
- [x] Mac OS (not tested yet, if you can test it, send an e-mail to **contactpaulao\@gmail.com**).

To include **C-Utils** into your **C project**, you need to use `CMake` and `Ninja` by adding these lines on `CMakeLists.txt`:

```CMakeLists.txt
cmake_minimum_required(VERSION 4.2.3)
project(Example-C-Project LANGUAGES C VERSION 20260127)
set(CMAKE_C_STANDARD 90) # 90 for C89, 99 for C99, 11 for C11, 17 for C17 and 23 for C23.
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
include(FetchContent) # Include Fetch Content.
FetchContent_Declare(C-Utils GIT_REPOSITORY https://github.com/paulao255/C-Utils.git GIT_TAG main) # Find C-Utils repo.
FetchContent_MakeAvailable(C-Utils) # Clone C-Utils repo.
add_executable(Executable ../src/Main.c)
target_compile_options(Executable PRIVATE -fdiagnostics-color=always -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion -Wformat=2 -Wnull-dereference -Wstrict-prototypes -Wmissing-prototypes -Wcast-align -Wpointer-arith -Wundef -v -O3 -funroll-loops -flto -mtune=native -march=native)
target_link_libraries(Executable PRIVATE C-Utils) # Link C-Utils to executable.
set_target_properties(Executable PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) # Put the executable into "./build/bin" directory.
```

For a **C++ project** you need to create a `CMakeLists.txt` like this:

```CMakeLists.txt
cmake_minimum_required(VERSION 4.2.3)
project(Example-Cpp-Project LANGUAGES CXX VERSION 20260127)
set(CMAKE_CXX_STANDARD 98) # 98 for C++98, 11 for C++11, 14 for C++14, 17 for C++17, 20 for C++20, 23 for C++23 and 26 for C++26.
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
include(FetchContent) # Include Fetch Content.
FetchContent_Declare(C-Utils GIT_REPOSITORY https://github.com/paulao255/C-Utils.git GIT_TAG main) # Find C-Utils repo.
FetchContent_MakeAvailable(C-Utils) # Clone C-Utils repo.
add_executable(Executable ../src/Main.cpp)
target_compile_options(Executable PRIVATE -fdiagnostics-color=always -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion -Wformat=2 -Wnull-dereference -Wcast-align -Wpointer-arith -Wundef -v -O3 -funroll-loops -flto -mtune=native -march=native)
target_link_libraries(Executable PRIVATE C-Utils) # Link C-Utils to executable.
set_target_properties(Executable PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) # Put the executable into "./build/bin" directory.
```

The **project structure** need to be like this to work:

```Directory.txt
.
├─ .git/
├─ .gitignore
├─ CMakeLists.txt
├─ src/
│  └─ Main.c or Main.cpp
├─ LICENSE
└─ README.md
```

## Dependencies

- `GCC` (or `Mingw GCC` for **Windows**).
- `CMake` to **build the project**.
- `Ninja` (or `Mingw Ninja` for **Windows**) to help `CMake` to **make the executable file**.

### Dependencies install process

**Windows**:

1. Press `Windows + R`.
2. type `cmd` and press `Ctrl + Shift + Enter`, then open it in administrator mode.
3. Type into **cmd** `winget install --id="Kitware.CMake" && winget install --id="MSYS2.MSYS2"`.
4. Now after install **CMake** and **MSYS2** press `Windows + R`.
5. Type `mingw64` or `mingw32` for 32 bits.
6. Press `Ctrl + Shift + Enter` to open it as an administrator.
7. Now on **Mingw Shell** type `pacman -Syyu --needed`.
8. It will probably say to **quit** after update.
9. Then you will press `y` to quit and enter in **Mingw Shell** again.
10. Type `pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-ninja --needed`.
11. Type `pacman -S --needed mingw-w64-x86_64-make`.
12. Now you just need to **build** the project.

**Linux**:

1. Install `GCC`, `CMake`, `Ninja` and `Make` with your **Package Manager**.
2. **Build** the project.

**macOS**:

1. Install a **[Mac port](https://www.macports.org/install.php)**.
2. Enter in **terminal**.
3. Type `sudo port selfupdate && sudo port install cmake gcc ninja make`.
4. **Build** the project.

#### Build process

- `make` or `make all` to build the executable.
- `make clean` to remove the build.
- `make install` to install in the binary directory.

##### Credits

**Created by: @paulao255**.
