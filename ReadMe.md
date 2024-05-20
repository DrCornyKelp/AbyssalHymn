# Abyssal Hymn

```
A game by
      ___   _____ ______________   
     /   | / ___// ____/  _/  _/___
    / /| | \__ \/ /    / / / //_  /
   / ___ |___/ / /____/ /_/ /  / /_
  /_/  |_/____/\____/___/___/ /___/

and
  _________                     __                   __                 
  \__  ___/___________    ____ |  | __ _____ _____  |  | __ ___________ 
    |  |  \_  __ \__  \ _/ ___\|  |/ //     \\__  \ |  |/ // __ \_  __ \
    |  |   |  | \// __ \\  \___|    <|  Y Y  \/ __ \|    <\  ___/|  | \/
    |__|   |__|  (____  /\___  >__|_ \__|_|  (____  /__|_ \\___  >__|   
                         \/     \/     \/     \/     \/     \/    \/   
```

---

## Introduction

In "Abyssal Hymn," embark on a mesmerizing journey alongside our main "protagonist" Nakuru, a courageous young girl on a quest to uncover the mystical melodies scattered across a multitude of enchanting realms. From the depths of dense forests to the ethereal heights of celestial skies, and even the infernal depths of both hellish abysses and heavenly realms, immerse yourself in a captivating adventure spanning across diverse landscapes.

As Nakuru, players will harness a versatile set of movement abilities, including the nimble maneuvers of crawling, swift ground and aerial dashes, graceful double jumps, and the acrobatic prowess of wall sliding and jumping. But the journey doesn't end with traversal alone – wield Nakuru's trusty sword to engage in exhilarating combat encounters, mastering the art of parrying bullets amidst the harmonious chaos of each environment.

With each music note collected, unlock fragments of an ancient melody, weaving together the fabric of a profound Abyssal Hymn that holds the key to unlocking the mysteries of the universe. But beware, for challenges and adversaries lie in wait, testing Nakuru's courage and resolve at every turn.

Dive deep into the depths of imagination and embark on an unforgettable odyssey through the symphonic wonders of "Abyssal Hymn," where the power of music serves as a beacon of hope amidst the darkness, guiding Nakuru towards her destiny.

Read Aloud Copy Regenerate Bad Repsonse Message ChatGPT…
Upgrade plan
Get GPT-4, DALL·E, and more @openai... wait oh crap

Yea gonna be honest I am too focus on functionality of the game I completely neglect the story :sob:

---

## SOME OUTSIDE INSTALLATION

- Download **Msys2** on the officical website
- Once done install, open the Mingw64.exe

- Do these things in order
  - `$ pacman -Syu`
  - Close then restart
  - `$ pacman -Su`
  - `$ pacman -S git global`
  - `$ pacman -S git`
  - `$ pacman -S git mingw-w64-x86_64-gcc base-devel`
  - `$ pacman -S mingw-w64-x86_64-clang base-devel`
  - *Note:* Just press Enter whenever they asked you to confirm stuff.

- Include in the PATH user environment variables
  - `%your_msys_folder%/mingw64/bin`
  - `%your_msys_folder%/usr/bin`

## Block Editor Guide

### Input

- **`~`**: execute `Command.a`.
- **`/`**: open/close editor.
- **`Ctrl` + `/`**: minimize/maximize editor.

- **`M1` (drag)**: place block.
- **`M2` (drag)**: delete block.
- **`scroll`**: change block index.

- **`Ctrl` + `m1`**: change block direction.
- **`Ctrl` + `m2`**: split block into `1`x`1` block.
- **`Ctrl` + `scroll`**: change block type.

### Button
- **`Delete`**: delete the last block (highest index).
- **`Global`**: convert blocks on map into "error-proof" blocks.
- **`Save`**: *save* the `map` to `block_<direction>.csv`.
- **`Load`**: *load* `block_<direction>.csv` into `map`.

#### Deep dive into [`Global`]
- **PARTS:** (not in a linear order):
  - **Split**: Split every block into `row`/`column`.
  - **Sort**: Sort every block in the ascending `X`/`Y`(priority) direction.
  - **Merge**: Merge block into `row`/`column`.

- **PROCESSES:**
  - Blocks are split into both `row` and `column`, becoming `1`x`1` blocks.
  - Blocks are sorted in the ascending `X` direction.
  - Blocks are merged into `column`.
  - Blocks are sorted in the ascending `Y` direction.
  - Blocks are merged into `row` to become rectangle

- **REASONS:**
  - `Player` block collision for `wall_sliding` cannot work properly for any *seperate vertically adjacent blocks* due to faulty coding (sorry about that) therefore blocks must be *vertically merged*.

- **ADDITIONAL NOTES:**
  - **Live Blocks**: singular (`1`x`1`) blocks that are placed using editor.
  - **After `Global`**:
    - *Live Blocks* became static and can no longer be tampered using the live editor (Except using `Delete`).
    - The order and number of blocks will not be the same, therefore `Delete` became unstable. `Delete` should only be use on *Live Blocks*.

