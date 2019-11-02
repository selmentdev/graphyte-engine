# Readme

## Requirements

### Fedora

```sh
sudo dnf install libuuid-devel SDL2-devel
```

### Ubuntu

```.sh
sudo apt install uuid-dev libsdl2-dev libx11-dev libunwind-dev
```

## Building

Variants

```sh
./generate.sh
make config=debug-x64
```

## Switching compilers

Remove alternatives

```.sh
sudo update-alternatives --remove-all cc
sudo update-alternatives --remove-all c++
```

Update to clang

```.sh
sudo update-alternatives --install /usr/bin/cc cc /usr/bin/clang-7 100
sudo update-alternatives --install /usr/bin/c++ c++ /usr/bin/clang++-7 100
c++ --version
```

Update to GCC

```.sh
sudo update-alternatives --install /usr/bin/cc cc /usr/bin/gcc-9 100
sudo update-alternatives --install /usr/bin/c++ c++ /usr/bin/g++-9 100
c++ --version
```

