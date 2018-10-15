## libcross2d

- a c++ cross platform 2d graphic, input and audio library
- currently run on Linux, Nintendo Switch, Nintendo 3DS and Sony PS Vita
- draw rectangles, circles, textures and more with ease
- basic tween engine (move, rotate, scale, color)
- pack your application (zip) for release on any target including target resources (data/common)
- quickly prototype your application on desktop (Linux)
- use hardware acceleration on Linux, Switch, 3DS and PS Vita
- use some of the great [sfml](https://www.sfml-dev.org/) library stuff (fonts, shapes, matrices)
- use [tweeny](https://github.com/mobius3/tweeny) for the (minimal) tween engine
- use some of the great [libretro](https://github.com/libretro/glsl-shaders) shaders (Linux, Switch)
- preliminary developed for my own use, but could now probably be used to ease development
- is still a work in progress

## A few cross2d examples
 - [texture](https://github.com/Cpasjuste/libcross2d-examples/tree/master/examples/texture): drawing a simple texture...
 - [font](https://github.com/Cpasjuste/libcross2d-examples/tree/master/examples/font): drawing some text
 - [input](https://github.com/Cpasjuste/libcross2d-examples/tree/master/examples/input): handle inputs (gamepads, keyboard on linux)
 - [fps](https://github.com/Cpasjuste/libcross2d-examples/tree/master/examples/fps): all about timing (fps, time, delta)
 - [filer](https://github.com/Cpasjuste/libcross2d-examples/tree/master/examples/filer): a file manager example
 - [crazy](https://github.com/Cpasjuste/libcross2d-examples/tree/master/examples/crazy): some tweeny stuff...

## Made with cross2d
- [pfba](https://github.com/Cpasjuste/pfba)
- [psnes](https://github.com/Cpasjuste/psnes)

## Build and run examples...
### On Linux (deb)
- Install dependencies  
    ```  
    sudo apt-get install build-essential cmake git libsdl2-dev libfreetype6-dev libglm-dev  
    ```  
- Then  
    ```  
    git clone --recursive git@github.com:Cpasjuste/libcross2d-examples.git  
    cd libcross2d-examples  
    mkdir cmake-build && cd cmake-build  
    cmake -DBUILD_SDL2=1 ../  
    make  
    ./examples/texture/texture.elf  
    ```
### On Nintendo Switch
- Install dependencies
    ```  
    wget https://github.com/devkitPro/pacman/releases/download/devkitpro-pacman-1.0.1/devkitpro-pacman.deb  
    sudo dpkg -i devkitpro-pacman.deb  
    sudo dkp-pacman -S switch-dev  
    sudo dkp-pacman -S switch-bzip2 switch-freetype switch-glad switch-glm switch-libdrm_nouveau switch-libpng switch-mesa switch-pkg-config switch-sdl2 switch-zlib  
    ```
- Then
    ```  
    git clone --recursive git@github.com:Cpasjuste/libcross2d-examples.git  
    cd libcross2d-examples  
    mkdir cmake-build && cd cmake-build  
    export DEVKITPRO=/opt/devkitpro  
    cmake -DBUILD_SWITCH=1 ../  
    make texture.nro  
    make texture_switch_release.zip  
    ```
### On Nintendo 3DS
- Install dependencies
    ```  
    wget https://github.com/devkitPro/pacman/releases/download/devkitpro-pacman-1.0.1/devkitpro-pacman.deb  
    sudo dpkg -i devkitpro-pacman.deb  
    sudo dkp-pacman -S 3ds-dev 3ds-zlib 3ds-freetype 3ds-libpng 3ds-pkg-config  
    ```   
- Then
    ```  
    git clone --recursive git@github.com:Cpasjuste/libcross2d-examples.git  
    cd libcross2d-examples  
    mkdir cmake-build && cd cmake-build  
    export DEVKITPRO=/opt/devkitpro  
    cmake -DBUILD_3DS=1 ../  
    make texture.3dsx  
    make texture_3ds_release.zip  
    ```
### On Sony Ps Vita
- Install dependencies
    ```  
    git clone https://github.com/vitasdk/vdpm
    cd vdpm
    ./bootstrap-vitasdk.sh
    export VITASDK=/usr/local/vitasdk # define $VITASDK if you haven't already
    export PATH=$VITASDK/bin:$PATH # add vitasdk tool to $PATH if you haven't already
    ./install-all.sh
    ```   
- Then
    ```
    git clone --recursive git@github.com:Cpasjuste/libcross2d-examples.git
    cd libcross2d-examples
    mkdir cmake-build && cd cmake-build
    export DEVKITPRO=/opt/devkitpro
    cmake -DBUILD_VITA=1 ../
    make texture.vpk
    make texture_vita_release.zip
    ```