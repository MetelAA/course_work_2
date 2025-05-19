CC = gcc
DEV = -Wall -Wextra
CFLAGS =  -std=c99
OBJ = main.o parser/parser.o parser/validator/base_validator.o parser/validator/canvas_entity_validator.o consoleLogs/help.o consoleLogs/info.o
EXEC = cw

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)

main.o: main.c base_structs.h parser/parser.h consoleLogs/help.h consoleLogs/info.h
	$(CC) $(CFLAGS) -c main.c -o main.o

parser/parser.o: parser/parser.c parser/parser.h parser/validator/canvas_entity_validator.h
	$(CC) $(CFLAGS) -c parser/parser.c -o parser/parser.o

parser/validator/base_validator.o: parser/validator/base_validator.c parser/validator/base_validator.h base_structs.h
	$(CC) $(CFLAGS) -c parser/validator/base_validator.c -o parser/validator/base_validator.o

parser/validator/canvas_entity_validator.o: parser/validator/canvas_entity_validator.c parser/validator/canvas_entity_validator.h parser/validator/base_validator.h base_structs.h
	$(CC) $(CFLAGS) -c parser/validator/canvas_entity_validator.c -o parser/validator/canvas_entity_validator.o

consoleLogs/help.o: consoleLogs/help.c consoleLogs/help.h
	$(CC) $(CFLAGS) -c consoleLogs/help.c -o consoleLogs/help.o

consoleLogs/info.o: consoleLogs/info.c consoleLogs/info.h base_structs.h
	$(CC) $(CFLAGS) -c consoleLogs/info.c -o consoleLogs/info.o


clean:
	rm -f $(OBJ) $(EXEC)