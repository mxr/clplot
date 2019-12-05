.PHONY: all

CC = g++
chartCompiled = bin/clplot
newpath = ""
BINDIR = bin

all: compile

compile:
	@echo "Compiling..."
	@${CC} -std=c++11 src/clplot.cpp src/args.cpp src/line.cpp src/bar.cpp -o ${chartCompiled}
	@printf "\e[32mCompiled successfuly!\e[0m\n"
	@sleep .4
	@printf "To install run '\e[31mmake install\e[0m'\n"

install:
	@echo "Copying binary..."
	@install -m 0755 ${chartCompiled} /usr/local/bin
	@printf "\x1b[32mSuccessfully copied program.\x1b[0m \nRun command '\x1b[31mchart\x1b[0m' to start program!\n"

silentcompile:
	@mkdir -p $(BINDIR)
	@${CC} -std=c++11 src/clplot.cpp src/args.cpp src/line.cpp src/bar.cpp -o ${chartCompiled}

brewinstall:
	@mkdir -p ${newpath}/bin
	@install -m 0755 ${chartCompiled} ${newpath}/bin/clplot