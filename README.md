# 2048 Game
Clone of 2048 game made in C

## Key Features
- It works!
- Resizeable!
- Adjustable Rows and Cols count
- Win and Retry screen
- Animations

## Screenshots
![Game](/img/game.png)
![Game Over](/img/gameover.png)
## How to build ?
1) Install SDL libs:

    - Debian, Ubuntu.. :
        ```bash
        $ sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev cmake pkg-config
        ```
    - Arch, Manjaro.. :
        ```bash
        $ sudo pacman -S sdl2 sdl2_image sdl2_ttf cmake pkgconf
        ```
2) build it
    ```bash
    $ mkdir build
    $ cd build
    $ cmake ..
    $ make
    ```
## Usage

- Arguments
    - H -> Windows height (min:50, max:10 000, default:800) 
    - W -> Windows width (min:50, max:10 000, default:800)
    - R -> Number of rows (min:2, max:50, default:4)
    - C -> Number of cols (min:2, max:50, default:4) 
    <br><br>

- *notes: Other arguments will be ignored, and if you enter a higher resolution than your monitor has, it may set the resolution to it*
- Example:
    ```bash
    ./2048
    ```
    ```bash
    ./2048 -R 5 -C 5 -W 600 -H 600
    ```
- Key Binds
    - WASD and Arrows - Movement
    - R - Restart game
    - M - Shows game over screen
    - N - Shows win screen (not everyone is good enough to get there legitimately)
    - ESC - Quit game