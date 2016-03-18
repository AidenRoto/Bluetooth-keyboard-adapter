# Bluetooth-keyboard-adapter
This project is based on Linkit smart 7688 Duo board, but is compatible with other boards with some modifications.

I really like to use my [KBP mini V60](https://www.facebook.com/media/set/?set=a.870489189643222.1073741835.316701428355337&type=3) mechanical keyboard, And I've wondered is there a Bluetooth adapter that can enhance this keyboard into a Bluetooth wireless keyboard. There are some products like [ATEN CS533](http://www.aten.com.tw/products/手持式裝置週邊與USB/TapUSB轉Bluetooth鍵盤滑鼠切換器/~CS533.html#.Vujzw8eLTcY), but there are issues saying that they are not compatible with some mechanical keyboards, so I decided to build my own Bluetooth keyboard adapter.

When [Raspberry pi zero](https://www.raspberrypi.org/products/pi-zero/) was released, it seems to be the best choice as the central part of the adapter, but pi zero is always out of stock, so when I found [Linkit smart 7688 (Duo)](http://home.labs.mediatek.com/hello7688/?gclid=Cj0KEQjw5Z63BRCLqqLtpc6dk7gBEiQA0OuhsLLn9KMJ94rh7Wxj8knOw5i-hPy-99o40BoDHnrRvdIaAvp18P8HAQ) is easier to buy now, I then decide to use this board as the adapter, and also, the Wi-Fi on 7688 gave me some more idea to build extra function in this project. Besides, MCU on 7688 Duo can separate the code which communicates with HID Bluetooth module into MCU, and ensure no interrupts in MPU will break the communication with Bluetooth module.

## Hardwares
* [Linkit Smart 7688 Duo](http://home.labs.mediatek.com/hello7688/?gclid=Cj0KEQjw5Z63BRCLqqLtpc6dk7gBEiQA0OuhsLLn9KMJ94rh7Wxj8knOw5i-hPy-99o40BoDHnrRvdIaAvp18P8HAQ)  
	This part can be replaced with raspberry pi, banana pi, etc as long as the board supports Serial read and write, and runs an linux system on it. You can choose it by yourself(offcourse you'll like your adapter as small as possible and energy saving!).
	
* [Bluefruit EZ-Key 12 input Bluetooth HID Keyboard Controller](https://www.adafruit.com/products/1535)  
	This is the most expensive part, there is also some HID Bluetooth modules you can choose, so you can modify the MCU code to communicate with the bluetooth module you choose.
	
* (optional) Arduino  
	If you use 7688 Duo, this part is already included, but if you use raspberry pi, and want to seperate the code which communicates with bluetooth module, you'll need an Arduino.
	
* Battery  
	You can use any batteries, or power bank as the power source, just make sure your board can work with it.
	
## Block Diagram
The main idea is this:
![](readme_img/main_idea.png)

and Linkit it smart 7688 Duo already contains the Linux system, Wi-Fi, MCU parts!

## Installation
In order to read usb, 7688 (or other board) must has the ability to read a usb device.

run

    $ opkg update
    $ opkg install kmod-input-core
    $ opkg install kmod-input-evdev
    $ opkg install kmod-usb-hid
    $ opkg install usbutils
    $ opkg install libusb-1.0
    
to install prerequest packages. Now you're able to connect a usb keyboard, and run the command

    $ lsusb
    Bus 001 Device 001: ID 1d6b:0002 Linux Foundation 2.0 root hub
    Bus 002 Device 005: ID 04d9:0112 Holtek Semiconductor, Inc.
    Bus 002 Device 001: ID 1d6b:0001 Linux Foundation 1.1 root hub
    
and you'll found a different usb device name, that is your keyboard. Or, you can run

    $ lsusb -v
    ...
      iManufacturer           0
      iProduct                2 USB-HID Keyboard
      iSerial                 0
    ...
    
and if some patterns like USB-HID Keyboard, then your board is able to use the keyboard.

Then clone the [pyusb](https://github.com/walac/pyusb) in github(since pip install pyusb and pip install pyusb --pre report no match version, you can clone from the repository)

    $ git clone https://github.com/walac/pyusb
    $ cd pyusb
    $ python setup.py install
    
then you just installed the pyusb package. If you look into the adapter.py, you'll find that there is a weird code

    backend = usb.backend.libusb1.get_backend(find_library=lambda x: "/usr/lib/libusb-1.0.so")
    
This is because python in 7688 did not search the path /usr/lib, so I added manually. If your board do search this path or save libusb in other path, you should modify this part.

