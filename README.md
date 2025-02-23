# C/C++ Project Manager (CPM)
<div align="center">
  <a href=https://github.com/vkeshav300/cpm/actions/workflows/codeql.yml><img src=https://github.com/vkeshav300/cpm/actions/workflows/codeql.yml/badge.svg></img></a>
  <a href=https://github.com/vkeshav300/cpm/actions/workflows/pages/pages-build-deployment><img src=https://github.com/vkeshav300/cpm/actions/workflows/codeql.yml/badge.svg></img></a><br>
  <img height=256 src=assets/CPM_LOGO.png></img>
  <p>CPM is a simple, yet useful tool for managing your C and C++ projects.</p><br>
  <img src=assets/readme/1.png>
  <img src=assets/readme/2.png>
</div>

### Operating System Support
Currently supports the following operating systems:
- All unix-based operating systems

### Building / Installing
#### Unix-Based Operating Systems
For building project (you may need to use sudo if you are getting `access denied` or `permission not granted` errors):
```
mkdir build
cd build
cmake ..
make
```
For building project and installing:
```
mkdir build
cd build
cmake ..
sudo make install
```
#### Arch Linux(AUR)
See [aur.archlinux.org/packages/cpm-git](https://aur.archlinux.org/packages/cpm-git) for package details.
Instalation command:
```
paru -S cpm-git
```

### Issues
All bug reports, feature requests and other issues are monitored at the [GitHub issue tracker](https://github.com/vkeshav300/cpm/issues).

### Other Information
The code uses 256-Color Mode [ANSI Escape Codes](https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797) to color text. Not all terminals support coloring text. To check if your terminal does, run: 
```
echo -e "\x1b[38;5;196mTest\x1b[0m"
```
This should print the text "Test" in a red-ish color. Most modern terminals support coloring using ANSI Escape Codes.
