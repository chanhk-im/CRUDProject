CC = gcc
CFLAGS = -g -Wall
TARGETS = main
OBJECTS = Main.o UsedProduct.o
.SUFFIXES = .c .o

main_debug: $(TARGETS)
main_debug: DEBUGOPTION = -DDEBUG

$(TARGETS): $(OBJECTS)
	$(CC) $(CFLAGS) $(DEBUGOPTION) -o $@ $^

.c.o:
	$(CC) $(CFLAGS) $(DEBUGOPTION) -c $<

clean:
	rm *.o $(TARGETS)

exec: main
	./main
