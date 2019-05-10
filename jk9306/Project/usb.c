#define  __INCLUDE_FROM_USB_DRIVER
#define  __INCLUDE_FROM_USB_CONTROLLER_C
#include <USBController.h>

void USB_Init(uint8_t corenum, uint8_t mode)
{
#if defined(USB_CAN_BE_HOST)	
	if (mode == USB_MODE_Host && Mem_IsInitialized == false)
	{
	  USB_Memory_Init(USBRAM_BUFFER_SIZE);
		Mem_IsInitialized = true;
	}
#endif
	USB_CurrentMode[corenum] = mode;
	HAL_USBInit(corenum);
	USB_ResetInterface(corenum, mode);
	USB_IsInitialized = true;
}