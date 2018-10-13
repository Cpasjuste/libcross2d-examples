## A few cross2d examples
 [texture](https://github.com/Cpasjuste/libcross2d-examples/tree/master/examples/texture): drawing a simple texture...\
 [font](https://github.com/Cpasjuste/libcross2d-examples/tree/master/examples/font): drawing some text.\
 [input](https://github.com/Cpasjuste/libcross2d-examples/tree/master/examples/input): handle inputs (gamepads, keyboard on linux)\
 [fps](https://github.com/Cpasjuste/libcross2d-examples/tree/master/examples/fps): is it fast enough?\
 [crazy](https://github.com/Cpasjuste/libcross2d-examples/tree/master/examples/crazy): some tweeny stuff...

## Build and run them...
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
    TODO
    ```   
- Then
    ```
    TODO
    ```