# SloeDOOM

Sloe Computers port of the classic game from id SOFTWARE.

## Status

[![Build Status](https://github.com/SloeComputers/SloeDOOM/actions/workflows/build_on_push.yml/badge.svg)](https://github.com/SloeComputers/SloeDOOM/actions/workflows/build_on_push.yml)

## Software

### Dependencies

+ https://github.com/SloeComputers/PDK
+ https://github.com/SloeComputers/id_DOOM
+ cmake
+ ninja (make works too)

### Checkout

This repo uses git sub-modules, so checkout using --recurse-submodules to clone all the
dependent source...

    git clone --recurse-submodules https://github.com/SloeComputers/SloeDOOM.git

or

    git clone --recurse-submodules ssh://git@github.com/SloeComputers/SloeDOOM.git

### Build

Build directly using cmake...

```
mkdir build
cd build
cmake ..
make
```

## License

See the [LICENSE](LICENSE) file for details.

The original DOOM [source](https://github.com/id-Software/DOOM) release from **id**
is embedded in this project, with a few modification, via a
[submodule](https://github.com/SloeComputers/id_DOOM). Therefore this project
inherits the same GPL 2 license that **id** have adopted.
