Examples
--------
- [texture](https://github.com/Cpasjuste/libcross2d-examples/tree/master/examples/texture): drawing a simple texture...
![image of texture](https://github.com/Cpasjuste/libcross2d-examples/raw/master/examples/texture/texture_mini.png)

Build and run (Linux/deb)
-------------------------

- Install dependencies
    ```
    sudo apt-get install build-essential cmake git libsdl2-dev libfreetype6-dev libglm-dev
    ```
- Build
    ```
    git clone --recursive git@github.com:Cpasjuste/libcross2d-examples.git
    cd libcross2d-examples
    mkdir cmake-build && cd cmake-build
    cmake -DBUILD_SDL2=1 ../
    make
    ./examples/texture/texture.elf
    ```


Build and run (Nintendo Switch)
-------------------------------

- Install dependencies

    ```
    wget https://github.com/devkitPro/pacman/releases/download/devkitpro-pacman-1.0.1/devkitpro-pacman.deb
    sudo dpkg -i devkitpro-pacman.deb
    sudo dkp-pacman -S switch-dev
    sudo dkp-pacman -S switch-bzip2 switch-freetype switch-glad switch-glm switch-libdrm_nouveau switch-libpng switch-mesa switch-pkg-config switch-sdl2 switch-zlib
    ```

- Build

    ```
    git clone --recursive git@github.com:Cpasjuste/libcross2d-examples.git
    cd libcross2d-examples
    mkdir cmake-build && cd cmake-build
    export DEVKITPRO=/opt/devkitpro
    cmake -DBUILD_SWITCH=1 ../
    make texture.nro
    make texture_switch_release.zip
    ```


Build and run (Nintendo 3DS)
----------------------------

- Install dependencies

    ```
    wget https://github.com/devkitPro/pacman/releases/download/devkitpro-pacman-1.0.1/devkitpro-pacman.deb
    sudo dpkg -i devkitpro-pacman.deb
    sudo dkp-pacman -S 3ds-dev 3ds-zlib 3ds-freetype 3ds-libpng 3ds-pkg-config
    ```
    
- Build

    ```
    git clone --recursive git@github.com:Cpasjuste/libcross2d-examples.git
    cd libcross2d-examples
    mkdir cmake-build && cd cmake-build
    export DEVKITPRO=/opt/devkitpro
    cmake -DBUILD_3DS=1 ../
    make texture.3dsx
    make texture_3ds_release.zip
    ```
    