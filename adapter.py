import os
import usb.core
import usb.util
import usb.backend.libusb1
import time
import serial


USB_IF, USB_TIMEOUT = 0, 5 # set usb interface and timeout
backend = usb.backend.libusb1.get_backend(find_library=lambda x: "/usr/lib/libusb-1.0.so") # set libusb path. If you didn't occur usb.core.find() error, delete this line and modify the usb.core.find() parameters

while True:
    try:
        idVendor = idProduct = None
        while (not idVendor) and (not idProduct):
            print "Searching keyboard..."
            try:
                idVendor, idProduct = os.popen("lsusb -v | grep -i keyboard -B 4 | grep -E 'idVendor|idProduct' | grep -E -o '0x.{4}'").read().split("\n")[0:2]
                dev = usb.core.find(idVendor=idVendor, idProduct=idProduct, backend=backend)
                # If you didn't use the 'backend', just delete it in find()

            except:
                print "No keyboards found."

        print "Found keyboard with idVendor {}, and idProduct {}".format(idVendor, idProduct)

    except:
        print "Can not read keyboards now, retrying..."
