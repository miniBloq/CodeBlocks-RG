@rem 2010.09.21:
@rem This bat compiles the example without the IDE. It lets to see step by step de Arduino IDE compilation process (but with a
@rem precompiled "core.a" (in this specifi case the core used is the m168_16MHz_core.a).

cls

@rem Generates the main.cpp.o file:
avr-g++ -c -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -mmcu=atmega168 -DF_CPU=16000000L -DARDUINO=19 -IC:\Projects\Multiplo\Soft\CodeBlocks-RG\v1.0\Soft\sdk\arduino-0019\hardware\arduino\cores\arduino main.cpp -omain.cpp.o

@rem Generates the main.cpp.elf file:
avr-gcc -Os -Wl,--gc-sections -mmcu=atmega168 -o main.cpp.elf main.cpp.o C:\Projects\Multiplo\Soft\CodeBlocks-RG\v1.0\Soft\sdk\arduino-0019\hardware\arduino\cores\arduino.Lib\WinAVR-20090313\m168_16MHz_core.a -L .\ -lm 

@rem Generates the main.cpp.epp file:
avr-objcopy -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0 main.cpp.elf main.cpp.epp

@rem Generates the main.cpp.hex file:
avr-objcopy -O ihex -R .eeprom main.cpp.elf main.cpp.hex 

avr-size --mcu=atmega168p --format=avr main.cpp.elf

@echo off
rem avr-objcopy -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0 
rem C:\Users\j\AppData\Local\Temp\build9148872925609882569.tmp\AnalogInOutSerial.cpp.elf 
rem C:\Users\j\AppData\Local\Temp\build9148872925609882569.tmp\AnalogInOutSerial.cpp.eep 
rem avr-objcopy -O ihex -R .eeprom 
rem C:\Users\j\AppData\Local\Temp\build9148872925609882569.tmp\AnalogInOutSerial.cpp.elf 
rem C:\Users\j\AppData\Local\Temp\build9148872925609882569.tmp\AnalogInOutSerial.cpp.hex 
