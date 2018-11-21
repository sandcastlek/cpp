MY_APP = sorting_app
#MY_LIBPATH = ../../library/build/linux64
MY_LIBPATH = ../../../library/build/linux64
MY_LIB = sorting
MY_OBJS = sorting_app.o

VPATH = ../../src:$(MY_LIBPATH)

all: $(MY_APP)

.PHONY: clean
clean:
	$(RM) $(MY_APP) $(MY_OBJS)

%.o: %.cpp
	g++ -c $< -o $@

#$(MY_APP): $(MY_LIB) $(MY_OBJS)
$(MY_APP): $(MY_OBJS)
	g++ $(MY_OBJS) -L$(MY_LIBPATH) -l$(MY_LIB) -o $@




