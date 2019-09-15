.PHONY: all

CC = g++
chartCompiled = bin/chart

ifneq ("$(wildcard $(chartCompiled))","")
all: exit
else
all: compile
endif

exit:
	@printf "Compiling...\n"
	@sleep .3
	@printf "\x1b[31mProgram already compiled, exiting... see 'make install' to move the binaries\e[0m\n"

compile:
	@echo "Compiling..."
	@${CC} -std=c++11 src/chartRunner.cpp src/functions.cpp -o bin/chart
	@printf "\e[32mCompiled successfuly!\e[0m\n"
	@sleep .4
	@printf "To install run '\e[31mmake install\e[0m'\n"

install:
	@echo "Copying binary..."
	@install -m 0755 bin/chart /usr/local/bin
	@printf "\x1b[32mSuccessfully copied program.\x1b[0m \nRun command '\x1b[31mchart\x1b[0m' to start program!\n"