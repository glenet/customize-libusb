#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "usbwrapper.h"

int GetLibUsb(struct USBWrapper *psUsb, const char *path)
{
	int err = -ENOMEM;
	void *fHandle;

	if (!psUsb || !path)
	{
		err = -EINVAL;
		goto err_out;
	}

	fHandle = dlopen(path, RTLD_NOW);
	if (!fHandle)
	{
		printf("Failed to open libusb at %s\n", path);
		goto err_out;
	}

	/* initial some necessary functions */
	psUsb->init = dlsym(fHandle,"libusb_init");
	if (!psUsb->init)
	{
		printf("Failed to acquire libusb_init\n");
		goto err_out;
	}
	psUsb->exit = dlsym(fHandle,"libusb_exit");
	if (!psUsb->exit)
	{
		printf("Failed to acquire libusb_exit\n");
		goto err_out;
	}
	psUsb->set_debug = dlsym(fHandle,"libusb_set_debug");
	if (!psUsb->set_debug)
	{
		printf("Failed to acquire libusb_set_debug\n");
		goto err_out;
	}
	psUsb->get_device_list = dlsym(fHandle,"libusb_get_device_list");
	if (!psUsb->get_device_list)
	{
		printf("Failed to acquire libusb_get_device_list\n");
		goto err_out;
	}
	psUsb->open_device_with_vid_pid = dlsym(fHandle,"libusb_open_device_with_vid_pid");
	if (!psUsb->open_device_with_vid_pid)
	{
		printf("Failed to acquire libusb_open_device_with_vid_pid\n");
		goto err_out;
	}
	psUsb->libusb_close = dlsym(fHandle,"libusb_close");
	if (!psUsb->libusb_close)
	{
		printf("Failed to acquire libusb_close\n");
		goto err_out;
	}
	psUsb->free_device_list = dlsym(fHandle,"libusb_free_device_list");
	if (!psUsb->free_device_list)
	{
		printf("Failed to acquire libusb_free_device_list\n");
		goto err_out;
	}

	psUsb->get_device_descriptor = dlsym(fHandle,"libusb_get_device_descriptor");
	if (!psUsb->get_device_descriptor)
	{
		printf("Failed to acquire libusb_get_device_descriptor\n");
		goto err_out;
	}

	err = 0;

err_out:
	 return err;
}
