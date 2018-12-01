MYAPP := nested.out
MYSRC := nested.cpp
MYOBJ := $(MYSRC:.cpp=.o)

.PHONY: clean

all: $(MYAPP)

clean:
	$(RM) $(MYAPP) $(MYOBJ)

$(MYAPP): $(MYOBJ)
	g++ $^ -o $@

%.o: %.cpp
	g++ -c $< -o $@

