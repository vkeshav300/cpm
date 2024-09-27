# [C/C++ Project Manager](https://github.com/vkeshav300/cpm) (CPM)
[![CodeQL](https://github.com/vkeshav300/cpm/actions/workflows/codeql.yml/badge.svg)](https://github.com/vkeshav300/cpm/actions/workflows/codeql.yml)
[![pages-build-deployment](https://github.com/vkeshav300/cpm/actions/workflows/pages/pages-build-deployment/badge.svg)](https://github.com/vkeshav300/cpm/actions/workflows/pages/pages-build-deployment)
[![Latest Release](https://img.shields.io/badge/Latest_Release-None-blue.svg?style=rounded-square)](https://github.com/vkeshav300/cpm/releases)
[![License](https://img.shields.io/badge/License-CC0_1.0_Universal-yellow.svg?style=rounded-square)](https://github.com/vkeshav300/cpm/blob/master/LICENSE)

### General information
CPM is a useful tool for managing your C and C++ projects. *Note from devs: don't expect changes / updates / releases to be frequent as we are making this software on our own time without a strict schedule.*

### Building
For building project normally (you may need to use sudo if you are getting `access denied` or `permission not granted` errors):
```
cd build
cmake ..
make
```
For building project and installing locally:
```
cd build
cmake ..
sudo make install
```
### Other information
The code uses 256-Color Mode [ANSI Escape Codes](https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797) to color text. Not all terminals support coloring text. To check if your terminal does, run: 
```
echo -e "\x1b[38;5;196mTest\x1b[0m"
```
This should appear red in your terminal. Most modern terminals support this feature.
