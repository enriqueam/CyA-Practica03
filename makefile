CC = g++
CFLAGS = -std=c++17 -g -Wall

F0  = p03_calculator
F1  = simbolos
F2  = alfabetos
F3  = cadenas
F4  = lenguajes
F5  = calculadoraRPN
FH  = .h
FCC = .cc

PROGRAM = p03_calculator

all: $(PROGRAM)
$(PROGRAM): $(F0)$(FCC)
	$(CC) $(CFLAGS) $(F0)$(FCC) $(F1)$(FCC) $(F2)$(FCC) $(F3)$(FCC) $(F4)$(FCC) $(F5)$(FCC) -o $(PROGRAM)

.PHONY: clean
clean:
	rm -rf $(PROGRAM)
	rm -rf fileout.txt