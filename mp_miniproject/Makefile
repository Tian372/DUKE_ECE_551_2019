CFLAGS =-pthread -std=gnu++11 -Wall -Werror -ggdb3
SRCS =$(wildcard *.cpp)
OBJS =$(patsubst %.cpp, %.o, $(SRCS))

numerics: $(OBJS) Expr.h 
	g++ $(CFLAGS) -o $@ $(OBJS)

%.o: %.cpp
	g++ -c $(CFLAGS) $<
