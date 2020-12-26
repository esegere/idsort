# idsort
[![CMake Actions Status](https://github.com/esegere/idsort/workflows/CMake/badge.svg)](https://github.com/esegere/idsort/actions)

	a utility to sort info inspired by IBM DFSORT utility

## required arguments

\[File\]

-O, --output-file \[File\]

## flags

-f, --field=field\[/field\]...

	defaults to the whole line

## field syntax

field		->		start\:length\:type\:order

	start		->	the number of column where the field begins, the first column is 1, if omitted defaults to 1

	length		->	the number of characters in the field, if omitted defaults to the end of the line

	type		->	N for numbers or S for strings, if omitted defaults to string

	order		->	A for ascending or D for descending, if omitted defaults to ascending

## installation

### prerequisites

- a c++17 capable compiler
- make
- cmake

### process

clone this repository, make a build directory inside the project repository, then run the cmake and make install commands

```shell script
git clone https://github.com/esegere/idsort
cd idsort
mkdir build
cd build
cmake ..
sudo make install
```