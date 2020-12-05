FILENAME = sweep
PORT = /dev/spidev0.0
DEVICE  = attiny85
PROGRAMMER = linuxspi
BAUD = 11500
INCLUDE = -I/usr/lib/avr/include
COMPILE = avr-gcc -Wall -Os -mmcu=$(DEVICE) $(INCLUDE)

default: compile upload clean

compile:
	$(COMPILE) -c $(FILENAME).c -o $(FILENAME).o
	$(COMPILE) -o $(FILENAME).elf $(FILENAME).o
	avr-objcopy -j .text -j .data -O ihex $(FILENAME).elf $(FILENAME).hex
	avr-size --format=avr --mcu=$(DEVICE) $(FILENAME).elf

upload:
	sudo avrdude -v -p $(DEVICE) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -U flash:w:$(FILENAME).hex

clean:
	rm $(FILENAME).o
	rm $(FILENAME).elf
	rm $(FILENAME).hex
