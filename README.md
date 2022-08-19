# ArducamPython

Python wrapper for Arducam library test with 32bit and 64bit.  
Tested at 14-8-2022.  
Logs are printed during interaction with the driver, but is due to the binary and not the python wrapper.
E.g. ```cam.set_mode(0) results in a Can't open file.```
This specific error is due to lens shading which cannot be found.

## Installation
Install requirements;
```
git clone --recurse-submodules https://github.com:hstarmans/Arducampython.git
sudo apt install i2c-tools
sudo apt-get install python3-pybind11
sudo apt -y install cmake
```
Install [Arducam python](https://github.com/ArduCAM/MIPI_Camera) and try ./capture.  If there is a kernel failure, fix [wiringpi](https://github.com/ArduCAM/MIPI_Camera/issues/82), and run the i2cdetect script in utils.
```
python3 setup.py install --user
```
Run the test
```
python3 test/test.py
```
## Arducam Notes
Installing arducam requires adding simlinks to the right libraries for opencv and mmal.  
Also had to leave 'i2c-dev' in '/etc/modules-load.d/modules.conf'.

## Compile Notes
```
cmake -H. -Bbuild & make -C ./build
```
Errors can be damangled with https://demangler.com/
