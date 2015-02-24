.PHONY: clean

ctc2: ctc2.c main.c
	gcc $^ -o $@ -Wall -O2

clean:
	@rm -f ctc2
	@rm -f ctc2.exe