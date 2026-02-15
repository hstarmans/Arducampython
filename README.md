# 📸 Arducam UC-621 Python Wrapper

This project provides a high-performance Python wrapper for the Arducam UC-621 (OV2311) camera. 
Python wrapper for Arducam UC-621. Only works with this camera on linux distro bullseye. Arducam has newer version with the same chip 
which uses a more recent version based on libcam.
Tested at 15-2-2026.  
Logs are printed during interaction with the driver, but is due to the binary and not the python wrapper.
E.g. ```cam.set_mode(0) results in a Can't open file.```
This specific error is due to lens shading which cannot be found.

## Installation
Install requirements;
```
git clone https://github.com:hstarmans/Arducampython.git
uv sync
```
Install [Arducam python](https://github.com/ArduCAM/MIPI_Camera) and try ./capture.  If there is a kernel failure, fix [wiringpi](https://github.com/ArduCAM/MIPI_Camera/issues/82), and run the i2cdetect script in utils.
```
uv run python setup.py install
```
Run the test
```
uv run python test/test.py Tests.pythonpreview
```

## Arducam Notes
Installing arducam requires adding simlinks to the right libraries for opencv and mmal.  
Also had to leave 'i2c-dev' in '/etc/modules-load.d/modules.conf'.

## Compile Notes
```
cmake -H. -Bbuild & make -C ./build
```
Errors can be damangled with https://demangler.com/
