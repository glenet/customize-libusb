#include <stdlib.h>
#include <stdio.h>
#include <libusb/libusb.h>
#include "usbwrapper.h"

#define LIBUSB_PATH "/data/libusb1.0.so"


static void PrintDevs(libusb_device **paDevs, struct USBWrapper *psUsbWrapper)

{
	libusb_device *dev;
	int i = 0, err;

	while ((dev = paDevs[i++]) != NULL)
	{
		struct libusb_device_descriptor desc;
		err = psUsbWrapper->get_device_descriptor(dev, &desc);
		if (err)
		{
			/* Skip to the next device */
			printf("Failed to get device descriptor\n");
			continue;
		}
		printf("%04x:%04x\n", desc.idVendor, desc.idProduct);
	}
}

int main(int argc, char **argv)
{
	struct USBWrapper sUsbWrapper;
    libusb_device **paDevs;
    libusb_context *ctx;
    ssize_t cnt;
	int err;

	err = GetLibUsb(&sUsbWrapper, LIBUSB_PATH);
	if (err)
	{
		printf("Failed to get libusb instance\n");
		goto err_out;
	}

    err = sUsbWrapper.init(&ctx);
    if(err)
	{
		printf("Failed to init usb\n");
        return 1;
    }

	sUsbWrapper.set_debug(ctx, 3);

    cnt = sUsbWrapper.get_device_list(ctx, &paDevs);
    if(cnt < 0) {
		printf("Failed to get devices\n");
        return 1;
    }

	PrintDevs(paDevs, &sUsbWrapper);

    sUsbWrapper.free_device_list(paDevs, 1);
    sUsbWrapper.exit(ctx);

err_out:
	return err;
}
