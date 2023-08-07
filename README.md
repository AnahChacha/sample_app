# POS CMake Project template

POS visual studio project exported to CMake. This template should you get you started with a POS project. 
You can then tighten your code quality by simply editing the CMake template and even include a testing framework.

## Requirements (must all be on path)
- Cmake
- Ninja (optional)
- Vanstone Tools on path and installed on ```C:\tools\```
- Code editor / Preferred IDE(CLion, Visual studio)
## Setup
1. Create a project using this template.
2. Wait for template janitor action to complete.
3. Clone the project.
4. 1. ```mkdir build && cd build```
   2. ```cmake ..```  
      -  Everytime you run this command a visual studio solution and project file are created from templates
      -  Required for successful vanstone build

## Vanstone VM Build
- This CMake setup so far do not integrate well with Vanstone VM which depends on correct location
the visual studio project file (WIP)
- However, by running a cmake build as directed above will generated vcproj file using a template. 
- Then open the project in visual studio, run and complete the vanston build (which is only necessary during
deployment)
- Simply develop using CLion(best for code formatting and error spotting) and deploy with visual studio.

