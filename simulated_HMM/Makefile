BUILD_TYPE=DEFAULT
TEST_FILE=stress_test.c # Default test file

all: myHMM clean  

ifeq ($(BUILD_TYPE), DEBUG)
CFLAGS= -g
endif

stress_test.o: $(TEST_FILE) myHMMheader.h
	gcc $(CFLAGS) -o stress_test.o -c $(TEST_FILE)

myHMM: myHMM.o stress_test.o 
	gcc $(CFLAGS) -o myHMM myHMM.o stress_test.o
	
clean:
	@rm -f *.o 



