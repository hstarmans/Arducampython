# ArducamPython

Python wrapper for Arducam library. 
Tested at commit hash for both raspberry pi 4 and 3B. 
```
commit 7f75cf1e0f870ba9eb567d71c5e09702b8a9f395 (HEAD -> master, origin/master, origin/HEAD)
Author: UCTRONICS <avahe@uctronics.com>
Date:   Wed Jan 13 09:05:18 2021 +0800

    Fix Ethernet problems
```
Logs are printed during interaction with the driver, but is due to the binary and not the python wrapper.
E.g. ```cam.set_mode(0) results in a Can't open file.```
This specific error is due to lens shading which cannot be found.

## Installation
Install requirements;
```
pip3 install pybind
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
## Compile Notes
```
cmake -H. -Bbuild & make -C ./build
```
Errors can be damangled with https://demangler.com/
