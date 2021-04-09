.PHONY: all
CC = g++ -std=c++11
#CROSS_COMPILE=aarch64-linux-gnu-

#all: target
all: clean mkdir lab02

lab02 : gpio_main.cpp
	$(CC) -o $@ $^
	#$(CROSS_COMPILE) $(CC) -o $@ $^
	# $@ -> the name of target
	# $^ -> ALL dependenices of this target
	# $< -> the first dependenices of this target
mkdir:
	mkdir -p bin obj

.PHONY: clean
clean:
	rm -f lab02
	
# file ./
# ssh -Y nvida@ 192.....