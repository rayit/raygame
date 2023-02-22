

> To build I needed to remove ld and atomic before cmake ..


#### OpenBSD build example
```bash
clang main.c -o m -I/usr/local/include -L/usr/local/lib -lraylib -lglfw  -lopenal -lm -lpthread
```
