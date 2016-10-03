CC=gcc -g

.phony all:
all: PMan inf

PMan: PMan.c processList.c commandService.c
	$(CC) PMan.c processList.c commandService.c -lreadline -lhistory -o PMan

inf: inf.c
	$(CC) inf.c -o inf

.PHONY clean:
clean:
	-rm -rf *.o *.exe
