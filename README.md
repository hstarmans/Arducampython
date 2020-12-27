# ArducamPython

Python wrapper for Arducam library. The official library provided by Arducam does not work.
A known error is that cam.set_mode(0) results in a Can't open file.
This is as the lens shading cannot be found, however lens shading is not needed in my case.

## Installation
```
pip3 install pybind
sudo apt -y install cmake
```
## Compile Notes
```
cmake -H. -Bbuild & make -C ./build
```
Errors can be damangled with https://demangler.com/