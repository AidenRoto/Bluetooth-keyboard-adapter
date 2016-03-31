import os
import usb.core
import usb.util
import usb.backend.libusb1
import time
import serial


USB_TIMEOUT = 5 # set usb timeout
backend = usb.backend.libusb1.get_backend(find_library=lambda x: "/usr/lib/libusb-1.0.so") # set libusb path. If you didn't occur usb.core.find() error, delete this line and modify the usb.core.find() parameters
ser = serial.Serial("/dev/ttyS0", baudrate=57600)

while True:
    dev = None
    try:
        while dev is None:
            print "Searching keyboard..."
            try:
                idVendor, idProduct = os.popen("lsusb -v | grep -i keyboard -B 4 | grep -E 'idVendor|idProduct' | grep -E -o '0x.{4}'").read().split("\n")[0:2]
                # If you didn't use the 'backend', just delete it in find()
                dev = usb.core.find(idVendor=int(idVendor, 16), idProduct=int(idProduct, 16), backend=backend)
                if dev is None:
                    raise ValueError('Device not found')
                endpoints = [] # Some keyboards use second interface to send HID customer reports, I am not sure purpose and usage of the third and higher interfaces, so currently only support to second interface
                try:
                    for i in range(2):
                        if dev.is_kernel_driver_active(i) is True:
                            dev.detach_kernel_driver(i)
                        endpoints.append(dev[0][(i, 0)][0])
                        usb.util.claim_interface(dev, i)
                except:
                    pass

                finally:
                    interfaces_num = len(endpoints)

                print "Keyboard is ready."
                break

            except:
                print "No keyboards found."

        print "Found keyboard with idVendor {}, and idProduct {}".format(idVendor, idProduct)

        while True:
            controls = [None] * interfaces_num
            try:
                for i in range(interfaces_num):
                    controls[i] = dev.read(endpoints[i].bEndpointAddress, endpoints[i].wMaxPacketSize, USB_TIMEOUT)

            except Exception, e:
                if e.errno == 19:
                    raise

            for control in controls:
                if control is not None:
                    print control
                    ser.write(control)
                    ser.write(bytearray([181]))
            
            time.sleep(0.01)

    except Exception, e:
        print e
        print "Can not read keyboards now, retrying..."
