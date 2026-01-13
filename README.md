# cutils.h

**C-Utils** is a repository with header(s) to make C/C++ more easy/fast to create projects and big applications, it have the most common features, like `CLEAR_TERMINAL()`, `petc()`, etc... works in **C89 Standard** or +, and have **Linux**, **Windows** and **macOS** support (It probably works on Android and MS-DOS too).

To include **C-Utils** into your C/C++ project, you need to use **CMake** by adding these lines on `CMakeLists.txt`:

```CMakeLists.txt
cmake_minimum_required(VERSION 3.14)
project(Example-C-Project LANGUAGES C VERSION 1.0.0)
set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "-fdiagnostics-color=always -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion -Wformat=2 -Wnull-dereference -Wstrict-prototypes -Wmissing-prototypes -Wcast-align -Wpointer-arith -Wundef -v -O3 -funroll-loops -flto -mtune=native -march=native")
include(FetchContent) # Include Fetch Content.
FetchContent_Declare(C-Utils GIT_REPOSITORY https://github.com/paulao255/C-Utils.git GIT_TAG main) # Find C-Utils repo.
FetchContent_MakeAvailable(C-Utils) # Clone C-Utils repo.
add_executable(Executable.exe ../src/Main.c)
target_link_libraries(Executable.exe PRIVATE C-Utils::C-Utils) # Link C-Utils to executable.
```

And the **project structure** need to be like this to work:

```Directory.txt
.
├─ .gitignore
├─ CMakeLists.txt
├─ src
│  └─ Main.c
├─ LICENSE
└─ README.md
```

**Build/Compile process**:

1. Create a directory in `.` named `./build`.
2. Change actual directory to `./build`.
3. Type `cmake ..` in `./build` directory to make the `./build/Makefile`.
4. Type `make` in `./build` to run `./build/Makefile` and create the compiled file named `./build/Executable.exe`.

Created by: @paulao255.
