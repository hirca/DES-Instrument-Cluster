# Qt CAN Bus Interface for Dashboard

This project provides a Qt-based interface for receiving and displaying CAN bus data, specifically RPM and speed information, on a Raspberry Pi.
There are two versions of interface **vcan0** for Virtual Can Bus system **can0** is real can data system.

## Hardware Requirements

- Raspberry Pi (tested on Raspberry Pi 4)
- CAN Bus interface module (e.g., MCP2515)
- 2-Channel CAN bus expansion HAT

## Software Requirements

- Qt 6
- socketcan kernel module

## Setup

1. Open I2C Interface in Raspberry PI : 	

	```
	sudo raspi-config 
	```
   Choose Interfacing Options -> I2C -> Yes.

   Reboot Raspberry PI

   ```
	sudo reboot
	```
2. Install Required Libraries

- **bcmp2835**

	```
	wget http://www.airspayce.com/mikem/bcm2835/bcm2835-1.60.tar.gz
	tar zxvf bcm2835-1.60.tar.gz 
	cd bcm2835-1.60/
	sudo ./configure
	sudo make
	sudo make check
	sudo make install
   ```
- **can-utils**

   ```
   sudo apt-get install can-utils
   ```

3. Dual SPI Mode: CAN_0 uses SPI0-0, interrupt pin is 25, CAN_1 uses SPI1-0, interrupt pin is 24.

   Add the following to `/boot/config.txt`:

   ```
   dtparam=spi=on
   dtoverlay=spi1-3cs
   dtoverlay=mcp251xfd,spi0-0,interrupt=25
   dtoverlay=mcp251xfd,spi1-0,interrupt=24
   ```

   Reboot Raspberry PI


   ```
   sudo reboot
	```


4. After rebooting, bring up the CAN interface:

   ```
   sudo ip link set can0 up type can bitrate 500000
   ```
5. To make this persistent across reboots, you can add it to `/etc/network/interfaces`

   ```
   sudo nano /etc/network/interfaces
   ```
   Add these lines:

   ```
   auto can0
   iface can0 inet manual
      pre-up /sbin/ip link set $IFACE type can bitrate 500000
      up /sbin/ifconfig $IFACE up
      down /sbin/ifconfig $IFACE down
   ```


5. Clone to codes according to your needs to Dashboard project

6. Compile the Qt project with CMake:

7. Run the compiled application.

## Usage

### For Virtual CAN (Testing/Development)

If you're using a virtual CAN interface for testing or development:

1. Set up a virtual CAN interface:

   ```
   sudo modprobe vcan
   sudo ip link add dev vcan0 type vcan
   sudo ip link set up vcan0
   ```

2. Use the original `IDashboardBridge` class (not provided in this repository) which is set up for `vcan0`.

### For Physical CAN Hardware

When using real CAN hardware:

1. Ensure your CAN interface is properly set up as described in the Setup section.

2. Use the `IDashboardBridge` class provided in `can0` repository, which is configured for the `can0` interface.

## Class Overview: IDashboardBridge

`IDashboardBridge` serves as the interface between the CAN bus and the Qt application. It:

- Connects to the CAN bus interface
- Receives and processes CAN frames
- Updates Qt properties for speed, RPM, gear, and battery level
- Emits signals when data changes, allowing the UI to update

## Customization

- Modify the `CAN_FRAME_ID` in `idashboardbridge.h` if your CAN frames use a different ID.
- Adjust the frame parsing in `processCANFrame()` if your CAN frame format differs.

## Troubleshooting

- Ensure the CAN interface is up and running (`ip -details link show can0`)
- Check system logs for any CAN-related errors (`dmesg | grep can`)
- Verify that your Qt application has the necessary permissions to access the CAN interface


