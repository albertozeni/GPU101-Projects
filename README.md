## Introduction
<p align="justify">
This repository contains all the programs that you have to use as a starting point for the GPU-101 Projects.
</p>

## Usage

### Compilation

You only need GCC to compile the various programs, which you should already have installed if you did already setup your maching for CUDA.
To compile all the examples simply type
```
make
```
Within the scope of this folder.
Note that the examples are all compiled using the -O3 flag, you have to use this flag also when compiling the GPU version of the code using nvcc.
All the parameters regarding input settings CANNOT BE CHANGED.
The smith-waterman algorithm is the only one that generates all the inputs at runtime, while for symgs and spmv you should also use a sparse matrix as input (the program will not run without it).
The one you should use for all of your comparisons has already been prepared for you and is available here:

https://www.dropbox.com/s/jzn573j0z9ffl7h/kmer_V4a.mtx?dl=0

You can fork this repo and use this as a starting point for your project.
Remember to include all your source code as well as a PDF (4/5 pages) with your project report in the repository.
Please DO NOT send me your repository, instead write the address of your repo in this shared google drive:

https://docs.google.com/spreadsheets/d/14sAdNkW2cGFkbGSs7X1Nzru4U0QvoxK1QYq7gB6e2pk/edit?usp=sharing

For the sake of convenience here is also the file containing the assigned project for all the partecipants to GPU-101: 

https://docs.google.com/spreadsheets/d/1FuVhxWxUPu5AtFw8xdbQEwp-se8vmi1xHnbswostcLs/edit?usp=sharing

NOTE: you cannot change your assigned project, and copying each others project will be considered cheating and will result in you not passing the course.
