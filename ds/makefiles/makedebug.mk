CC = gcc -ansi -pedantic-errors -Wall -Wextra -g

HDR = $(shell gcc -MM ../src/$(NAMESPACE).c)

HDR := $(filter %.h, $(HDR))

OBJ = $(patsubst ../src/../include/%.h, ../obj/%.o, $(HDR))

../bin/$(NAMESPACE)_d.out : ../obj/$(NAMESPACE)_test.o ../lib/lib$(NAMESPACE).so 
	$(CC) -o $@ $^

../lib/lib$(NAMESPACE).so : $(OBJ)
	$(CC) -shared -o $@  $^

../obj/%.o : ../src/%.c
	$(CC) -c -fPIC -o $@ $<
	
../obj/$(NAMESPACE)_test.o : ../test/$(NAMESPACE)_test.c ../include/$(NAMESPACE).h
	$(CC) -c -o $@ $<



