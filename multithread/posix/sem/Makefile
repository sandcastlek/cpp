MY_APP := sem_app
SRCS   := sem_app.cpp
OBJS   := $(SRCS:.cpp=.o)

all: $(MY_APP)

$(MY_APP): $(OBJS)
	g++ $^ -o $@ -lpthread

%.o: %.cpp
	g++ -c $< -o $@

.PHONY: clean
clean:
	$(RM) $(OBJS) $(MY_APP)

