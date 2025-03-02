<div align="center">
  <img height=256 src=assets/CPM_LOGO.png><br>
  <p>CPM is a simple, yet useful tool for managing your C and C++ projects.</p>
  <br>
  <a href=https://github.com/vkeshav300/cpm/actions/workflows/codeql.yml><img src=https://github.com/vkeshav300/cpm/actions/workflows/codeql.yml/badge.svg></a>
  <a href=https://github.com/vkeshav300/cpm/actions/workflows/pages/pages-build-deployment><img src=https://github.com/vkeshav300/cpm/actions/workflows/pages/pages-build-deployment/badge.svg></a>
  <br><br>
  <h2>Quick Navigation</h2>
  <a href="https://github.com/vkeshav300/cpm/releases/?include_prereleases&sort=semver"><img src="https://img.shields.io/github/tag/vkeshav300/cpm"></a>
  <a href="https://github.com/vkeshav300/cpm?tab=readme-ov-file#updating"><img src="https://img.shields.io/badge/Updating-grey"></a>
  <a href="https://github.com/vkeshav300/cpm/issues"><img src="https://img.shields.io/badge/Issue_Tracker-grey"></a>
  <a href="https://github.com/vkeshav300/cpm?tab=readme-ov-file#building--installing"><img src="https://img.shields.io/badge/Installation_/_Building-blue"></a>
  <br><br>
  <h2>Examples</h2>
  <img src=assets/readme/1.png>
  <img src=assets/readme/2.png>
</div>

### Operating System Compatability
CPM currently is compatable with the following operating systems:
- All unix-based operating systems

### Building / Installing
#### Unix-Based Operating Systems (build it yourself)
For installation in release mode, type the following commands in the project root directory:
```
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
sudo make install
```
note that this will require the installation of cmake, make, and any other dependencies the project has.

#### AUR / Arch Linux (package installation)
See [aur.archlinux.org/packages/cpm-git](https://aur.archlinux.org/packages/cpm-git) for package details.
Installation command:
```
paru -S cpm-git
```
May not update by default via `paru -Syu`. To check for updates more accurately please run:
```
paru -Sy cpm-git
```

### Updating
To check for updates for CPM, run:
```
cpm scan
```
CPM automatically scans for updates occasionally when a command is run. To set the frequency of automatic update scanning run:
```
cpm scan -f=[n]
```
where n is after how many commands you want to run an update scan. To disable automatic update scanning run:
```
cpm scan --off
```
or to enable automatic update scanning run:
```
cpm scan --on
```
Scanning for updates will cause lag, which is why CPM doesn't automatically scan for updates every time it is used.

### Issues
All bug reports, feature requests and other issues are monitored at the [GitHub issue tracker](https://github.com/vkeshav300/cpm/issues).

### Text Coloring
The code uses 256-Color Mode [ANSI Escape Codes](https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797) to color text. Not all terminals support coloring text. To check if your terminal does, run: 
```
echo -e "\x1b[38;5;196mTest\x1b[0m"
```
This should print the text "Test" in a red-ish color. Most modern terminals support coloring using ANSI Escape Codes.

If your terminal does NOT support `256-Color Mode ANSI Escape Codes`, run the following command to disable text coloring:
```
cpm config set text_coloring off
```
