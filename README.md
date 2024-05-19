# 5dof-Manipulator-firmware
This Git repository hosts the firmware and software developed for control of a 5-degree-of-freedom (DOF) manipulator. The manipulator is designed for precise  control, integrating feedback loops for all its links to enable position trackback mechanism.
## Hardware used:
>STM32 Black Pill Micro controller
>Jetson orin
## Prerequisites and Platform:
ROS 1
Rosserial 
Platform IO
## Architecture:
![arch](https://github.com/ayushle/5dof-Manipulator-firmware/blob/main/5dof-Manipulator-arch.drawio.png)
## Initial Setup:
Intigate the following in different terminals of on board computer:
```bash


    roscore
```  
```bash

    sudo chmod 666 /dev/ttyACM0
    rosrun rosserial_python serial_node.py /dev/ttyACM0
```
> [!CAUTION]
> Make sure to replace your active port with "**ACM0**" in above mentioned commands.

Intigate the following in different terminals of on remote computer:
```bash


  source devel/setup.bash
  roslaunch teleop_twist_joy teleop.launch
```
```bash


  source devel/setup.bash
  rosrun teleop_twist_joy explore
```
> [!CAUTION]
> Make sure to replace your active port with "**js0**" in launch file.
> It is at "**joystick/src/teleop_twist_joy/launch**" location.

> [!NOTE]
> Change "**command.data**", it is pwm values to different links +ve is one direction and -ve is counter of that, for all the buttons to control sensitivity of links.
> It is in "**joystick/src/teleop_twist_joy/src/remap_map.cpp**".
