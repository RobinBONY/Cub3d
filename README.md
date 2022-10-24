# Cub3d - Tiny Raycaster


This project is inspired by the world-famous 90’s game 'WOLFENSTEIN', which is considered to be the first FPS ever.

![ef48d3686e28da74fedb0773226e3b58](https://user-images.githubusercontent.com/13594148/197554737-c4fdec93-63cc-415a-9b8a-e9de8d5eca3c.png)

Wolfenstein 3D is the ancestor of games like Doom (Id Software, 1993), Doom II
(Id Software, 1994), Duke Nukem 3D (3D Realm, 1996) and Quake (Id Software, 1996),
that are additional eternal milestones in the world of video games.

# Goals


This project’s objectives are similar to all this first year’s objectives: Rigor, use of C, use of basic algorithms, information research etc.

As a graphic design project, cub3D helped us improve our skills regarding windows, colors, events, fill shapes etc.

![ezgif com-gif-maker(2)](https://user-images.githubusercontent.com/13594148/197533939-e2c7a475-c5f6-4df5-9ab6-ffefd5396a6f.gif)

Cub3D is a remarkable playground to explore the playful practical applications of mathematics without having to understand the specifics.

With the help of the numerous documents available on the internet, we used simple mathematics as a tool to create an elegant and efficient raycasting algorithm.


# Requirements


◉ Must use the miniLibX library, either Mac or Linux version.

◉ Window management must be smooth : passing over of another window, minization, etc.

◉ Display different wall textures that vary depending on which compass the wall is facing (NO, SO, EA, WE).

◉ Must be able to handle different colors for rendering the ceiling and the floor.

◉ Keyboard's directional keys must allow camera rotation.

◉ W, A, S, D keys must allow the player to move in the maze (and the camera accordingly).

◉ Pressing ESC should close the window and quit the program cleanly.

◉ Pressing the red cross atop the window should close it and quit cleanly as well.

◉ The program takes a descriptive file as an argument, which must have .cub as its extension, containing all the map's infos.

◉ The game map must be composed by only 6 characters : 0 for empty spaces, 1 for walls, and N/S/E/W representing the player's starting position as well as its orientation.

◉ The game map must be closed/surrounded by walls, else the program quits and returns an error.

◉ The map must be parsed according to what is in the .cub file. Empty spaces are a valid part of the map. Cub3d should be able to render any valid map.

◉ The .cub file must also provide textures for the game's walls, represented by NO/SO/WE/EA, as well as rgb colors for the floor and ceiling.

◉ If any configuration problem occurs while parsing the file, an error should be returned accordingly.


# Raycasting ?

The idea behind ray casting is to trace rays from the eye, one per pixel, and find the closest object blocking the path of that ray – think of an image as a screen-door, with each square in the screen being a pixel. This is then the object the eye sees through that pixel.

![777px-Camera_models](https://user-images.githubusercontent.com/13594148/197557091-68cf260c-a260-44b1-8158-c9a36be3d999.jpg)


Light rays and the camera geometry form the basis for all geometric reasoning here. 

This figure shows a pinhole camera model for perspective effect in image processing and a parallel camera model for mass analysis. 

The simple pinhole camera model consists of a focal point (or eye point) and a square pixel array (or screen). Straight light rays pass through the pixel array to connect the focal point with the scene, one ray per pixel.


A ray is simply a straight line in the 3D space of the camera model. 

![440px-Cameras_local_coordinate_system](https://user-images.githubusercontent.com/13594148/197558371-05cfe1cd-5071-4e9d-b618-e61f3cc5daf7.jpg)

It is best defined as a direction vector in parameterized form as a point (X0, Y0, Z0) and a direction vector (Dx, Dy, Dz).


# Basic Idea

In our case, the map is a 2D square grid, and each square can either be 0 (= no wall), or a positive value (= a wall with a certain color or texture).

For every x of the screen (i.e. for every vertical stripe of the screen), send out a ray that starts at the player location and with a direction that depends on both the player's looking direction, and the x-coordinate of the screen. 

Then, let this ray move forward on the 2D map, until it hits a map square that is a wall. 

If it hit a wall, calculate the distance of this hit point to the player, and use this distance to calculate how high this wall has to be drawn on the screen: the further away the wall, the smaller it's on screen, and the closer, the higher it appears to be.

![raycastgrid](https://user-images.githubusercontent.com/13594148/197560822-1f8dba87-e0bd-43e8-8a07-1bfd803a5bc8.gif)

To find the first wall that a ray encounters on its way, you have to let it start at the player's position, and then all the time, check whether or not the ray is inside a wall. 

If it's inside a wall (hit), then the loop can stop, calculate the distance, and draw the wall with the correct height. If the ray position is not in a wall, you have to trace it further: add a certain value to its position, in the direction of the direction of this ray, and for this new position, again check if it's inside a wall or not. 

Keep doing this until a wall is finally hit.

# Result

<img width="195" alt="Screen Shot 2022-10-24 at 5 19 10 PM" src="https://user-images.githubusercontent.com/13594148/197563111-bfafc4aa-ee1d-4c3e-9ab2-c273e41e5ece.png">
