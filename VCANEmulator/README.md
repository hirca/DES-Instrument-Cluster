# CAN Bus Emulator Application

This application simulates a CAN bus interface, generating realistic vehicle data for testing and development purposes. It's designed to work in conjunction with the Dashboard application or any other CAN bus data consumer.

## Features

- Simulates vehicle speed data
- Generates engine RPM information
- Emulates gear shifts
- Produces battery level data
- Customizable data ranges and update frequencies
- User-friendly interface for data manipulation

## Prerequisites

- Qt 6.x
- C++17 compatible compiler
- CMake 3.16 or higher

## Building the Application

1. Clone the repository:
   ```
   git clone https://github.com/hirca/DES-Instrument-Cluster.git
   cd VCANEmulator
   ```

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
./appVCANEmulator
```

Use the interface to adjust various vehicle parameters:

- Slide the speed control to change the simulated vehicle speed
- Adjust the RPM slider to modify engine RPM
- Select different gears using the gear selector
- Set the battery level using the provided control

The application will continuously send this data over a virtual CAN bus interface, which can be consumed by other applications like the CAN Bus Dashboard.

## Customization

You can modify the data ranges, update frequencies, and other parameters by editing the `CANBusDataManager` class in the source code.

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## License

This project is licensed under the MIT License - see the LICENSE file for details.