# Automatic Curtain Opener

The automatic curtain opener allows curtain to be opened and closed: 
* Remotely 
* At specific times 
* Automatically at dawn and dusk 

Thus allowing users to:
* Wake up naturally using the light of the sun 
* Appear at home, when away travelling

This real-time project utilises a Raspberry Pi 3, light and proximity sensors, a motorised pulley system, custom PCB boards, and a web GUI. 

More details about the hardware and software can be found in the [Wiki](https://github.com/LaurenJA/automatic-curtain/wiki.

### System Overview 

Below is an simple overview of how the deployed sensors and motor could be positioned on the curtain pole. 

![alt tag](image/system-overview.png)

### Build Instructions 

The code related to this project can be found in the software folder.

#### Requirements 
CMake version 3.10 

Python version 3.6

Django version 2.11.1

#### Build 
create build folder 
```
mkdir build 
cd build 
```

Build project using CMake. Be sure to check the output for any errors 
```
cmake .. 
```

Compile the project 
``` 
make
```

To run the program
``` 
./main 
```

To open the folder of the web app(which is named as mysite in this project).
```
cd ...
```

Then run the server.
```
python manage.py runserver
```


