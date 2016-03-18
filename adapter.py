import os
import usb.core
import usb.util
import usb.backend.libusb1
import time
import serial


USB_IF, USB_TIMEOUT = 0, 5 # set usb interface and timeout
backend = usb.backend.libusb1.get_backend(find_library=lambda x: "/usr/lib/libusb-1.0.so") # set libusb path. If you didn't occur usb.core.find() error, delete this line and modify the usb.core.find() parameters
ser = serial.Serial("/dev/ttyS0", baudrate=57600)
dev = None

while True:
    try:
        while dev is None:
            print "Searching keyboard..."
            try:
                idVendor, idProduct = os.popen("lsusb -v | grep -i keyboard -B 4 | grep -E 'idVendor|idProduct' | grep -E -o '0x.{4}'").read().split("\n")[0:2]
                dev = usb.core.find(idVendor=int(idVendor, 16), idProduct=int(idProduct, 16), backend=backend)
                print dev
                if dev is None:
                    raise ValueError('Device not found')
                # If you didn't use the 'backend', just delete it in find()
                endpoint = dev[0][(0,0)][0]
                if dev.is_kernel_driver_active(USB_IF) is True:
                    dev.detach_kernel_driver(USB_IF)
                usb.util.claim_interface(dev, USB_IF)

                print "Keyboard is ready."
                break

            except:
                print "No keyboards found."

        print "Found keyboard with idVendor {}, and idProduct {}".format(idVendor, idProduct)

    except:
        print "Can not read keyboards now, retrying..."
