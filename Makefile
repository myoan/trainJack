cc = gcc
cflags = -W -Wall -O2 -g0
#cflags = -W -Wall -O0 -g3
obj = trainjack.o debug.o

.PHONY: all
target = trainjack
all: $(target)
$(target): $(obj)
	$(cc) -o $(target) $(obj)
trainjack.o: trainjack.c
	$(cc) $(cflags) -c $<
debug.o: debug.c
	$(cc) $(cflags) -c $<

.PHONY: clean
clean:
	rm -rf $(target) $(obj)
