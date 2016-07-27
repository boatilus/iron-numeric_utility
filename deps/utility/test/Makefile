all:
ifeq ($(CXX),g++)
	$(CXX)$(VER) -std=c++14 -Wall -Wextra -pedantic-errors has_char_traits.cpp has_eq_or_greater_range.cpp have_same_signedness.cpp is_integer_like.cpp safe_to_int.cpp smallest_integer.cpp traits.cpp width_as_integer.cpp -o main
else
	$(CXX)$(VER) -std=c++14 -Weverything -Wno-newline-eof -Wno-exit-time-destructors -pedantic-errors has_char_traits.cpp has_eq_or_greater_range.cpp have_same_signedness.cpp is_integer_like.cpp safe_to_int.cpp smallest_integer.cpp traits.cpp width_as_integer.cpp -o main
endif

test:
	./main

clean:
	rm -r main
