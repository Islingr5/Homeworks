


  _______ _          ______                                               _                  
 |__   __| |        |  ____|                            /\               | |                 
    | |  | |__   ___| |__   ___  ___ __ _ _ __   ___   /  \__      ____ _| | _____ _ __  ___ 
    | |  | '_ \ / _ \  __| / __|/ __/ _` | '_ \ / _ \ / /\ \ \ /\ / / _` | |/ / _ \ '_ \/ __|
    | |  | | | |  __/ |____\__ \ (_| (_| | |_) |  __// ____ \ V  V / (_| |   <  __/ | | \__ \
    |_|  |_| |_|\___|______|___/\___\__,_| .__/ \___/_/    \_\_/\_/ \__,_|_|\_\___|_| |_|___/
                                         | |                                                 
                                         |_|                                                 



**How to Play?**

\-When the program starts, you will have the options to start a new game or load
a saved game. You can access old saves from the load game option. Once you enter
the game, you are free to use the method you want.

\-After any of your actions, the map will always be visible, as well as the
enemies and items in the room will be visible.

\-"Usable" items restore health but disappear from your inventory.

\-"Weapon" items increase your damage and remain in your inventory.

\-There are also items whose functions are completely unknown.

\-You can provide access to the items in your inventory by using the “inventory”
command.

\-If you use the "Attack" option, a combat will start, and it will continue
until either you or the enemy dies, but you can end this combat early by using
“flee” option. However, the enemy will continue to stay there with full health
after a successful flee. You can also access the inventory in the middle of the
combat and use items to heal or change equipment.

\-When you use the "move \<direction\>" command, you can move to a room around
you.

\-"look" command will show the life and damage of this enemy if there is an
enemy in the room you are in.

\-The "Save" option allows you to save your progress. It will also save any
items you haven't collected from the rooms you have cleared.  

________________________________________________________________________________

**GAME LOGIC** -In the game, you can interact with the environment by picking up
and discarding items, as well as moving between rooms. You can find mysterious
items after defeating enemies. Some items are usable. Collect various weapons to
strengthen your character and use health recover items reasonable, because they
are limited in the map.

________________________________________________________________________________

**CODE STRUCTURE**

\-TheEscapeAwakens.exe: The compiled executable file of the game. This is the
file you run to start the game.

\-Makefile: This file contains the instructions for building the project. It
compiles the various C source files into the executable.

 

*C Source Files* 

 

\-game.c: Handles the core game logic, including initializing the game,
combat mechanics, saving/loading game states, and drawing the map.

\-item.c: Manages item creation, attributes, and inventory interactions. It
also handles the saving and loading of item data.

\-enemy.c: Defines enemy behaviors, including random generation, combat
mechanics, and saving/loading enemy states.

*\-player.c: Contains the player's attributes and manages inventory. It also
defines the character struct and related functions.

\-room.c: Responsible for creating the 3x15 grid layout and populating
rooms with random events, enemies, and items.

\-commands.c: Handles command parsing for user actions such as moving,
looking around, attacking, and managing inventory.

 

*Header Files* 

 

\-game.h: Defines structures and function prototypes related to the game’s
logic and mechanics.

\-item.h: Declares item-related structures and functions for item
management.

\-enemy.h: Contains the structures and function prototypes for handling
enemies.

\-player.h: Defines the structures for the player and character, as well as
related functions.

\-room.h: Contains the function prototypes for managing rooms and their
contents.

\-commands.h: Declares the functions for processing player commands.

 
