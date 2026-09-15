WARNINGS := \
	-Wall \
	-Wextra \
	-Wpedantic \
	-Werror \
	-Wconversion \
	-Wsign-conversion \
	-Wshadow \
	-Wformat=2

.PHONY: build run clean

build:
	mkdir -p bin
	$(CC) -std=c23 $(WARNINGS) main.c -o bin/out

run: build
	./bin/out $(filter-out $@,$(MAKECMDGOALS))

%:
	@:

clean:
	rm -rf bin
