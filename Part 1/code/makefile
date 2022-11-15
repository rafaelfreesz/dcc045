CC  = g++
CFLAGS  = -Wall
LDFLAGS =
OBJFILES = LexicalAnalyzer.o SymbolTable.o ErrorManager.o main.o
TARGET  = lex.out

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~