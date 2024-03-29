# Halloween Artillery Game (Shadow of the Pumpkin-caster -- tentative name)

See the ```Documents``` directory for a more detailed run down of how to build/play the game.
It's a WIP game but the aim is to keep the ```main``` branch playable throughout development.

## Requirements

- Compiler that can handle C++ 20 (or at least C++ 17 if you modify the CMake)
- CMake 2.28 or later
- opengl
- [glfw3](https://www.glfw.org/)
- [box2d](https://box2d.org/)

For more infomation on setting up the external dependencies,
see the ```README.md``` in the ```Extern``` directory.

Example build that I use with my system
```
mkdir -p Builds/CMakeBuild
cd Builds/CMakeBuild
cmake ../.. -G "MinGW Makefiles"
cmake --build ./
```

# TODO List (personal use)

## phase 4

- ~~keyboard input~~
- - ~~A-Z~~
- - ~~0-9~~
- - ~~escape, tab, enter, backspace~~
- ~~screen sizing correctly~~
- - ~~wasd to move screen~~
- - ~~zoom via wheel~~
- - ~~different screen ratios handled~~
- ~~menu system~~
- - ~~main UI~~
- - ~~buttons~~
- ~~level system~~
- - ~~UI~~
- - ~~regions~~
- - - ~~pumpkin patch~~
- - - ~~haunted house~~
- - - ~~cemetery~~
- - - ~~cursed forest~~
- - - ~~'vampire castle' pick a better name lol~~
- ~~pumpkin patch 5 missions (5/5)~~
- score system
- - pass, bronze, silver, gold score per level
- - expensive shots decrease score more
- weapon/ammo selection
- - UI selection
- ~~clean level code~~
- - ~~mission manager~~
- - ~~prevent non-implemented level running~~
- cmake
- - ~~working static build~~
- - map down inter-dependencies
- - presets
- ~~documents for repo~~

## feature pool

- background with 'aim-assisting' grids
- LevelEntities into a class
- bind spell function to spell caster class
- complete control/firing
- struct to clean up entity parameter passing
- - include force, etc so gravestones carry on same path as deceased entity
- - include density, ghost should be less dense
- block destruction (breaking up)
- look into re-vamp-ing... hehehe the input controller (more functional than class)
- more advanced ammo types
- shields
- fancy graphics
- - entities
- - background
- - cannon
- cannon camera if looking in the distance
- toolbox project (contains useful block shapes... good for other projects)
- verify/research KE/force damage model
- cannon moves toward mouse direction rather than snapping
- break total namespace down into modules (future use in other projects... not priority atm)
- re-evaluate circle entity (semi redundant)

# Completed Phases

## phase 1

- ~~lisence~~
- ~~set up building~~
- ~~set up ignore~~
- ~~set up graphics~~
- ~~hello world~~

## phase 2

- ~~test level~~
- ~~blocks~~
- - ~~base~~
- - ~~static~~
- - ~~dynamic~~
- - ~~projectile~~
- - - ~~basic/solid shot~~
- - - ~~explosive~~
- - ~~block~~
- - ~~target~~
- - ~~polygon~~
- - ~~circle~~
- - ~~restructure location~~
- ~~damage~~
- - ~~force~~
- - - ~~Contact Listener~~
- - - ~~KE transfer decided~~
- - - ~~Body User Data Structure~~
- - - ~~Application of force damage in dynamic entity~~
- - ~~water~~
- - ~~explosion (done via particle collision)~~
- ~~player position icon~~
- - ~~base/pivot point~~
- - ~~arrow/barrel~~
- ~~mouse control~~
- - ~~position tracking~~
- - ~~recognise at boarder~~
- - ~~click~~
- - - ~~hold~~
- - - ~~release~~
- - ~~wheel~~
- ~~cleaner license~~
- ~~total namespace~~

## phase 3

- ~~enemy types~~
- - ~~pumpkin~~
- - ~~skeleton~~
- - ~~ghost~~
- - ~~necromancer~~
- - ~~witch~~
- - ~~gravestone~~
- - ~~vampire~~
- ~~5 basic levels (5/5)~~
- ~~counter~~
- ~~level class (better object management)~~
