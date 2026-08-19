Description: 

This is an example console program that utilizes the Skyetek C API.  It will detect all Skyetek RFID
 modules connected, perform several connect/disconnect cycles of the interface, and execute an
 inventory select to find all tags in the field. 


System configuration:

- Serial - The appropriate serial ports (/dev/ttyS0, /dev/ttyS1, etc) need user r/w permissions.

- USB - The Skyetek API utilized the libusb library for accessing usb devices. On most distros, the
 HID driver claims the device upon initialization.  The API handles this by calling a libusb function
 to detach the kernel driver, but the device needs user r/w permissions for this to occur.  To
 automate the process, a udev rule should be added.  See the included 85-skyemodule.rules file
 included in this directory.  Udev rules are typically located in /etc/udev/rules.d/
  

Build:

0. Be sure you done the prerequisite setup described in "System configuration:"
 especially if you are using a USB reader.

1. Compile Example

  cd get_tags
  make

 No separate step is necessary to build the SkyeTekAPI.
 The example's Makefile will automatically call SkyeTekAPI/unix/Makefile.

2. Run Example

  ./example
