# Matrix Calculator
20465 System Programming Laboratory - Assignment 22 (Grade 100)


### Overview
- For detailed description, see [Assignment 22](doc/assignment_22.pdf)


### Requirements
C Standard
- ANSI C(89/90)

Linux
- Ubuntu >= 16.04
- Install gcc and make
```
sudo apt update
sudo apt install build-essential
```

Windows
- Windows 10/11
- MSVC 2022


### Build Instructions
Linux
```
make clean
make
```

Windows
```
# Activate the Visual Studio build environment for x64 architecture.
call "C:\Program Files\Microsoft Visual Studio\2022\Enterprise\VC\Auxiliary\Build\vcvarsall.bat" x64

# Compile all C sources into mainmat.exe
cl /nologo /W4 /EHsc /std:c89 mainmat.c utils.c mymat.c
```


### Usage
- Use command line:

Linux
```
./mainmat
./mainmat < test/valid_inputs.txt
```

Windows
```
mainmat.exe
mainmat.exe < test/valid_inputs.txt
```