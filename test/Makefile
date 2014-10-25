CC=	gcc

TEST_DIR=	tests

all:
	@$(CC) $(TEST_DIR)/*.c -I.. -L.. -lmod
	@./a.out < ./input_file.txt 1> ./test.txt 2> /dev/null
	@python3.4 ./test
	@rm -f test.txt
	@rm -f a.out
