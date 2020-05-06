# 3D HotDog

[![license](https://img.shields.io/badge/license-MIT-green)](LICENSE)
[![docs](https://img.shields.io/badge/docs-yes-brightgreen)](docs/README.md)

Read [this document](https://cliutils.gitlab.io/modern-cmake/chapters/basics/structure.html) to understand the project
layout.
![Hotdog Example](/images/hotdog.png)
- 3D Hotdog allows users to visualize and customize their hotdogs in 3D. As a special element, certain items can only be caught from a dropdown and cannot be manually added. 
- Users can directly customize perspective, location, color, and menu items. 

## General Flow
The program starts with a sausage and bun and also has 3 ImGui windows for users to control. The instructions windows details what users can do and also hold the option for users to turn off item drops. The list of ingredients lets users choose which they would like to control. On the inspector panel, users can change object type, color, name, and location. In order to switch the background color, click the mouse. To change your perspective, use the mouse wheel and arrow keys. Each ingredient is stored in a list of Objects that can be added or removed. The .obj files can be viewed in the resources folder. 

## Dependencies
- This program uses the [ImGui Cinderblock](https://github.com/simongeilfus/Cinder-ImGui)
- [OpenGL in Cinder](https://libcinder.org/docs/guides/opengl/index.html)
- To build the project, see [CMake](https://cmake.org/download/)
- **MacOS** : Clion IDE used to develop and run found [here](https://www.jetbrains.com/clion/download/#section=mac)

## Getting Started
- Download [Cinder](https://libcinder.org/download)
- Extract the downloaded folder and build libcinder
- create a folder called my-projects in your Cinder folder and clone this repo inside of it
- Open this repo and run cinder-myapp as the target and cinder-myapp as the executible. 
![View on CLion](/images/cinder-myapp.png)
- On Macbooks, you may get an "error = 13, Permissions", in this case do 
Edit configurations -> Executable -> Select Other -> Find my-projects/cinder-myapp/cmake-build-debug/Debug/cinder-myapp/Contents/MacOS/cinder-myapp


**Author**: Angela Luo - [`example@illinois.edu`](mailto:angelal6@illinois.edu)
