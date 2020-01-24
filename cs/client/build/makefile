MY_APP := clientLin
MY_SRC := client_lin.cpp
MY_OBJS := $(MY_SRC:.cpp=.o)
CXXFLAGS := -g3 -std=c++11

VPATH = ../src

.PHONY: clean all

all: $(MY_APP)

clean: 
	@echo $(value CXXFLAGS)
	$(RM) $(MY_APP) $(MY_OBJS)

$(MY_APP): $(MY_OBJS)
	g++ $(CXXFLAGS) $^ -o $(MY_APP) -lpthread

%.o: %.cpp
	g++ $(CXXFLAGS) -c $< -o $@


