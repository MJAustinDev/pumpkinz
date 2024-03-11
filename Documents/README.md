# Preamble

As the game is a WIP the below will end up changing and will be updated as the game is updated.

# Menu navigation

Text and unique colouring on menu buttons have yet to be implemented (lower priority).
This guide has been written to help you understand how to navigate and play the game.
You use the ```left mouse button``` to click on the menu buttons.

## Main Menu

![main_menu_img](./Images/main_menu.jpg)

- ```New game/continue game``` -- Not implemented yet
- ```Mission select``` -- Opens region select menu
- ```Help/Tutorial``` -- Not implemented yet
- ```Exit``` -- Kills the program

## Region Menu

![region_menu_img](./Images/region_menu.jpg)

- ```Pumpkin patch``` -- Contains 5 active missions
- ```Haunted house``` -- No active missions
- ```Cemetery``` -- No active missions
- ```Cursed forest``` -- No active missions
- ```Vampire castle``` -- Contains 1 active mission
- ```Return to menu``` -- Returns to main menu

The demo mission that uses all the currently implemented enemy types is found in vampire castle.

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

You control the purple cannon and the camera.

- ```Move the cursor``` -- Cannon will aim directly at your cursor
- ```Left mouse button``` -- Will fire a non-explosive bullet
- ```Right mouse button``` -- Will fire an explosive round
- ```WASD``` -- Will pan the camera
- ```Mouse scroll wheel``` -- Will zoom the camera in and out
- ```Esc``` -- Returns to the mission menu

## Enemies

### Pumpkin

![pumpkin_img](./Images/pumpkin.jpg)

Very weak and basic enemy, no powers or effects.

### Skeleton

![skeleton_img](./Images/skeleton.jpg)

More durable enemy, turns into a gravestone after death.

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
Also turns into a gravestone after death.

### Witch

![witch_img](./Images/witch.jpg)

Enemy, can heal damaged enemies and objects.
It's restoration spell is purple.
Also turns into a gravestone after death.

### Vampire

![vampire_img](./Images/vampire.jpg)

Enemy that takes no fall damage, and harms your projectiles.
It's vampirism spell is red.
Also turns into a gravestone after death.

## Goal

As of now there is no implemented win mechanics,
but the ultimate goal will be to kill all enemies with as few shots as possible.
For now just press ```Esc``` when you're finished in a mission.