---

## Personal Draft: 

#### Style:
- 2d platformer 

#### Controller support:
- Yes

#### Player stats:
- health (max 3), mp (for ranged attacks, later stage of dev) 

#### Gameplay:
- Getting from the start to the end of the stage, beating enemies along the way, collecting items for power up, exploring for secrets 

#### Moveset:
- Walk, crouch, crawl, ground dash, crouch dash, air dash, jump, charged jump, double jump, melee attack, ranged attack 

#### Enemies:
- Small slime, big skeleton,… (later stage of development) 

#### Maps:
- Sunlight Valley - Standard Green Zone (2 section: outside field, inside valley)
- Snowy Canyon - Standard Snowy Zone (2 section: outside snow, inside mountain)
- Dusty Mirage - Standard Desert Zone (2 section: outside desert, inside pyramid)
- Ancient Temple - Jungle Temple Area (2 section: outside jungle, inside temple)
- Deep Cavern - Standard Cave Zone (just cave)
- Dead Ahead - Haunted Map with ghost (spooky, 2 section: outside forest, inside mansion)
- Sea Horizon - Beach Map (2 section: beach, sea)
- Cloud Highway - Sky Map (endgame content, extremely hard platforming)

#### Maps Progress

| Map | Background | Platform | Logic Platform | Enemy | Boss
|-|-|-|-|-|-
| **Sunlight Valley** | Done | | | |
| **Snowy Canyon** | Done | | | |
| **Dusty Mirage** | Done | | | |
| **Ancient Temple** | Done | | | |
| **Deep Cavern** | Done | | | |
| **Dead Ahead** | | | | |
| **Sea Horizon** | | | | |
| **Cloud Highway** | | | | |

#### Minigame(?)
- To be decided

#### Score calculation
- To be decided

---

## PROGRESSES UPDATE

### [`10/3`] Planning stages

Movement and game design planning: 

##### Sprites:
- ***#Asciiz*** taking charge of sprite work for main character, some level assets can be borrowed online 

##### Moveset:
- Wall jump (press jump while grabbing wall to jump to an adjacent wall) 
- Dash, Air dash (upgrade, Ultrakill like, starts at 1, upgrade to 3 bars)
- Slide: affected by speed, low speed: crawl, high speed: slide (B button/down) 

##### Combat:  
- **Melee**: smack, 2 hit swing, 1 charge attack, air swing, wall swing, parry flying objects
- **Ranged**: throw jellyfish, parry the jellyfish more velocity & dmg

##### Enemy: 
- slime, ranged enemy, ... 

##### Code platform:
- C++, using the SDL library for display and sound output (foreshadowing)
- Java wasn’t considered because of the lack of performance and because I f*cking hate java lmao 

### [`14/3`] WITTY NITTY STUFF UNVEILED
- Use case, component diagram finished, ready for development 

### [`15/3`] DEMO: DISPLAYING PROGRESS

- Creating a demo version, with only display output 
- Draft version of movement finished, able to move left to right, jump 

### [`16/3`] INDEXING FOR STABILITY

- Added fps control, allowing for consistent framerates
- Drawing sprites, making sprites sheets, indexing actions, adding code for indexes 

### [`17/3`] DYNAMIC OBJECTS AND DIVERSE MOVEMENTS

- Debugging, adding `object2d`
- Added double jump, crawl, dash, added animations for the new moves 
- Added demo block tile (ground)
- Cleaning up the code

### [`18/3`] ENHANCING QUALITY OF LIFE
- Added `Hud`
- Added `Decoration` (static and dynamic)
- Added BGM (demo)
- Added functional `blocks`
- Added hitboxes
- Added `player collision` 
- Air/ground dash improved 
- Added crouch dash
- Added `Maps` 
- Improved code readability 
- Improved movement flow 
- Added crouch under ceiling limit

### [`22/3`] GRID-BASED DECOR AND DEBUGGING

- Combined `dynamic` and `static` `decorations` into one class `Decoration`, `Decoration` now inherit `Object2D` 
- Implement grid style for block, decoration placement in stages
- Moving block logic implementation, setting up debug mode (printing grid lines, grid positions, add godmode) 
- Design and import `Map1` layout 

### [`25/3`] REFINEMENT AND HITBOX FIXES

- Fixes hitbox
- Reorder and split some methods for more consistency: seperation between heavy performance logic like `player movement/collision` and `drawing`
- Implemented `Block Engine`: combine many adjacent block into a singular retangle to reduce collision logic
- Clean up code 

### [`27/3`] EXPANDING GAMEPLAY ELEMENTS

- Added `Npc`
- Combat finished (range attack, parry, charged attack) 
- Separating `input` from movement calculation, allowing for player control outside of just player character (for menu navigation) 
- `Map1` finished (not really)
- `Menu` concept and demo
- Added `Item` 
- Added `Collision`

