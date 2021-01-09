# ArducamPython

Python wrapper for Arducam library. The official library provided by Arducam does not work
on Raspberry 4. The camera driver can also lead to kernel failures.
Another known error is that cam.set_mode(0) results in a Can't open file.
This is as the lens shading cannot be found, however lens shading is not needed in my case.

## Installation
Install requirements;
```
pip3 install pybind
sudo apt -y install cmake
```
Install [Arducam python](https://github.com/ArduCAM/MIPI_Camera), run camera_i2c detect in utils folder
and try ./arducamstill -?.  If there is a kernel failure, fix [wiringpi](https://github.com/ArduCAM/MIPI_Camera/issues/82).
Install this library;
```
python3 setup.py install --user
```
Run the test
```
python3 test/test.py
```
## Compile Notes
```
cmake -H. -Bbuild & make -C ./build
```
Errors can be damangled with https://demangler.com/