cc = gcc
cflags = -W -Wall -O0 -g3
obj = trainjack.o
src = trainjack.c

.PHONY: all
target = trainjack
all: $(target)
$(target): $(obj)
	$(cc) -o $(target) $(obj)
trainjack.o: $(src)
	$(cc) $(cflags) -c $<

.PHONY: clean
clean:
	rm -rf $(target) $(obj)
