Display [Kanizsa square](https://puzzlewocky.com/optical-illusions/kanizsa-square-and-triangle-illusions/) 

![](kanizsa_square.png)

# Installation

## Requirements:

    libSDL2 and libSDL2_gfx 
    
Under Ubuntu, they can be installed with
    
    sudo apt install build-essentials libsdl2-dev libsdl2-gfx-dev


## Compilation

    cc -I/usr/include/SDL2  kanisza_square.c  -lSDL2  -lSDL2_gfx -o kanizsa_square
    
or just:

    make kanizsa_square
    
   


