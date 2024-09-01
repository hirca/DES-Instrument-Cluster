# Instrument Cluster as Qt Dashboard Application

This application provides a visual dashboard interface for displaying CAN bus data, specifically designed for automotive use. It features a speedometer, RPM gauge, battery level indicator, and gear display.

## Features

- Real-time display of vehicle speed
- Engine RPM visualization
- Current gear indicator
- Battery charge level display
- Smooth animations and transitions
- Customizable color zones for speed and RPM

## Prerequisites

- Qt 6.x
- C++17 compatible compiler
- CMake 3.16 or higher

## Building the Application

1. Clone the repository:
   ```
   git clone https://github.com/hirca/DES-Instrument-Cluster.git
   cd Dashboard
   ```

2. Copy the needed interface bridge class and header file from `IDashboardBridge` folder to `Dashboard` folder. Virtual CAN: `VCAN0`, Physical CAN: `CAN0`.

2. Create a build directory and navigate to it:
   ```
   mkdir build && cd build
   ```

3. Run CMake and build the project:
   ```
   cmake ..
   make
   ```

4. The executable will be created in the `build` directory.

## Usage

Run the application:

```
./appDashboard
```

The dashboard will attempt to connect to a CAN bus data source. Ensure that your CAN bus emulator or actual CAN bus interface is set up and running before starting the dashboard.

## Customization

You can customize various aspects of the dashboard by modifying the QML files in the `qml` directory. Key files include:

- `Dashboard.qml`: Main dashboard layout
- `Speedometer.qml`: Speedometer component
- `Tachometer.qml`: RPM gauge component
- `BatteryDisplay.qml`: Battery level display
- `GearIndicator.qml`: Current gear indicator

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## License

This project is licensed under the MIT License - see the LICENSE file for details.