# Template project for the Geehy APM32F103CB demonstrating GPIO / USART / FPU access

Template CMake project for the Geehy [APM32F103x4x6x8xB Series](https://www.geehy.com/apm32?id=13)

Developed on the ```WeAct TC Studio BluePill-Plus-APM32 (APM32F103CB)``` [development board](https://github.com/WeActStudio/WeActStudio.BluePill-Plus-APM32) obtainable from Aliexpress.

Note: The FPU is a peripheral (i.e. not like an M4) and uses a library to communicate with it (see ```fpu_sc_dot.o``` and ```fpu_sc_math.o```).

## Building:

i.  Create build system: ```cmake -DCMAKE_BUILD_TYPE=Debug -B build```

ii. Build firmware: ```cmake --build build --target all```
