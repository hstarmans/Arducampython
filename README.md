# ArducamPython

Python wrapper for Arducam UC-621. Only works with this camera on linux distro bullseye. Arducam has newer version with the same chip 
which uses a more recent version based on libcam.
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
git clone --recurse-submodules git@github.com:hstarmans/Arducampython.git
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
python3 test/test.py Tests.pythonpreview
```
## 64 bit
Camere works with 64 bit binary, you have to look in subfolders of https://github.com/ArduCAM/MIPI_Camera for this.
```
https://github.com/RPi-Distro/raspi-gpio
```
Vchiq fails and can only be fixed by setting permissions.
A usefull blog is [site](https://zengliyang.wordpress.com/2021/01/04/raspberry-pi-4b-ubuntu-20-04-camera/).
Best would be to try reproduce above with classical camera.

## Compile Notes
```
cmake -H. -Bbuild & make -C ./build
```
Errors can be damangled with https://demangler.com/
