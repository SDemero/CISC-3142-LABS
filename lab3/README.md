# BC Grade Rates Reporter

## Purpose

This program takes in a set of formatted input files (see input files section below) 
displaying course information and grades per student. The program then processes *all* the 
input files and creates a map of courses to student grades. These grades are then processed 
to show the rates of each type of grade per course information attribute based on the type 
of report chosen.


## How to Run this Program
1. Clone the repository:
``git clone https://github.com/makmn1/CISC-3142-LABS``
2. Move into the lab3 directory:
`cd lab3`
3. Right now, the data directory is empty since it is a submodule.
Git does not add submodules when cloning a repository.
You can have Git add the submodule by running:`git submodule update --init`.
You can also add your own data files by following the *Input File Format* section below.
6. Build the program using the provided Makefile by running: `make lab3`
7. After the program finishes building, it will automatically execute the program. 
You can execute the program again in the future by running: `./a.out`


## Report Generation
### Report Types
The following types of reports are available:

1. Rates by Instructor
2. Rates by Course
3. Rates by Course & Semester

Data files are included in the data directory of the repository as a submodule.

### Input File Format

The input file must have the following types of headings in the same order:
- EMPLID : Student Identification Number. This is not used anywhere in the program.
- COURSENO : A string representing a course.
- INSTRUCTORID : A string representing an instructor.
- TERMID: A string representing a term.
- SECTIONID: A string representing a section.
- GRADE*: A string representing a grade.

Note that the names of these headings can be anything, but it is important they show up in the same order as above.


*Only the following grades are allowed:
- A+
- A
- A-
- B+
- B
- B-
- C+
- C
- C-
- D+
- D
- D-
- F
- WD
- W
- WN
- WU
- INC
- FIN
- CR
- P
- NC
- AUD