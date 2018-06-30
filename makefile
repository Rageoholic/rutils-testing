RUTILS_DIR= rutils/

# TODO: Come up with actual ways to set these properly (shell script?)
PLATFORM = LINUX

TESTDIR = tests/

ARCHITECTURE = X86_64

TESTS = string-test




WARNINGS = -Wall -Wextra -Werror -Wno-error=unused-variable	\
-Wno-error=unused-parameter -Wno-missing-field-initializers	\
-Wno-unused-function

BASECFLAGS = $(WARNINGS) --std=c99 -MD -MP -D$(PLATFORM) -D$(ARCHITECTURE)
DEPS = $(shell find . -name "*.d")

all: tests

tests: $(TESTS)
	./run-tests $^
tests: CFLAGS = $(BASECFLAGS) -g
tests: LDFLAGS = -lcmocka


-include $(DEPS)
-include rutils/rutils.mk

-include .user.mk		#User defined includes. Use this to configure specific settings on build files

clean:
	-$(RM) -f *.o *.d $(RUTILS_DIR)/*.o $(RUTILS_DIR)/*.d vgcore.* $(TESTS)

string-test: string-test.o rutils.a

.PHONY: all clean tests
