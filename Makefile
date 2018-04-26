#Programmed by: Matthew Nevle
#Student Id: Man160530
CXX = g++
CXXFLAGS = 
CPPFLAGS = -Wall -I /scratch/perkins/include
LDFLAGS = -L /scratch/perkins/lib
LDLIBS = -lcdk -lcurses


EXECFILE = printMatrix

OBJS = main.o

all: $(EXECFILE)

#Clean files
clean:
	rm -f $(OBJS) $(EXECFILE) *.P  *~ \#*

#Specify compiling rules
$(EXECFILE):	$(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)
