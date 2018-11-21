
MY_LIB = sorting.a
MY_OBJS = sort.o

VPATH = ../../src

all: $(MY_LIB)

%.o: %.cpp
	g++ -c $< -o $@

$(MY_LIB): $(MY_OBJS)
	ar rcs $@ $(MY_OBJS)
	cp $(MY_LIB) lib$(MY_LIB)

.PHONY: clean
clean:
	$(RM) $(MY_LIB) $(MY_OBJS) *.o *.a

