#ifndef USBWRAPPER_H
#define USBWRAPPER_H

#include <libusb/libusb.h>

struct USBWrapper {
	int (*init)(libusb_context **);
	void (*exit)(libusb_context *);
	void (*set_debug)(libusb_context *, int);
	ssize_t (*get_device_list)(libusb_context *, libusb_device ***);
	libusb_device_handle *(*open_device_with_vid_pid)(libusb_context *,
	                                                  uint16_t, uint16_t);
	void(*libusb_close)(libusb_device_handle *);
	int (*get_device_descriptor)(libusb_device *,
	                             struct libusb_device_descriptor *);
	void (*free_device_list)(libusb_device **, int);
};

int GetLibUsb(struct USBWrapper *psUsb, const char *path);

#endif
