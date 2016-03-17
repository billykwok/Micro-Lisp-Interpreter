SRCS    = $(shell /bin/ls *.cc)
CFLAGS   = -DOP_ASSIGN

.SUFFIXES: $(SUFFIXES) .cpp

%.o: %.cpp
#	g++ -c $(CFLAGS) $<
	g++ -c $(CFLAGS) -fno-elide-constructors $<

OBJS = main.o parse.o eval.o Cell.o IntCell.o DoubleCell.o SymbolCell.o ConsCell.o ProcedureCell.o

main: $(OBJS)
	g++ -g $(CFLAGS) -o $@ $(OBJS) -lm

main.o: Cell.hpp cons.hpp parse.hpp eval.hpp main.cpp
	g++ -c -g main.cpp

parse.o: Cell.hpp cons.hpp parse.hpp parse.cpp
	g++ -c -g parse.cpp

eval.o: Cell.hpp cons.hpp eval.hpp eval_helper.hpp RefDict.hpp eval.cpp
	g++ -c -g eval.cpp

Cell.o: Cell.hpp Cell.cpp
	g++ -c -g Cell.cpp

IntCell.o: Cell.hpp IntCell.hpp IntCell.cpp
	g++ -c -g IntCell.cpp

DoubleCell.o: Cell.hpp DoubleCell.hpp DoubleCell.cpp
	g++ -c -g DoubleCell.cpp

SymbolCell.o: Cell.hpp SymbolCell.hpp SymbolCell.cpp
	g++ -c -g SymbolCell.cpp

ConsCell.o: Cell.hpp ConsCell.hpp ConsCell.cpp
	g++ -c -g ConsCell.cpp

ProcedureCell.o: Cell.hpp ProcedureCell.hpp ProcedureCell.cpp
	g++ -c -g ProcedureCell.cpp

doc:
	doxygen doxygen.config

test:
	rm -f testoutput.txt
	./main testinput.txt > testoutput.txt
	diff testreference.txt testoutput.txt

clean:
	rm -f core *~ $(OBJS) main main.exe testoutput.txt
