program_NAME := ta
program_CXX_SRCS := $(wildcard *.cpp)
program_OBJS := ${program_CXX_SRCS:.cpp=.o}

# put the path to boost in program_INCLUDE_DIRS:
program_INCLUDE_DIRS := C:\temp\boost_1_71_0

CPPFLAGS += $(foreach includedir,$(program_INCLUDE_DIRS),-I$(includedir))

#Optimisation and warnings flags
CPPFLAGS += -Wall -O3 -DUSE_EXTENDED_PRECISION

# need to staticly link if on windows (MinGW fix)
ifeq ($(OS),Windows_NT)
    CPPFLAGS += -static-libgcc -static-libstdc++
endif

.PHONY: all clean distclean

all: $(program_NAME)

$(program_NAME): $(program_OBJS)
	$(LINK.cc) $(program_OBJS) -o $(program_NAME)

clean:
	@- $(RM) $(program_NAME)
	@- $(RM) $(program_OBJS)

distclean: clean
