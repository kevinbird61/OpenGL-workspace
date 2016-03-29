# OpenGL-workspace
Experiment and Practice on openGL . 

## How to build linux openGL environment
1. install your GPU driver.

* If using virtual machine , please type those in terminal to install mesa opengl : 
* `sudo apt-get(or -fast) install libgl1-mesa-dev`

2. install necessary package.

* `sudo apt-get install build-essential xorg-dev git cmake (doxygen)`

3. download `glfw3` and compile 

* `git clone https://github.com/glfw/glfw.git`
* `cd glfw` 
* `cmake`
* `make`
* `sudo make install`
