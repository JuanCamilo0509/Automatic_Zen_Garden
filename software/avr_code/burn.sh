#!/bin/bash
avrdude -c usbasp-clone -p m88p -U flash:w:$1.hex:i
