README
======

This package includes the following files.

|-- Caller.c [This is the driver program which will be used to invoke the MemoryManager.]
|-- CreateArray.c [CreateArray is implemented here. The file has a few helper funcitons and a primary function, get_running_ratio, which gets the average of even odd ratios from the arrays that are created, populated, and destroyed with random values give ]
|-- CreateArray.h [Header file declaring the function exposed from CreateArray]
|-- README.txt [This file]

Use the provided makefile as a template.

To compile:
    gcc *.c

To run:
    ./a.out <seed>

For example;
    ./a.out 1234

