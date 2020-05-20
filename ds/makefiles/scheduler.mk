TRUE=1
CC=gcc -ansi -pedantic-errors -Wall -Wextra 
#ifeq($(DEBUG),$(TRUE))
#	CFLAGS=:-g
#else
#	CFLAGS=:-DNDEBUG -03
#endif
DEPS=../include/dll.h

../bin/dll.out: ../obj/dll_test.o ../lib/dll.so
	$(CC) -o $@ $^ $(CFLAGS)

../lib/dll.so: ../obj/dll.o
	$(CC) $(CFLAGS) -shared -o $@ $^  # or $< ?
	
../obj/dll.o: ../src/dll.c $(DEPS)
	$(CC) $(CFLAGS)-c -fpic -o $@ $<
	
../obj/dll_test.o: ../test/dll_test.c ../include/dll.h
	$(CC) -c -o $@ $< $(CFLAGS)
	
.PHONY:clear

clear:
	rm -v ../obj/*.o
	rm -v ../bin/*.out
	rm -v ../bin/*.elf
