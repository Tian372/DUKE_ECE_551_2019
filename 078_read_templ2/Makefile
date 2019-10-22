CFLAGS=-Wall -Werror -std=gnu++98 -pedantic -ggdb3
SRCS=$(wildcard *.cpp)
OBJS=$(patsubst %.cpp, %.o, $(SRCS))
PROGRAM= code

$(PROGRAM): $(OBJS)
	g++ $(CFLAGS) -o $@ $(OBJS)


clean:
	rm -f $(OBJS) $(PROGRAM) *~
