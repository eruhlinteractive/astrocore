A game creation framework based on the Raylib library

** CAUTION: THIS FRAMEWORK IS CURRENTLY IN PRE-ALPHA AND IS NOWHERE NEAR FEATURE COMPLETE. USE AT YOUR OWN RISK **

# Description
Astrocore is a set of general-purpose game systems designed to increase the speed of 'spartan' game development. The features are intended to add another level of functionality above popular game libraries like [XNA/Monogame](https://monogame.net/) and [Raylib](https://www.raylib.com/), without implmenting a full GUI application or build pipeline. 

Added features include:
- Main gameloop (update/fixed update/ draw) propogation through all entites
- Flexible 'node' based entity system inspired by the [Godot](https://godotengine.org/) game engine
- Input binding management

Upcoming features include:
- Audio framework
- Lightweight 2D physics
- Resource management
- File IO system


# Usage
1. Download, build and install Raylib as a static library as described [here](https://github.com/raysan5/raylib?tab=readme-ov-file#build-and-installation)
2. Install vcpkg/cmake as described [here](https://learn.microsoft.com/en-us/vcpkg/get_started/get-started?pivots=shell-cmd)
3. Run make to build the library, or include the source directly in your project
4. *Profit(?)*
