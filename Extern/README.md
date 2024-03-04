# Setting up External dependencies

Make a copy of ```Example_CMakeLists.txt``` and re-name it to just ```CMakeLists.txt```.
This file will set 4 different CMake variables, 2 for box2d and 2 for glfw3.
As of now the CMake is designed to use the static library versions,
so make sure you're not trying to use a DLL file.

## opengl

Should already be installed on your OS

## Box2d

Pull down the [box2d repository](https://github.com/erincatto/box2d)
from github and follow the install instructions.

- ```EXTERNAL_BOX2D_INCLUDE``` -- Should point to your box2d's ```include directory```
- ```EXTERNAL_BOX2D_LIBRARY``` -- Should point to your compiled box2d ```library file```.

## GLFW3

Download the precompiled binaries from the [GLFW website](https://www.glfw.org/download.html).
When you decompress the downloaded zip file,
you will see an ```include``` directory as well as multiple ```lib-<...>``` directories.

- ```EXTERNAL_GLFW_INCLUDE``` -- Should point to the ```include directory```
- ```EXTERNAL_GLFW_LIBRARY``` -- Should point to the appropriate ```library file``` for your compiler
