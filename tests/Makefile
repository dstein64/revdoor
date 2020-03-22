all:
	$(CXX) \
		-Wall -Wextra -Wpedantic -Werror \
		-fsanitize=address -fsanitize=undefined \
		-I.. \
		test_revdoor.cpp \
		-o test_revdoor \
		-std=c++0x \
		-lboost_unit_test_framework
