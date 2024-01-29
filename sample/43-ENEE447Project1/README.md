# ENEE447 2024 Spring Project 0 

## What are we doing in this project
- We will run test code for Project 1. (You don't need to know what Project 1 is now). The detail description and objective of Project 1 will be announced later. 
- This is set-up for all projects throughout the semester. 

## What to submit on ELMS by Feb 11:
1. A pdf that has:
	- Members of your group.
	- A screenshot that shows Project 1 test code is successfully compiled using cross-compiler (shows kernel*.img has been generated)
	- A screenshot that shows Project 1 test code is successfully executed in QEMU (shows running screenshot from QEMU emulator)
	- Answer the following questions in 2-3 sentences:
	   * What is Bare-metal programming?
	   * Why do we need a cross compiler for Rasberry Pi?
	   * What is the job of bootstrap code for a program?
	   * What is the job of an assembler and a linker?


### 1. How do I run this sample in qemu? (Prerequisite: cross-compiler installed)
- First, install qemu on your computer.
	- If you are using MacOS, follow [these instructions](https://www.qemu.org/download/#macos).
	- If you are using Linux, follow [these instructions](https://www.qemu.org/download/#linux).
	- If you are using Windows, follow [these instructions](https://www.qemu.org/download/#windows).
- Then, type `qemu-system-arm --version` in your terminal to make sure it has been sucessfully installed.
- Then, cd into the root directory of circle and type:
	- `./configure --qemu -f`
	- `./makeall clean && ./makeall`
- You should have `sample/43-ENEE447Project1/kernel.img` generated if the compilation is successful.
- Then, to run the generated kernel in qemu, type `qemu-system-arm -M raspi0 -bios sample/43-ENEE447Project1/kernel.img `
	- A new Window should pop up which emulates the code running on Raspberry Pi Zero.

### 2. How do I run this sample on my Raspberry Pi? (for who want to build)
- First, [follow these instructions to build a `kernel*.img` file for your version of Pi](https://github.com/sklaw/circle#building)
- Then, [follow these instructions to copy firmware files and the `kernel*.img` file to your FAT-formatted SD card](https://github.com/sklaw/circle#installation).
- Then, insert the SD card into your Pi, connect your Pi's HDMI port to a external monitor, then power on your Pi. 

### 3. After I modify some codes, how do I compile and get the latest kernel?
- If you have modified source codes of the library (any code in `lib` or `include`), run `./makeall clean && ./makeall`.
- If you have modified _only_ codes in the sample but not in the library, run `cd sample/43-ENEE447Project1/`, then run `make clean && make`.

