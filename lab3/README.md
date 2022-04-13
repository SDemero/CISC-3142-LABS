# BC Grade Rates Reporter

## Purpose

This program takes in a set of formatted input files (see input files section below) 
displaying course information and grades per student. The program then processes *all* the 
input files and creates a map of courses to student grades. These grades are then processed 
to show the rates of each type of grade per course information attribute based on the type 
of report chosen.

## Report Generation

### Report Types
The following types of reports are available:

1. Rates by Instructor
2. Rates by Course
3. Rates by Course & Semester

Data files are included in the data directory of the repository. They are passed to the 
program as command-line arguments. The data files in this repository are examples. You 
can add more data files as long as they follow the same format (meaning they must have the 
same number of columns with the same type of data).