### [`28/3`] MAP OVERHAUL: SIMPLIFICATION

- Maps’ components are now created/loaded from `<component>.csv` files, no more code, only numbers and letters

### [`1/4`] DYNAMIC PARALLAX IMPLEMENTATION

- Added dynamic parallax background that correspond with the player movement

### [`3/4`] INPUT EVOLUTION: VERSATILITY

- Input can now exist in 3 states: 
  - `Press`: for instant action
  - `Hold`: for repeating action
  - `Threshold`: similar to Hold but only start trigger after a certain time (threshold)
- Clean up old input method for the combat charge attack

### [`8/4`] WORLD NAVIGATION

- `Object2D` has additional method for boundary checking
- Added class `World`
- `Maps` are now a part of `World`, player can switch between `Maps` using the `switchMap()` function
- Each map now includes:
  - `Global Method`: runs regardless of where you are on the world
  - `Active method`: only runs with the player presence 
- Door allows player to move to a different Location{...} 
  - `Location`: {`map index`, `spawn x`, `spawn y`} 
$\Rightarrow$ Player can move between location using `Transition` (from Object2D boundary method) or using `Door`

### [`14/4`] ENGINE CREATION: EMPOWERING DEVELOPMENT

- Includes a lot of functions for map manipulation 
- Flexible syntax
- Current Map Component Manip: `Block`, `Player`

### [`20/4`] EMPOWERING MAP EDITING (ft. Parallax Bg Revamp)

##### Block Editor
- Includes a user-friendly interface allowing for an easier time making map 
- Includes several useful script:
  - Convert LDTK `map.csv` file into a map template (contain the structure but no textures) 
  - Perform the `block engine`'s merging adjacent block features to `map.csv` itself beforehand instead of doing so in runtime

##### Parallax Background:
- Added an independent `background speed` for moving component like clouds, wind, etc 
- Fixes `background size ratio` being affected by the window width and height by making it expand/shrink with respect to a specific window size's property $\Rightarrow$ Background always fits the screen but remains true to original image
- Fixes background jittering when entering new map
- Fixes background snapping when entering a `camera unfocus` section (section where `camera` no longer depends on `player`)

### [`25/4`] LIBRARY ARCHITECTURE OVERHAUL.

- Libraries are now `x64` instead of `x32` $\Rightarrow$ More compatibility with modern system + Higher `long` value (`max: 2^64 - 1`)
- Update `g++` from `6.3.0` to `13.2.0` $\Rightarrow$ Added a new library previously incompatible:
  - `SFML` for audio playback
  - Removing `SDL_mixer` from libraries list due to bad performance and bug infestation

### [`26/4`] AUDIO INTEGRATION AND HARMONY

- Created class `Audio`, each map has their own BGMs playlist with simple properties: { `music’s paths`, `delays`, `random playlist flag` }

### [`27/4`] SPEED CONTROL OPTIMIZATION

- `Speed` (both `horizontal` and `vertical`) is now dynamically adjusted, no longer rigidly constrained to the `speed limit` once it exceeds the maximum threshold.
- If `speed` remains above the `limit` for a certain period of time, it will automatically ease back to the `limit` instead of a "snap back to reality"

### [`28/4`] MEMORY MANAGEMENT

- Added destructors and memory freeing methods to every component in `map` to avoid memory leakage

### [`29/4`] DYNAMIC AUDIO OBJECT

- Created a dynamic `audio object`: audio get louder as player get closer, as well as the ability to override the background music

### [`6/4`] MULTIPLAYER: CONCEPT

- ADDED MULTIPLAYER (concept): Multiple `Player` entities can exist in game, opening up opportunities for functioning multiplayer

### [`12/4`] MULTIPLAYER: FUNCTIONALITY

- `Muliplayer` is now functioning (in demo stages, bugs and missing interactions to be expected)
- `Map Components` now have more interactions with each seperate `player`
- `Camera` dynamically shift to include all `players` on screen
- REWORKED `input` for more compatibility with the new `multiplayer`:
  - Each `player` now has a seperate input method for *multiple controller support (still a WIP)*
  - Improve `input` code readability by explicitly defining keys' by their `name` instead of their indexs `number`
  - Added more methods for involvement with the `map`:
    - Accurate `map` position based on the `mouse position`
    - Accurate `offset` from `main player`
  - Apply the `hold/threshold/threspeak` paradigm from `key input` to `mouse input`
  - Added `wheel` value for scroll direction

### [`24/4`] USER FRIENDLY INTERFACE

- Working opening `Intro` sequence
- Complete `Menu` and `Pause` rework (still under development)

---

## Credits
- ***Asciiz*** (add me on steam I'm 9k elo (I have been cooldown 4 times for team killing for fun) in CS2: 1263698907).
- ***Trackmaker***.
- ***ChatGPT*** for the introduction paragraph lol.