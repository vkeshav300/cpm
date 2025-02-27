# Contribution Guidelines
### Code formatting
Format code to follow LLVM formatting guidelines.
The easiest way to do that is via the clang-format command or llvm-based formatters.
For the clang-format command, the .clang-format file already exists in the main project directory.
Example:
```
clang-format -i src/*.cpp include/*.h src/commands/*.cpp include/commands/*.h
```

### Code documentation
If possible, please include DOXYGEN style code documentation. To create a pdf with all the code documentation, run:
```
cd docs
doxygen
cd output/latex
make
open refman.pdf
```