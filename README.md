HCC : An open source C++ compiler for heterogeneous devices
===========================================================
This repository hosts HCC compiler implementation project. The goal is to implement a compiler that takes a program conforming parallel programming standards such as C++ AMP, HC, C++ 17 ParallelSTL, or OpenMP and transforms it into the following targets:

1. AMD GCN ISA
2. HSA BRIG

The project is based on LLVM+CLANG.  For more information, please visit the [hcc wiki][1]:

[https://github.com/RadeonOpenCompute/hcc/wiki][1]

Git submodules
--------------
The project now employs git submodules to manage external components it depends upon. It it advised to add `--recursive` when you clone the project so all submodules are fetched automatically.

For example:
```
# automatically fetches all submodules
git clone --recursive -b clang_tot_upgrade git@github.com:RadeonOpenCompute/hcc.git
```

For more information about git submodules, please refer to [git documentation][2].

[//]: # (References)
[1]: https://github.com/RadeonOpenCompute/hcc/wiki
[2]: https://git-scm.com/book/en/v2/Git-Tools-Submodules

Device libraries
----------------
HCC device library is a part of [ROCm-Device-Libs](https://github.com/RadeonOpenCompute/ROCm-Device-Libs).
When compiling device code with hcc, rocm-device-libs package needs to be
installed.

In case rocm-device-libs package is not present, you are required to build it
from source. Once it's built, run `make install` and config ToT HCC like:

```
cmake \
    -DCMAKE_BUILD_TYPE=Release \
    -DHSA_LLVM_BIN_DIR=<where ToT LLVM binary exeuctables are> \
    -DHSA_AMDGPU_GPU_TARGET=<AMD GPU ISA version string> \
    -DROCM_DEVICE_LIB_DIR=<where bitcodes of ROCm-Device-Libs are> \
    <ToT HCC checkout directory>
```

An example would be:
```
# ToT LLVM is built at ~/llvm/build , executables are at ~/llvm/build/bin
# Use AMD:AMDGPU:8:0:3 AMD GPU ISA
# ROCm-Device-Libs is built at ~/ocml/build , bitcodes are at
# ~/ocml/build/dist/lib
cmake \
    -DCMAKE_BUILD_TYPE=Release \
    -DHSA_LLVM_BIN_DIR=~/llvm/build/bin \
    -DHSA_AMDGPU_GPU_TARGET=AMD:AMDGPU:8:0:3 \
    -DROCM_DEVICE_LIB_DIR=~/ocml/build/dist/lib \
    ..
```
