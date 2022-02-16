# Simple C++ Data Parser

This program reads the given csv file and generates a report based on the input file's data.

## Report Generation
This program outputs to both the console and an output file called output.txt.

## Installation

### Installing A C++ Compiler
The Makefile assumes you have the GNU Compiler Collection (GCC). If you do not, then you can install it by following the links below.

[For Linux Users](https://linuxize.com/post/how-to-install-gcc-compiler-on-ubuntu-18-04/)

[For Windows Users](https://sourceforge.net/projects/mingw/) (this is a GCC package manager)

### Installing Makefile
Make sure to have Makefile installed using:

```bash
sudo apt install make
```
If you are using a Windows machine and you do not have access to a Unix/Linux environment, install the [Windows Subsystem for Linux 2 (WSL2)](https://docs.microsoft.com/en-us/windows/wsl/install). This will create a Linux virtual machine for you to run this script and to use Makefile.

## Usage

Run the following command in the root directory of the cloned repository to build the *project*.

```bash
make -f lab1.mak
```

To build the program without using make, execute the following in your terminal:

```bash
gcc -o build main.cpp -lstdc++ -std=c++98
```

Either of these commands will build the program. 
A "build" file will be created in your root directory.
You can run this build file by executing:

```bash
./build
```
