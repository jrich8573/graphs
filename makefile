DIR=${PWD}
ASST=$(notdir ${DIR})
MAINPROG=tripplanner
ifneq (,$(findstring MinGW,$(PATH)))
DISTR=MinGW
CPPFLAGS=-g -D$(DISTR) -std=c++0x
EXE=.exe
LFLAGS=
else
DISTR=Unix
CPPFLAGS=-g -D$(DISTR) -std=c++17
EXE=
LFLAGS=
endif
#
########################################################################
# Macro definitions for "standard" C and C++ compilations
#
CFLAGS=-g
TARGET=$(MAINPROG)$(EXE)
CPPS=tripplanner.cpp roadmap.cpp
LINK=g++ $(CPPFLAGS)
#
CC=gcc
CXX=g++
#
#
#  In most cases, you should not change anything below this line.
#
#  The following is "boilerplate" to set up the standard compilation
#  commands:
#


OBJS=$(CPPS:%.cpp=%.o)
DEPENDENCIES = $(CPPS:%.cpp=%.d)



%.d: %.cpp
	touch $@

%.o: %.cpp
	$(CXX) $(CPPFLAGS) -MMD -o $@ -c $*.cpp

# 
# Targets:
# 
all: $(TARGET)

$(TARGET): $(OBJS)
	$(LINK) $(FLAGS) -o $(TARGET) $(OBJS) $(LFLAGS)

clean:
	-/bin/rm -f *.d *.o $(TARGET)



make.dep: $(DEPENDENCIES)
	-cat $(DEPENDENCIES) > $@

include make.dep
