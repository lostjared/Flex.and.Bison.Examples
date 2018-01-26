# Simple practice project

Just using this as a way to test out some of the things I have been reading about.
To build use

$ make flex && make

to build with debug output info use

$ make clean && make flex && make debug

Also to run the program without debug information use:

for using the stdin

$ ./cc-test

or

for using a text file

$ ./cc-test script.exp

for Information about what is happening use debug build like this

for using the stdin

$ ./cctest-debug

or use a file

$ ./cctest-debug script.exp
 
