# raycasting memo

## `rc.map_x` and `rc.map_y`:
These variables represent the current grid cell in the map array that the player is occupying. This is determined by casting the player’s floating-point position (`state->p_pos.x`, `state->p_pos.y`) to an integer. It is crucial as a starting point for the Digital Differential Analyzer (DDA) algorithm used for raycasting, which will trace a path through the grid cells to find where walls are hit.
## `rc.camera_x`:
This value represents the x-coordinate on the camera plane that the current ray is passing through, normalized to range between -1 and 1. The left side of the screen corresponds to -1, the center to 0, and the right to 1. This normalization helps in calculating the ray’s direction relative to the player’s viewing direction and the camera plane.
## `rc.ray_dir_x` and `rc.ray_dir_y`:
These values are the direction vectors for the ray being cast. They are computed by adding the player’s direction vector scaled by the player’s plane, which is adjusted by `rc.camera_x`. The camera plane’s scaling factor (`rc.camera_x`) adjusts how far from the center of the view the ray is cast, essentially controlling the field of view (FOV).
The calculation uses vector addition where the player's forward direction is adjusted by the camera plane offset, creating a new vector that slants left or right from the player’s direct forward, depending on the value of `rc.camera_x`.
## `rc.delta_dist_x` and `rc.delta_dist_y`:
These represent the distance the ray has to travel in grid units to move one unit along the x and y axes, respectively. These are crucial for the DDA algorithm to determine how much to move the ray along the x and y axes after hitting a side of a grid cell.
They are calculated as the inverse of the absolute values of the ray direction components to ensure that the stepping happens consistently over the grid, no matter the angle of the ray. If the ray direction component is zero, an extremely large number is used instead to avoid division by zero, effectively ensuring the ray moves directly along the other axis without ever considering stepping in this direction.
## `rc.is_obstacle_hit`:
A boolean flag used in the DDA loop to indicate whether the ray has hit an obstacle (a wall). It starts as false and is set to true once the ray encounters a grid cell in the map array that indicates a wall (a non-zero value).
## `rc.is_obstacle_side`:
This flag indicates whether the last hit made by the ray was a vertical (true) or horizontal (false) wall. This information is often used to calculate correct shading or texturing on the walls, as vertical and horizontal walls may be rendered differently.