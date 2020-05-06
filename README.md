# 3D HotDog

[![license](https://img.shields.io/badge/license-MIT-green)](LICENSE)
[![docs](https://img.shields.io/badge/docs-yes-brightgreen)](docs/README.md)

Read [this document](https://cliutils.gitlab.io/modern-cmake/chapters/basics/structure.html) to understand the project
layout.
![Hotdog Example](/images/hotdog.png)
3D Hotdog allows users to visualize and customize their hotdogs in 3D. As a special element, certain items can only be caught from a dropdown and cannot be manually added. 

**Dependencies**
This program uses the [ImGui Cinderblock](https://github.com/simongeilfus/Cinder-ImGui)
and [OpenGL in Cinder](https://libcinder.org/docs/guides/opengl/index.html)
To build the project, see [CMake](https://cmake.org/download/)


**Getting Started**
Run cinder-myapp as the target and cinder-myapp as the executible. 
![View on CLion](/images/cinder-myapp.png)
On Macbooks, you may get an "error = 13, Permissions", in this case do 
Edit configurations -> Executable -> Select Other -> Find my-projects/cinder-myapp/cmake-build-debug/Debug/cinder-myapp/Contents/MacOS/cinder-myapp


**Author**: Angela Luo - [`example@illinois.edu`](mailto:angelal6@illinois.edu)
