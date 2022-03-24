# Complex C++ Calculator

This program is an example of what happens when a project scope goes beyond the allotted time allocated to it.
While the design of the program is feasible, the implementation is not successful as there are a few invalid memory accesses
 attempted by the program which still need to be ironed out.

## Program Design
The program takes in a valid mathematical expression. It then parses out all spaces using native string functionality.

This parsed mathematical expression is then sent to a function that uses the postfix method to calculate the answer.
This function uses a stack of doubles to hold the operands, and a stack of chars to hold the operators.
It then loops through the mathematical expression string and follows a series of several conditions.

If an operator causes another operator on the stack to pop, it then calls a function to take the operator and the two most 
recent operands to perform a calculation. The result is then pushed back onto the operand stack.

The goal is to have one operand left on the operand stack: the answer. And no operators left on the operator stack.

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
make lab2
```

To build the program without using make, execute the following in your terminal:

```bash
gcc -o build main.cpp -lstdc++ -std=c++14
```

Either of these commands will build the program. 
A "build" file will be created in your root directory.
You can run this build file by executing:

```bash
./build
```

## How to Use this Program

Change the hardcoded testcase1 value to one that you'd like to test before building this program.
The program expects any of the following characters:

**Addition: +**

**Subtraction: -**

**Multiplication**

**Division: /**

**Exponentiation: ^**

**Open Parentheses: (**

**Close Parentheses: )**

When running the program, the test case will be evaluated.
