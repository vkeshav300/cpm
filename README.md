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
By default, CPM checks for updates every time you run a valid command. This does cause lag, however, and to get rid of this lag you can run:
```
cpm config set update_scanning off
```
which disables auto-update scanning. At the moment, CPM does not auto-update, and will only alert you when a newer version is availible.

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
