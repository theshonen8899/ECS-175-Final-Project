Jesse Ikawa
ID: 996060633
CSIF Account: jikawa
ECS175 Homework Assignment 4

Description: A 3D scene was rendered using OpenGl. We have 2 cars that are textured and properly lighted driving around the city streets. We have placed multiple office type buildings and housing in blocks. There are people,streetlamps, and trees placed around the road. There is a skybox and a ground texture that is applied as a base. We implemented two camera modes. One which follows either car, or a free movement mode.
 
How to run:
    "cmake ." will construct the Makefile
    "make" to create the executable
    "./p4.x" to run program

Controls:
    "q": Terminates the Program
    "w": Moves the camera forward(in freeview only)
    "s": Moves the camera backward(in freeview only)
    "a": Pans the view horizontally left
    "d": Pans the view horizontally right
    "c": Switch car views OR link camera to car if in freeview mode
    "f": Turn on freeview mode.

    Holding the mouse and moving it will rotate the camera, rotation/CameraPan/CameraMovement allow exploration of any position of the skybox. When linked to car, camera will not go below ground.
    
