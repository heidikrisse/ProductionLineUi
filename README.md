# ProductionLineUi

## Monitoring / UI / Telemetry requirements - Group 3

Create a monitoring / UI system for the production line.

- Figure out how to input / output data
    - You'll need to agree with the other teams on this.

- Create analytics data from the data received from the production line
    - Historical failure rates?
    - Operating costs?  (The costs of breakdowns, unit price, etc. could be configurable)

- Create UI software for the production line
    - Use Qt for graphical interface
        - UI should be separated from logic as much as possible (it is possible to delay the separation,
          but it needs to be taken into account or it will become *hard*)
    - Display analytics data received from the production line in a clear manner
    - Allow users to set the production line parameters manually or automatically.  (Fun fact:
      An analogue of the manual thing here is what caused Chernobyl disaster!)
        - Send commands to control software / firmware (you'll need to agree on protocol)
    - Allow viewing of analytics/telemetry data and saving it to a file/database/something
    - **Documentation**
        - This part is the user-facing part, so documentation shouldn't be overly technical, and more like
          an user guide.

### Production line tech specs - for all the groups 1 - 3

#### Sensors

- Production line convoyer has variable speed, measured in units pushed through/minute.
    - The maximum speed of the convoyer is 600 units / minute
    - The minimum speed of the convoyer is 0 units / minute
    - The convoyer uses power linearly from 350W to 20000W, depending
      on the speed of the production line (350W at stop, 20000W at full speed)
    - The convoyer works perfectly up to 80°C
    - Convoyer's efficiency is 0% at minimum speed and rises linearly to 44% at 10% speed, after which it is constant
        - efficiency here measures how much of the power is converted to heat (100% at min speed, 56% at 10% speed)
    - The convoyer has a sensor that reports its current speed in linear scale as a 8-bit unsigned integer
      (0 = 0u/m, 255 = 600u/m)

- Production line has three steps of assembly
    - A heater heats the product for shaping
        - Formed of 3 2000W heating elements, individually controllable
    - A shaper shaper
    - A bolter bolts

- Cooling system
    - The production line will be equipped with a cooling system, that can dissipate some heat, but exact details
      are still up in the air (or changing every week)

- 10 TI-LM35C temperature sensors are spaced out evenly across the product line, which
  measure the temperature.

- A DFR0833/OpenMV-H7 camera (OV7725 image sensor) is used at the end of the production
  line for quality control
    - The quality control system can handle maximum of 542 units / minute, after which it fails everything
    - The quality control system measures 16 units at one go, before checking the next 16
    - The incoming data from the camera is just `uint16_t` bitmask of failed QC checks



#### Controls

- Convoyer target speed can be adjusted by user from 0 (0 / units) to 255 (600 units / minute)
    - Convoyer's acceleration/deceleration is at maximum 1 units/minute /second.

- Heating elements are simply large metal resistors that can be turned on or off individually.
- Cooling system can be turned on/off
- QC camera can be turned on/off

## Group 3: 

- [Elisa](https://github.com/ElisaHoo)
- [Ville](https://github.com/kapteenimuttipolpa)
- [Heidi](https://github.com/heidikrisse)

## Prerequisites

- Git
- CMake
- Qt Creator

## Setup Project

### 1. Clone the repository

```shell
git clone https://github.com/heidikrisse/ProductionLineUi.git
```

### 2. Fetch the submodules (Ubuntu and openSUSE Leap 15.5)

```shell
# Install packages (Ubuntu)
sudo apt-get install libssl-dev libpaho-mqtt-dev
```

```shell
# Install packages (openSUSE Leap 15.5)
sudo zypper install libopenssl-devel libpaho-mqtt-devel
```

```shell
# To add the submodules
cd ProductionLineUi
cd production_line_ui
git submodule add https://github.com/eclipse/paho.mqtt.c.git
git submodule add https://github.com/eclipse/paho.mqtt.cpp.git

# To initialize and update the submodules:
git submodule update --init --recursive
```
### 3. Install library to create charts

```shell
# Ubuntu
sudo apt install libqt5charts5-dev
```

```shell
# openSUSE Leap 15.5
sudo zypper install libQt5Charts5-devel
```

### 4. Build and run the project using Qt Creator

- Open Qt Creator.
- Select File > Open File or Project.
- Navigate to the directory where you cloned ProductionLineUi
- Navigate to the 'production_line_ui':
  ```shell
  cd production_line_ui
  ```
 - Select the CMakeLists.txt
- Once the project is loaded, configure the build settings
- Click the Build button to compile the project
- After building, click the Run button to execute the project
