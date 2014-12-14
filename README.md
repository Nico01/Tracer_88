Tracer_88
=========

###USING THE 8088 ASSEMBLER AND TRACER TOOLKIT

## Assembling your assembly language programs

Assembler source files have an extension ".s". To create a binary for a
source named "project.s", enter the command:

        as88 project

This performs the assembly, and generates three files:

- `project.88` — The 8088 binary
- `project.#` — A file which links the file positions in the source file to the positions in the binary file
- `project.$` — A copy of the source file which contains included secondary sources and satisfies preferred conventions for the assembly process

## Tracing
Once you have assembled project.s, you can trace it with:

        t88 -t project

The tracer subwindow for the source file displays the "project.$" version.
Instead of using `t88 -t`, you can use `t88 -r`. This just runs the program without
displaying the registers and source code as it is running.
