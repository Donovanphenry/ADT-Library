#------------------------------------------------------------------------------
#  Makefile for CSE 101 Programming Assignment 7
#
#  make                     makes Arithmetic
#  make BigIntegerTest		makes BigIntegerTest module
#  make clean               removes all binaries
#  make memcheck            tests for memory leaks
#  make memcheckTest		tests for memory leaks in BigIntegerTest
#------------------------------------------------------------------------------

CLIENT         = Arithmetic
ADT1           = BigInteger
ADT2           = List
TEST1		   = $(ADT1)Test
TEST2		   = $(ADT2)Test
SOURCE         = $(CLIENT).c
OBJECT         = $(CLIENT).o
ADT1_SOURCE    = $(ADT1).c
ADT1_OBJECT    = $(ADT1).o
ADT1_HEADER    = $(ADT1).h
ADT2_SOURCE    = $(ADT2).c
ADT2_OBJECT    = $(ADT2).o
ADT2_HEADER    = $(ADT2).h
TEST1_SOURCE   = $(TEST1).c
TEST1_OBJECT   = $(TEST1).o
TEST2_SOURCE   = $(TEST2).c
TEST2_OBJECT   = $(TEST2).o
COMPILE        = gcc -c -std=c11 -Wall
LINK           = gcc -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

$(CLIENT) : $(OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)
	$(LINK) $(CLIENT) $(OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)

$(TEST1) : $(TEST1_OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)
	$(LINK) $(TEST1) $(TEST1_OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)

$(TEST2) : $(TEST2_OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)
	$(LINK) $(TEST2) $(TEST2_OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)

$(OBJECT) : $(SOURCE) $(ADT1_HEADER) $(ADT2_HEADER)
	$(COMPILE) $(SOURCE)

$(TEST1_OBJECT) : $(TEST1_SOURCE) $(ADT1_HEADER) $(ADT2_HEADER)
	$(COMPILE) $(TEST1_SOURCE)

$(TEST2_OBJECT) : $(TEST2_SOURCE) $(ADT1_HEADER) $(ADT2_HEADER)
	$(COMPILE) $(TEST2_SOURCE)

$(ADT1_OBJECT) : $(ADT1_SOURCE) $(ADT1_HEADER)
	$(COMPILE) $(ADT1_SOURCE)

$(ADT2_OBJECT) : $(ADT2_SOURCE) $(ADT2_HEADER)
	$(COMPILE) $(ADT2_SOURCE)

clean :
	$(REMOVE) $(CLIENT) $(OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)

memcheck : $(CLIENT)
	$(MEMCHECK) $(CLIENT) in5 out5

memcheckBigIntTest : $(TEST1)
	$(MEMCHECK) $(TEST1)

memcheckListTest : $(TEST2)
	$(MEMCHECK) $(TEST2)