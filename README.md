# SBAC-PAD-marathon-problems

## Problems

You can check a compiled table of all problems at Problems.md

## Compiling and Running

* Navigate to the directory containing the problem
* Compile the problem
  ```
  make clean
  make -j
  ```
* Run the problem (where `X` is the letter of the problem)
  ```
  bash X.sh
  ```

## Contributing

You can contribute by providing parallel solutions to problems. When creating a PR, please make sure that your solution is placed at correct year directory, inside a folder with the nome of parallel tool, in lowercase letters.

**Example:** You want to provide an OpenMP parallel solution for problem A from year 2014

Your implementation should be placed in
```
2014/openmp/A
```
All commands to compile it must be placed in its `Makefile`, and all the necessary steps to run the parallel solution should be placed in the problem script (e.g. `A.sh` file).

### Formatting

This repository provides a `.clang-format` file. Feel free to use it in your solutions and suggest improvements.

## Disclaimer

All problems were extracted from SBAC-PAD Marathon of Parallel Programming website. You can visit it at http://lspd.mackenzie.br/marathon/