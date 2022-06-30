C = clang -pedantic -Wall -ggdb -std=c11
OBJS = staticlist.o
BINS = test.out

all: $(BINS)

staticlist.o: staticlist.c staticlist_p.h
	$(C) -c $< -o $@

test.out: test.c $(OBJS)
	$(C) $< $(OBJS) -o $@

clean:
	rm $(OBJS) $(BINS)

test:
	./test.out

