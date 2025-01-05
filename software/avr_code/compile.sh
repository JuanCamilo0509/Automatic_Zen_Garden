#!/bin/bash
avr-gcc -mmcu=atmega88p -Os -o $1.elf $1.c
avr-objcopy -O ihex -R .eeprom $1.elf $1.hex
