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

### Releases
#### Tag
When creating a release tag, create a new tag in the format of `vX.X.X` or `vMajor.Minor.Patch`. This is to avoid breaking the auto update scanning feature of CPM, where it's functioning relies on the first character in the version tag being v, and the rest being positive integers separated by commas.

#### Sumarry + release notes
Create a short summary for the release describing the changes at the very top of the release description. You can create your own release notes, or just use GitHub's feature for creating release notes automatically.

### Creating commands
CPM uses an object-oriented approach for managing commands. To create a command, create a new class file pair inside the `include/comands` and `src/commands` folders which inherits from the `Command` interface. Then add it to the command manager in `main.cpp`. Try your best to add DOXYGEN style code documentation to the new command.
