## So_long
2D game built in C using the **MiniLibX** library. In this game, the player navigates through a map to collect items and escape through an exit.


- **Gameplay**:
  - Navigate a map to collect all items and reach the exit.
  - Movement controlled with the **Left**, **Right**, **Up**, and **Down** arrow keys.
  - Displays the number of moves made by the player in the terminal.
- **Smooth User Interaction**:
  - Interactive 2D view rendered in a window using MiniLibX.
  - Supports minimizing, focus switching, and resizing.
- **Clean Exit**:
  - Quit the game by pressing **ESC** or clicking the close button.
- **Map Parsing**:
  - Validates a `.ber` map file provided.
  - Ensures maps are rectangular, enclosed by walls, and contain required elements.

### Game Rules
- **Objective**: Collect all collectibles (`C`) on the map and exit through the designated exit (`E`).
- **Movement**: The player (`P`) can move up, down, left, or right on empty spaces (`0`) but cannot pass through walls (`1`).
- The game ends when the player successfully exits after collecting all items.

### Map Requirements
Map must:
- Be a `.ber` file.
- Contain only these characters:
  - `0`: Empty space.
  - `1`: Wall.
  - `C`: Collectible.
  - `E`: Exit.
  - `P`: Player's starting position.
- Follow these constraints:
  - Be rectangular and fully enclosed by walls.
  - Have exactly one `P` and `E`, and at least one `C`.
  - Provide a valid path connecting the player, all collectibles, and the exit.

### Example Map
```txt
1111111111111
10010000000C1
1000011111001
1P0011E000001
1111111111111
```

```Bash
./so_long map.ber
```
