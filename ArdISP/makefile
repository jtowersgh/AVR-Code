FILENAME = 16bitTimer
PORT = /dev/spidev0.0
DEVICE  = atmega328p
PROGRAMMER = arduino
BAUD = 11500
INCLUDE = -I/usr/avr/include
COMPILE = avr-gcc -Wall -Os -mmcu=$(DEVICE) $(INCLUDE)

# removed "upload" between compile and clean from the below line
default: compile clean

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
#	rm $(FILENAME).hex
