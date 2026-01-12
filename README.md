# cutils.h
**C-Utils** is a repository with header(s) to make C/C++ more easy/fast to create projects and big applications, it have the most common features, like `CLEAR_TERMINAL()`, `petc()`, etc... works in **C89 Standard** or +, and have **Linux**, **Windows** and **macOS** support (It probably works on Android and MS-DOS too).

To include **C-Utils** into your C/C++ project, you need to use **CMake** by adding these lines on `CMakeLists.txt`:
```CMakeLists.txt
# CMake example:
cmake_minimum_required(VERSION 3.14)                                                               # 3.14 or +.
project(Example-C-Project LANGUAGES C)                                                             # Create an example project.
set(CMAKE_C_STANDARD 89)                                                                           # C89 standard.
set(CMAKE_C_STANDARD_REQUIRED ON)                                                                  # Force standard.
set(CMAKE_C_FLAGS "-O3")                                                                           # Flags to compilation.
include(FetchContent)                                                                              # Fetch packages from web.
FetchContent_Declare(C-Utils GIT_REPOSITORY https://github.com/paulao255/C-Utils.git GIT_TAG main) # Find C-Utils repo.
FetchContent_MakeAvailable(C-Utils)                                                                # Clone C-Utils.
add_executable(Executable.exe ../src/Main.c)                                                       # Make and executable.
target_link_libraries(Executable.exe PRIVATE C-Utils::C-Utils)                                     # Link to Executable.
```

And the **project structure** need to be like this to work:
```Directory.txt
.
├─ .gitignore
├─ build
│  └─ .gitkeep
├─ CMakeLists.txt
├─ src
│  └─ Main.c
├─ LICENSE
└─ README.md
```

You will **build your project with C-Utils** by going to `./build` directory and typing `cmake ..` to create the **main executable**.

### Created by: @paulao255
