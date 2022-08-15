# nds-lcdtest
### A simple NDS program for testing the LCD, written in C using libnds 

lcdtest is a program I've written for mainly my own personal use as I needed to be able to recalibrate my Nintendo DSi's screens after fiddling around with the two little potentiometers under the battery cover.

The test suite includes 4 test patterns at the moment (which can be seen in the `res/` directory). An SMPTE colour bar example, a greyscale gradient (which isn't very smooth at the moment) and a horizontal and vertical line example.

## Building

### Requisites

- a terminal emulator
- devkitPro (devkitARM & libnds)

### Steps

1. Clone the repo
2. Open the repo directory in your terminal emulator of choice
3. Source the `setup-env.sh` shell script to add required devkitPro environment variables to your session
4. Create a `build/` and `obj/` directory
5. Type `make` or `make -k`, if it doesn't build properly the first time, enter the make command again.
6. `lcdtest.nds` will be in the `build/` directory