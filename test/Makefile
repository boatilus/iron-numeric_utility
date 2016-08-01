all:
ifeq ($(CXX),g++)
	$(CXX)$(VER) -std=c++14 -Wall -Wextra -pedantic-errors *.cpp -o main
else
	$(CXX)$(VER) -std=c++14 -Weverything -Wno-newline-eof -Wno-exit-time-destructors -Wno-c++98-compat -Wno-c++98-compat-pedantic -pedantic-errors *.cpp -o main
endif

test:
	./main

clean:
	rm -r main