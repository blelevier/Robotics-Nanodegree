# Project 1 - Build My World

Pick a place where you want to deploy your robot, for example: your apartment, your office, or your favorite restaurant. In addition, create any model of your choice and import a model from the Gazebo library.

## Summary of Tasks

1. Build a single floor wall structure using the Building Editor tool in Gazebo. Apply at least one feature, one color, and optionally one texture to your structure. Make sure there's enough space between the walls for a robot to navigate.
2. Model any object of your choice using the Model Editor tool in Gazebo. Your model links should be connected with joints.
3. Import your structure and two instances of your model inside an empty Gazebo World.
4. Import at least one model from the Gazebo online library and implement it in your existing Gazebo world.
5. Write a C++ World Plugin to interact with your world. Your code should display “Welcome to ’s World!” message as soon as you launch the Gazebo world file.

## Directory Structure

```
    1-BuildMyWorld                     # Main folder 
    ├── images                         # Code output image                   
    │   ├── output.png
    ├── model                          # Model files
    │   ├── Building
    │   │   ├── model.config
    │   │   ├── model.sdf
    │   ├── HumanoidRobot
    │   │   ├── model.config
    │   │   ├── model.sdf
    ├── script                         # Gazebo World plugin C++ script      
    │   ├── hello.cpp
    ├── world                          # Gazebo world file that includes the models
    │   ├── apartment
    ├── CMakeLists.txt                 # Link libraries 
    └──                              
```
 
## Deployment

#### Step 1: Clone the repository
We will be using "/home/workspace/" as an example directory, but feel free to change it according to your path.
```sh
cd /home/workspace/
git clone https://github.com/blelevier/Robotics-Nanodegree.git
```
#### Step 2: Compile the code
```sh
cd /home/workspace/Robotics-Nanodegree/1-BuildMyWorld/
mkdir build
cd build/
cmake ../
make
```

#### Step 4 Add the library path to the Gazebo plugin path
```sh
export GAZEBO_PLUGIN_PATH=${GAZEBO_PLUGIN_PATH}:/home/workspace/Robotics-Nanodegree/1-BuildMyWorld/build
```

#### Step 5 Run the Gazebo World file
 ```
 cd /home/workspace/Robotics-Nanodegree/1-BuildMyWorld/world
 gazebo apartment
 ```
 
 ## Output
 
 <img src="images/preview.PNG" height=300>
