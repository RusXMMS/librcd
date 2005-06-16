all: generate ascii test upper debug 
generate: generate.c
	gcc -lm -o generate generate.c
ascii: ascii.c
	gcc -o ascii ascii.c
test: test.c charset_auto_russian.h russian_table.h
	gcc -o test test.c
debug: debug.c charset_auto_russian.h russian_table.h
	gcc -o debug debug.c
upper: upper.c