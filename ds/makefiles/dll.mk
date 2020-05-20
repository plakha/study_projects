#reference lining exercise in system_programming directory
#points to mind: LD_LIBRARY_PATH, link in order of dependncy
#FOR_DEBUG=-g
#FOR_PROD=-DNDEBUG -03
#ifeq($(DEBUG),0)
#CFLAGS=$(FOR_DEBUG)
#else
#CFLAGS=$(FOR_PROD)
#endif

CC=gcc -ansi -pedantic-errors -Wall -Wextra 

../bin/dll.out: ../obj/dll_test.o ../lib/dll.so
	$(CC) -o ../bin/dll.out ../obj/dll_test.o ../lib/dll.so

../lib/dll.so: ../obj/dll.o
	$(CC) -shared -fpic -o ../lib/dll.so ../obj/dll.o
	
../obj/dll.o: ../src/dll.c ../include/dll.h
	$(CC) -c -fpic -o ../obj/dll.o ../src/dll.c
	
../obj/dll_test.o: ../test/dll_test.c ../include/dll.h
	$(CC) -c -fpic -o ../obj/dll_test.o ../test/dll_test.c
