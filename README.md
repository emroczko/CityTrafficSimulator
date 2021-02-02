# City Traffic Simulator
> Application allowing to build roads and simulate traffic on them. 

## Table of contents
* [General info](#general-info)
* [Screenshots](#screenshots)
* [Setup](#setup)
* [Technologies](#technologies)
* [Instruction](#instruction)
* [Tests](#tests)
* [Graphics](#graphics)
* [Contact](#contact)

## General info
City traffic simulator implemented by me and my friend [@Jan Szewczyński](https://github.com/lulek1410) for a university subject. 
App allows to create and delete streets, add and delete cameras and simply to simulate traffic on builded streets. 
Crossings and turns texture are checked and added/changed by the app, so user doesn't have to think about them. 
User can choose one demo project or load previously saved projects from the disk. 
Data is written to txt file. 
This application is not perfect, yet is very big, and a lot of features can be added. 
When we were starting writing the code, we didn't think how big will it be. 

## Screenshots
![Main menu screenshot](Resources/Screenshots/Screenshot1.png)
![Empty grid screenshot](Resources/Screenshots/Screenshot2.png)
![Many streets screenshot](Resources/Screenshots/Screenshot3.png)
![Simulation screenshot](Resources/Screenshots/Screenshot4.png)
![Zoom simulation screenshot](Resources/Screenshots/Screenshot6.png)
![Bigger zoom simulation screenshot](Resources/Screenshots/Screenshot7.png)
![Save/load state screenshot](Resources/Screenshots/Screenshot8.png)


## Setup
In order to make it work you need:
* C++17 Compiler
* SFML Library (You can download it from here: https://www.sfml-dev.org/download.php)
* CMake (You can download it from here: https://cmake.org/download/)

In order to make the tests work you also need BoostTest (You can download it from here: https://www.boost.org/users/download/)

If you have downloaded/installed all the things above on macOS or Linux you have to open terminal in the base folder of downloaded repo. 
Then, to run the application, type into terminal following commands one by one: 
```sh
cmake .
make
./CityTrafficSimulator
```
And the app should start. 

If you want to run tests, type into terminal following commands one by one: 
```sh
cmake -D BUILD_TESTS=ON .
make
./CityTrafficSimulator
```

## Technologies
* C++17
* SFML
* BoostTest

## Instruction
After launching the app, you can choose to create new city, load demo project or load map from file. 
When you click create new city, you can choose how big the grid will be. Then, you will see the main map view. 
You can create streets and delete them. You have to remember to connect you streets to one external road. You cannot modify the external road. 
You can also add camera - they are counting how many cars or trucks passed under them. You can put camera only above the street. 
You can zoom in and out using scroll, and by using arrows you can move the camera. 
You can start simulation by clicking the button start simulation. Now, you can see the vehicles and the city starts living.  
When you click save to file, you can choose on which slot current map will be saved and when it saves you can go back to the map view. 
That's all for now!

## Tests
We have written tests using BoostTest library. There is 62 test cases. 

## Graphics
All the street graphics and buttons graphics was made by [@Jan](https://github.com/lulek1410). Excellent work!

## Status
Project is: _currently finished_

## Contact
Created by [@Eryk Mroczko](https://www.erykmroczko.pl/) and [@Jan Szewczyński](https://github.com/lulek1410).
Feel free to contact us!

## License
We don't have any rights to the background picture in the main menu of application :)

