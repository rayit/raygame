
#### Idea
> Idea is to make counting game.. So you get a sum and you have to take the good 1 in your basket..


TODO:
    - split up, use InitGame, UpdateGame, DrawGame, UnloadGame, UpdateDrawFrame?? in seperate files .h .c
    - think about building (cmake or Makefile)
    - create src directory?


## OpenBSD raylib
> doas pkg_add glfw openal

> To build I needed to remove ld and atomic before cmake .. (made PR)

> Solution: I needed to create a symlink in lib called "libraylib.so" that linked to the actual library. Any explanations as to why this works would be appreciated.


#### OpenBSD build example
```bash
clang main.c -o m -I/usr/local/include -L/usr/local/lib -lraylib -lglfw  -lopenal -lm -lpthread
```
