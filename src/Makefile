COMPILER = g++ -std=c++17
CFLAGS = 
TESTFLAGS = -lgtest -g -fno-elide-constructors
TEST_EXE = test_runner.out

CONTAINERS = list vector deque
TEST_SRC = $(wildcard tests/*_test.c)
TEST_OBJ = $(TEST_SRC:.c=.o)

.PHONY: all test clean
.DEFAULT_GOAL := all

all: test

$(TEST_OBJ): %.o: %.c
	$(COMPILER) $(CFLAGS) -c $< -o $@

test: $(TEST_OBJ)
	$(COMPILER) $(CFLAGS) $(TEST_OBJ) -o $(TEST_EXE) $(TESTFLAGS)
	./$(TEST_EXE)

clean:
	rm -rf $(TEST_OBJ) $(TEST_EXE) tests/*.info tests/*.gcda tests/*.gcno tests/*.out tests/*.o tests/report/ *.o

OS := $(shell uname -s)
ifeq ($(OS), Linux)
    ifneq (,$(findstring Microsoft,$(shell uname -r)))
        OPEN := explorer.exe
    else
        OPEN := xdg-open
    endif
else ifeq ($(OS), Darwin)
    OPEN := open
endif

gcov_report:
	@mkdir tests/report -p
	$(COMPILER) $(CFLAGS) --coverage $(TEST_SRC) -o tests/test.out $(TESTFLAGS)
	./tests/test.out
	lcov -t "test" -o tests/test.info -c -d ./tests
	lcov --remove tests/test.info '/usr/include/*' '*tests*' -o tests/filtered_coverage.info
	genhtml -o tests/report/ tests/filtered_coverage.info
	@if [ "$(OS)" = "Linux" ]; then \
		if [ -n "$$(grep -i microsoft /proc/version)" ]; then \
			WIN_PATH=$$(wslpath -w "tests/report/index.html"); \
			explorer.exe "$$WIN_PATH"; \
		else \
			xdg-open "tests/report/index.html"; \
		fi; \
	elif [ "$(OS)" = "Darwin" ]; then \
		open "tests/report/index.html"; \
	else \
		echo "Unsupported OS: $(OS)"; \
		exit 1; \
	fi