# Under construction!!!
## GCC build using MinGw
Tested x64 builds using **MinGW** installed on Windows-11. Tested the following MinGw installation methods.
- [WinLibs](#WinLibs)
- [Sourceforge](#Sourceforge)
- [Github niXman](#Github-niXman)
- [MSYS2](#MSYS2)

### WinLibs
- [winlibs](https://winlibs.com/)
  - GCC 15.2.0 (with POSIX threads) + MinGW-w64 13.0.0 (UCRT) - release 1 
### Sourceforge
- [sourceforge-mingw](https://sourceforge.net/projects/mingw/)
### Github niXman
- [15.2.0-rt_v13-rev0](https://github.com/niXman/mingw-builds-binaries/releases/tag/15.2.0-rt_v13-rev0)
 - x86_64-15.2.0-release-posix-seh-ucrt-rt_v13-rev0.7z
   - This version uses modern Windows runtime (ucrt), POSIX threading for cross-platform compatibility, and SEH for 64-bit Windows exception handling.
 - Used installation instructions from the following link for intallation and configuration:
   - https://phoenixnap.com/kb/install-gcc-windows
### MSYS2
- Downloaded from the following link:
  - https://www.msys2.org
  - Used default installation instructions.
  - gcc.exe (Rev8, Built by MSYS2 project) 15.2.0
  - This version is able to compile the following languages:
    - Ada
	- C
	- C++
	- Fortran
	- Obj-C
	- Obj-C++
	- OCaml 


