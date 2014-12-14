I. GETTING STARTED WITH THE 8088 ASSEMBLER AND TRACER TOOLKIT FOR LINUX

By now you should have unzipped the distribution file and changed to the
linux directory. You should see the following directories:

* as_src
* bin
* examples
* exercises
* trce_src

You should also see these files:

* asinstal.sh
* READ_ME.txt
* release.txt
* syscalnr.h

II. TESTING THE 8088 ASSEMBLER AND TRACER INSTALLATION

1. Change to the examples directory by typing:
        cd examples

2. Run the first example program using the t88 tracer. Type: 

	./t88 HlloWrld

3. You should see the x86 registers in the upper left corner of the screen.
   You should see the source program on the right. The arrow should be
   pointing to the instruction: 

        MOV CX,de-hw

4. Hit the Enter (or Return) key. The arrow should move to the next
   instruction:
  
        PUSH CX

5. Hit Enter five more times. Each time the arrow advances to the next
   instruction. After the fifth hit, text should appear in the output
   window, which is below the registers and program code. It should say:

        Hello World
   or
        Hello World\n

6. Hit Enter five more times. The tracer will exit and you should get a
   shell prompt.

7. If this appears, it looks like everything is working. You are ready
   to use this tool. See Appendix C.8 in the book for more examples.


III. USING THE 8088 ASSEMBLER AND TRACER TOOLKIT

A. INTRODUCTION

This section contains notes intended to help you quickly begin working with
the 8088 Assembler and Tracer Toolkit. For more detailed instructions,
please see Appendix C of the book. 

Now go back up one level by typing:

        cd ..

Here you will find five directories. Their contents are as follows:

* as_src      Source code for the assembler
* bin	      The Linux executable programs as88, s88, and t88
* examples    Example programs with source and executables
	      For your convenience, as88, s88, and t88 are copied here
* exercises   Some programs you can learn from: deskcalc, display, mempager
* trce_src    Source code for the interpreter, s88, and the tracer, t88
	      The difference is that t88 is interactive; s88 is not

B. ASSEMBLING YOUR ASSEMBLY LANGUAGE PROGRAMS

Assembler source files have an extension ".s". To create a binary for a
source named "project.s", enter the command:

	as88 project

This performs the assembly, and generates three files:

	project.88	The 8088 binary

	project.#	A file which links the file positions in the
			source file to the positions in the binary file)

	project.$	A copy of the source file which contains included
			secondary sources and satisfies preferred
			conventions for the assembly process

It is best to do this in the examples directory. Once you have assembled project.s, you
can trace it with

        t88 project

The tracer subwindow for the source file displays the "project.$" version.
Instead of using t88, you can use s88. This just runs the program without
displaying the registers and source code as it is running.

C. COMPILATION OF THE ASSEMBLER AND TRACER TOOLS

C-based source files are provided in the event you ever need to recompile
this software. On Unix and Linux platforms, the command "make" should
recompile the sources and place the binaries in the directories "bin", 
"examples", and "exercise."

To recompile, you need a working gcc compiler installed. If you have one,
you can compile by typing from the linux directory:

	sh asinstal.sh

To see if everything was freshly built, type:

        ls -l */[st]88  */as88
        date

The creation times of all the files listed should be within a minute of
the current time.

D. TRACING

To trace a file, use the command "t88". For example, to trace a file named
"project," enter the command:

	t88 project

This displays the registers, stack, portions of memory, and other
information in a set of windows, enabling you to observe execution.

The tracer executes exactly on assembler command when the return key is hit.
To stop execution, type the command "q", followed by a return. Execution
stops on its own when the process itself exits.

To interpret a file without displaying the tracer window, use the s88
Command. For example, to interpret a file named "project," enter the
command:

	s88 project

The entire assembler project uses command line terminal windows. This is
commonplace on Posix compliant systems, but less typical for Windows
platforms.

Additional notes on the current implementation, known bugs, and
restrictions can be found in the file release.txt in this directory.

Good Luck,
Evert Wattel
Vrije Universiteit, Amsterdam
evert@cs.vu.nl (or e.wattel@few.vu.nl)
