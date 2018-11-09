sem:test.c comm.c
	gcc -o $@ $^ -g

.PHONY:clean
clean:
	rm -f sem
