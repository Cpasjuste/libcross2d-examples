## libcross2d

- a c++ cross platform 2d [graphic](https://github.com/Cpasjuste/libcross2d-examples/tree/master/examples/texture), [input](https://github.com/Cpasjuste/libcross2d-examples/tree/master/examples/input), audio and [config](https://github.com/Cpasjuste/libcross2d-examples/tree/master/examples/config) library
- run on Windows, Linux, Nintendo Switch, Nintendo 3DS and Sony PS Vita
- draw textures, rectangles, circles, texts (TrueType) and more
- basic [tween](https://github.com/Cpasjuste/libcross2d-examples/tree/master/examples/crazy) engine (move, rotate, scale, color)
- [clock/timer](https://github.com/Cpasjuste/libcross2d-examples/tree/master/examples/fps) classes
- [configuration](https://github.com/Cpasjuste/libcross2d-examples/tree/master/examples/config) file handling
- pack your application (zip) for release on any target, including resources (data/common)
- quickly prototype your application on desktop (Linux and Windows)
- use hardware acceleration on Linux, Windows, Switch, 3DS and PS Vita
- use some of the great [sfml](https://www.sfml-dev.org/) library stuff (fonts, shapes, matrices)
- use [tweeny](https://github.com/mobius3/tweeny) for the (minimal) tween engine
- use some of the great [libretro](https://github.com/libretro/glsl-shaders) shaders (Linux, Switch)
- use some [citro2d](https://github.com/devkitPro/citro2d) code for the 3ds renderer
- use some [vita2d](https://github.com/xerpi/libvita2d) code for the vita renderer
- use [libconfig](https://github.com/hyperrealm/libconfig) for the configuration classes
- preliminary developed for my own use, still a work in progress

## A few cross2d examples
 - [texture](https://github.com/Cpasjuste/libcross2d-examples/tree/master/examples/texture): drawing a simple texture...
 - [font](https://github.com/Cpasjuste/libcross2d-examples/tree/master/examples/font): drawing some text
 - [input](https://github.com/Cpasjuste/libcross2d-examples/tree/master/examples/input): handle inputs (gamepads, keyboard on linux)
 - [fps](https://github.com/Cpasjuste/libcross2d-examples/tree/master/examples/fps): all about timing (fps, time, delta)
 - [config](https://github.com/Cpasjuste/libcross2d-examples/tree/master/examples/config): handle a configuration file
 - [configbox](https://github.com/Cpasjuste/libcross2d-examples/tree/master/examples/configbox): draw a configuration to screen
 - [filer](https://github.com/Cpasjuste/libcross2d-examples/tree/master/examples/filer): a file manager example
 - [crazy](https://github.com/Cpasjuste/libcross2d-examples/tree/master/examples/crazy): some tweeny stuff...
 - [physics](https://github.com/Cpasjuste/libcross2d-examples/tree/master/examples/physics): basic box2d support

## Made with cross2d
- [pfba](https://github.com/Cpasjuste/pfba)
- [psnes](https://github.com/Cpasjuste/psnes)

## Build and run...
1. [On Linux For Linux](#on-linux-for-linux)
2. [On Linux For Nintendo Switch](#on-linux-for-nintendo-switch)
2. [On Linux For Nintendo 3DS](#on-linux-for-nintendo-3ds)
2. [On Linux For Sony Ps Vita](#on-linux-for-sony-ps-vita)
3. [On Windows For Windows](#on-windows-for-windows)

#### On Linux (For Linux)
- Install dependencies  
    ```  
    sudo apt-get install build-essential cmake git libsdl2-dev libfreetype6-dev libglm-dev libconfig-dev libphysfs-dev
    ```  
- Then  
    ```  
    git clone --recursive https://github.com/Cpasjuste/libcross2d-examples.git
    cd libcross2d-examples
    mkdir cmake-build && cd cmake-build
    cmake -DPLATFORM_LINUX=ON -DOPTION_BOX2D=ON -DCMAKE_BUILD_TYPE=Release ../
    make texture
    cd examples/texture && ./texture
    ```
#### On Linux (For Nintendo Switch)
- Install dependencies
    ```  
    wget https://github.com/devkitPro/pacman/releases/download/devkitpro-pacman-1.0.1/devkitpro-pacman.deb  
    sudo dpkg -i devkitpro-pacman.deb
    sudo dkp-pacman -S switch-dev switch-portlibs switch-glad switch-glm
    ```
- Then
    ```  
    git clone --recursive https://github.com/Cpasjuste/libcross2d-examples.git
    cd libcross2d-examples  
    mkdir cmake-build && cd cmake-build  
    export DEVKITPRO=/opt/devkitpro  
    cmake -DPLATFORM_SWITCH=ON -DOPTION_BOX2D=ON -DCMAKE_BUILD_TYPE=Release ../
    make texture.nro
    make texture_switch_release.zip
    ```
#### On Linux (For Nintendo 3DS)
- Install dependencies
    ```  
    wget https://github.com/devkitPro/pacman/releases/download/devkitpro-pacman-1.0.1/devkitpro-pacman.deb  
    sudo dpkg -i devkitpro-pacman.deb  
    sudo dkp-pacman -S 3ds-dev 3ds-zlib 3ds-freetype 3ds-libpng 3ds-pkg-config  
    ```   
- Then
    ```  
    git clone --recursive https://github.com/Cpasjuste/libcross2d-examples.git
    cd libcross2d-examples  
    mkdir cmake-build && cd cmake-build  
    export DEVKITPRO=/opt/devkitpro  
    cmake -DPLATFORM_3DS=ON -DCMAKE_BUILD_TYPE=Release ../
    make texture.3dsx  
    make texture_3ds_release.zip  
    ```
#### On Linux (For Sony Ps Vita)
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
    git clone --recursive https://github.com/Cpasjuste/libcross2d-examples.git
    cd libcross2d-examples
    mkdir cmake-build && cd cmake-build
    export VITASDK=/usr/local/vitasdk
    cmake -DPLATFORM_VITA=ON -DOPTION_SDL2=ON -DOPTION_RENDER_GLES2=ON -DOPTION_LOADER_GLAD=OFF -DOPTION_BOX2D=ON -DCMAKE_BUILD_TYPE=Release ../
    make texture.vpk
    make texture_vita_release.zip
    ```
#### On Windows (For Windows)
- Install dependencies (from a working devkitPro installation, or preferably a mingw-w64 installation)
    ```
    echo -e "[mingw64]\nInclude = /etc/pacman.d/mirrorlist.mingw64" >> /etc/pacman.conf
    pacman -Syuu
    pacman -Sy bash git mingw-w64-x86_64-toolchain mingw-w64-x86_64-cmake mingw-w64-x86_64-SDL2 mingw-w64-x86_64-freetype mingw-w64-x86_64-glm mingw-w64-x86_64-glew mingw-w64-x86_64-mesa mingw-w64-x86_64-libconfig
    ```
- Then
    ```
    C:\devkitPro\msys2> .\msys2_shell.bat -mingw64
    ```
    ```
    git clone --recursive https://github.com/Cpasjuste/libcross2d-examples.git
    cd libcross2d-examples
    mkdir cmake-build && cd cmake-build
    cmake -G "MSYS Makefiles" -DPLATFORM_WINDOWS=ON -DCMAKE_BUILD_TYPE=Release ../
    make texture
    cd examples/texture && ./texture
    ```
