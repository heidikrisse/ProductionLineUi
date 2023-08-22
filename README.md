# ProductionLineUi

Monitoring / UI / Telemetry requirements
========================================
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

### Group: 

- [Elisa](https://github.com/ElisaHoo)
- [Ville](https://github.com/kapteenimuttipolpa)
- [Heidi](https://github.com/heidikrisse)

### Prerequisites

- Git
- CMake
- Qt Creator

### Setup Project

1. Clone the repository

```shell
git clone https://github.com/heidikrisse/ProductionLineUi.git
```

2. Fetch the submodules

# To add the submodules
```shell
cd ProductionLineUi
cd production_line_ui
git submodule add https://github.com/eclipse/paho.mqtt.c.git
git submodule add https://github.com/eclipse/paho.mqtt.cpp.git

# To initialize and update the submodules:
git submodule update --init --recursive
```

3. Build and run the project using Qt Creator:

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
