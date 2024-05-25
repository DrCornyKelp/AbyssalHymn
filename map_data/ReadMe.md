## Map Data Introduction

### [`map`]
- Represents dynamically changing **objects** that store information updated throughout the game. These **objects** retain the latest saved data, ensuring that revisiting maps display the most recent information.
### [`map_data`]
- A folder that consists of static files initialized for each new game session. These files provide a baseline or starting point for the **`map`**, ensuring consistency across different game sessions.

---

## Map Data Components

### General Values

- `x, y`: object position.
- `w, h`: width and height.
- `hw, hh`: hitbox's width and height
- `sw, sh`: sprite's width and height
- `sim, sfm`: sprite animation properties:
  - `sim`: sprite index max, the number of frames in a sprite sheet.
  - `sfm`: sprite frame max (**WARNING**: not *sprite sheet's "frame"* BUT "frame" as in *frame-per-second*), after a certain amount of frame increase the value of `sprite index`.
- `box _`: a trigger box, object must be in the boundary of the `box` for certain method to activate.
  - E.X:  `box up/down/left/right(respectively) = {20, 10, 5, 9}`, `object pos = {15, 7}`, because `boxL < objX < boxR` and `boxD < objY < boxU` $\Rightarrow$ Trigger a certain method

### [`block_main` - `block_back`]`.csv`
- `type`, `x`, `y`, `w`, `h`,
- `<w x h> index vector`

| `type` | Type | Description
|-|-|-
| `0` | Solid | Standard Collision Block
| `1` | Ice | Slippery Block
| `2` | Go Through | No Collision
| `3` | Bridge | Platform Block
| `4` | Water | Water Logged
| `5` | <ERROR> | Under maintanence
| `6` | <ERROR> | Under maintanence

### [`block_hidden`]`.csv`
- `-1`, `x`, `y`, `w`, `h`,
- `<w x h> index vector`

- Hidden Blocks are blocks that reveal themself upon contact with player, use `>` to seperate sections of hidden blocks.
- EX:

```cpp
-1,8,6,2, 6,10,10,10,10,10,10,10,10,10,10,6,7
-1,10,6,2, 2,10,10,7,10
-1,3,7,5, 5,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,7,7
>
-1,47,0,2, 6,10,10,10,10,10,10,10,10,10,10,10,10
-1,49,0,2, 5,10,10,10,11,10,11,10,11,10,11
>
```

  - Uses basic `block` syntax with a `>` to seperate each section.
  - Contact with any block of a section $\Rightarrow$ reveal the entire section.

### [`block_path`]`.csv`
- Contains directory to block's tileset.

### [`decoration_back`-`decoration_front`]`.csv`
  - Starts with **`type`**: `0` / `1` / `2`
#### - Type 0: Static
  - `0`, `path`, `x`, `y`, `w`, `h`, `alpha`
#### - Type 1: Animation Sheet (for short animation with small sprite sheet)
  - `1`, `path`, `x`, `y`, `w`, `h`, `sw`, `sh`, `sim`, `sfm`, `alpha`
#### - Type 2: Animation Folder (for long animation with large sheets)
  - `2`, `folder path`, `x`, `y`, `w`, `h`, `sim`, `sfm`
  - **NOTE:** folder path must include a "/" at the end (E.X: `assets/Decoration/City/`).

### [`background`]`.csv`

##### - [`Background color`]
- `*`, `red`, `green`, `blue`
  - If nothing, default `0`, `0`, `0` or `black`

##### - [`Background layer`](for parallax background)

- `layer path`, `w/h ratio`, `scale speed x`, `scale speed y`, `independent speed x`
- **NOTES:**
  - **`w/h ratio`**: the ***width* / *height* ratio** of the background image (this is necessary to **accommodate different window's width - height**)
  - **`scale speed`**(`0 < sclSpd < 1`): the ratio of layer's distance cover with respect to player.
    - E.X: `scale speed x = 0.1`, *Player* move `player move x = 100` $\Rightarrow$ *Layer* move `layer move x = 100 * 0.1 = 10`.
  - **`independent speed x`**(`iSpd > 0`): when adding an independent speed value to a layer, it will moves on its own in a loop in the horizontal direction, independent from player movement.

  $\Rightarrow$ **`scale speed x`** and **`independent speed x`** **cannot coexist**, once you specify a specific `speed x`, the other must be `0`.

  - Layer's movement is opposite to player, so as the **player move right**, each **layer move left**, **player move up**, each **layer move down**, a distance based on the `scale speed` (`scale speed x` is ignored for non-`independent x` layers).

### [`playlist`]`.csv`
- A list of **background soundtracks** for a specific `Map`:
  - `Music Path`, `delay`
  - `*`

- **`delay`**: a period of delay after previous track finished.
- When adding a **`*`** on the last line $\Rightarrow$ Playlist will be **shuffled**.
- **Note**: If two `playlist` are the same (same paths, same after delays, both random/not random) $\Rightarrow$ Map Playlist remains, no changes .

### [`bubble`]`.csv`
- Popup Bubble
- `bubble type`, `bubble path`, `x`, `y`, `w`, `h`, `box up`, `box down`, `box left`, `box right`, `offset x`, `offset y`, `max alpha`

- **3 Types** of bubble.
  - *Type 0*: Standard.
  - *Type 1*: Follow Player.
  - *Type 2*: Absolute On Screen.
- **NOTES**:
  - Although type 1 bubble ignores `x` and `y`, they must still be included in `bubble.csv` (tip: set them to an arbitrary value like `0` or `-1` for clear distinction).

### [`door`]`.csv`
- `style`, `handle left`, `door x`, `door y`, `map index`, `spawn x`, `spawn y`, `star count`
  - **`style`**: the door path index, refer to assets/Door and see which one looks best
  - **`handle left`**: the direction of the door's handle, **`0`** if on the **right** and **`1`** if on the **left**.
  - **`star count`**: the number of star needed to unlock door.

### [`audio_obj`]`.csv`
- A dynamic proximity audio source with volume based on player distance from the source.
- `audio path`, `audio x`, `audio y`, `radius effect`, `radius max vol`, `radius override`
  - **`radius effect`**: the radius in which the audio volume start changing
  - **`radius max vol`**: the radius in which the audio reach max volume (`vol = 100`)
  - **`radius override`**: the radius in which the map `playlist` volume reached `0`
- **Note**: for `radius effect`, the closer the player is to the source
  - The higher the `source volume`
  - The lower the `map playlist (or background music) volume`

### [`transit_map`]`.csv`
- For map transition. When player come in contact with a **`box`**, apply change to player's **`location`**.

- `box up`, `box down`, `box left`, `box right`, `map index`, `spawn x`, `spawn y`

### [`camera_box`]`.csv`
- For camera boundary. When player position is within the **`box`**, **`camera`** is lock to a *`border`*.

- `box up`, `box down`, `box left`, `box right`, `border up`, `border down`, `border left`, `border right`

### [`Exclusive Function`]`.h`
- Functions that are **unique** to each map and have **high level of customization**
  - **[`exclusive_init`]**: For preprocessing.
  - **[`exclusive_update`]**: For runtime.

- **NOTES for [`exclusive_update`]**
  - Use *`map->MapActive`* for updates between *global* and *active* function
    - **`GlobalFunction`**: functions that are updated globally despite their activity state (E.X: daynight cycle, weather, ... must be consitent between each map as, well, that's kinda common sense).
      - **DISCLAIMER**: There's no weather/daytime cycle for my game (yet).
    - **`ActiveFunction`**: functions that are only updated while their `map` are active (E.X: halt all enemy movement/logic to avoid those pesky spawn camper).

---

## Additional Notes

- Position/Size are calculated using a 64x64 pixel grid.
  - E.X: `x = 1` $\Rightarrow$ `real_x = x * 64`

- `Decoration` is usually for some cool looking decorations with high level of details like trees, houses, even people, not to be confused with `block_back` which purpose is to serve as a pseudo `decoration` that acts under the influence of `Block` for an easier time editing map.
  - **ADHD version**: `block_back` are the impostor of `decoration` that works under `Block`.

- For **`door`** and **`transit_map`**, set `map_index = -1` to stay in current map.

- Type `2` decoration is very **performance/memory intensive** and has **no alpha mode** so transparency is not an option.

- General order of drawing:
  - Background (parallax)
  - Back Block (the pseudo decoration mentioned above)
  - Back Decoration
  - Entity (player, enemy, bullet, ...)
  - Front Block
  - Front Decoration