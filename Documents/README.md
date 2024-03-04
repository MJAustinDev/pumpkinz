# Preamble

As the game is a WIP the below will end up chaning and will be updated with the game itself.

# Menu navigation

Text and unique colouring on menu buttons have yet to be implemented (lower priority).
This guide has been written to help you understand how to navigate and play the game.

## Main Menu

![main_menu_img](./Images/main_menu.jpg)

- ```New game/continue game``` -- Not implemented yet
- ```Mission select``` -- Opens region select menu
- ```Help/Tutorial``` -- Not implemented yet
- ```Exit``` -- Kills the program

## Region Menu

![region_menu_img](./Images/region_menu.jpg)

- ```Pumpkin patch``` -- Contains 1 active mission
- ```Haunted house``` -- No active missions
- ```Cemetery``` -- No active missions
- ```Cursed forest``` -- No active missions
- ```Vampire castle``` -- No active missions
- ```Return to menu``` -- Returns to main menu

As of now only mission 5 of the pumpkin patch region is active.
It runs a demo mission that uses all the currently implemented enemy types.

## Mission Menu

![mission_menu_img](./Images/mission_menu.jpg)

- ```Mission select (1-15)``` -- Runs that mission if it's implemented
- ```Left/Right sliders``` -- Not implemented but will shift the displayed missions by +/- 15
- ```Mission select``` -- Returns to region menu
- ```Main menu``` -- Returns to main menu

# In game

![in_game_img](./Images/in_game.jpg)

When in game you can press ```Esc``` to return to the mission menu.


## Controls


## Enemies

### Pumpkin

![pumpkin_img](./Images/pumpkin.jpg)

Very weak and basic enemy, no powers or effects.

### Skeleton

![skeleton_img](./Images/skeleton.jpg)

More durable enemy, turns in to a gravestone after death.

### Ghost

![ghost_img](./Images/ghost.jpg)

Very weak enemy, but takes no fall damage.

### Gravestone

![gravestone_img](./Images/gravestone.jpg)

Durable object, can be reanimated into a skeleton by a necromancer.

### Necromancer

![necromancer_img](./Images/necromancer.jpg)

Durable enemy, can raise skeletons from gravestones.
It's necromancy spell is bright green.
Also turns into a skeleton after death.

### Witch

![witch_img](./Images/witch.jpg)

Enemy, can heal damaged enemies and objects.
It's restoration spell is purple.
Also turns into a skeleton after death.

### Vampire

![vampire_img](./Images/vampire.jpg)

Enemy that takes no fall damage, and harms your projectiles.
It's vampirism spell is red.
Also turns into a skeleton after death.

## Goal

As of now there is no implemented win mechanics,
but the ultimate goal will be to kill all enemies with as little shots as possibe.
For now just press ```Esc``` when you're finished in a mission.
