CXX = g++
CXXFLAGS = -I /scratch/perkins/include
CPPFLAGS = -Wall
LDFLAGS = -L /scratch/perkins/lib
LDLIBS = -lcdk -lcurses


EXECFILE = printMatrix

OBJS = main.o

all: $(EXECFILE)

#Clean files
clean:
	rm -f $(OBJS) $(EXECFILE) *~ \#*

#Specify compiling rules
$(EXECFILE):	$(OBJS)
	$(CXX) -static -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)
