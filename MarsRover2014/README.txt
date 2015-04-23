This Simulink project contains the files for the Mathworks Mars Rover robot competition. The primary model of interest is the simulation model, but also included is a model for execution on an Arduino DUE. The Arduino model uses a number of S-functions for use of the peripherals, including the I2C interface for communication with a Raspberry Pi. More detail on each of these models and the robot itself is included in the project documentation.

================== Quick Start ==================
1. Open the project by double clicking the MakerFaire.prj file in MATLAB
2. Open SimulationModel.slx
3. Press Run to start simulation

================== Requirements ==================
MATLAB r2014a on Windows 7 with Simulink, Stateflow, and some other TBs (add full list here)
Arduino DUE Simulink support package
Install Arduino DUE Windows drivers (copied in support package install, but must be installed by hand)

================== Release Notes ==================

Feb 2015 v1.0 First Public Release


TODO list
- Fix PCB issues:
 - Reversed Power/GND pins on servo headers
 - Add protection diode on battery input
 - Add separate holes for each pushbutton/switch for easier wiring
 - Increase hole size for power module and power input wires
  