RUTILS_DIR= rutils/

# TODO: Come up with actual ways to set these properly (shell script?)
PLATFORM = LINUX

TESTDIR = tests/

ARCHITECTURE = X86_64

_TESTS = string-test

TESTS = $(patsubst %,$(TESTDIR)%.test, $(_TESTS))

WARNINGS = -Wall -Wextra -Werror -Wno-error=unused-variable	\
-Wno-error=unused-parameter -Wno-missing-field-initializers

BASECFLAGS = $(WARNINGS) --std=c99 -MD -MP -D$(PLATFORM) -D$(ARCHITECTURE)
DEPS = $(shell find . -name "*.d")

ifndef VERBOSE
.SILENT:
endif

all: tests

tests: $(TESTS)
tests: CFLAGS = $(BASECFLAGS) -g

-include $(DEPS)
-include rutils/rutils.mk

-include .user.mk		#User defined includes. Use this to configure specific settings on build files

clean:
	-$(RM) -f *.o *.d $(RUTILS_DIR)/*.o $(RUTILS_DIR)/*.d

string-test: string-test.o rutils.a

$(TESTDIR)%.test: %
	mkdir -p $(TESTDIR)
	@echo "Beginning test $<"
	./$< > $@

.PHONY: all clean tests
