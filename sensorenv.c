#include "sensorenv.h"

int initAsyncSensors(Vn200* vn200) 
{
	VN_ERROR_CODE errorCode;
	const char* const COM_PORT = "//dev//ttyUSB0";
	const int BAUD_RATE = 115200;

	errorCode = vn200_connect(vn200,COM_PORT,BAUD_RATE);
	
	//the struct VnDeviceCompositeData in vndevice.h contain all posible variables.

	/* Make sure the user has permission to use the COM port. */
	if (errorCode == VNERR_PERMISSION_DENIED) {

		printf("Current user does not have permission to open the COM port.\n");
		printf("Try running again using 'sudo'.\n");

		return -1;
	}
	else if (errorCode != VNERR_NO_ERROR)
	{
		printf("Error encountered when trying to connect to the sensor.\n");
		return -1;
	}
	
	/* Configure the VN-200 to output asynchronous data. */
	errorCode = vn200_setAsynchronousDataOutputType(vn200,VNASYNC_VNINS,true);

	/* Pause to ensure we have received the first asynchronous data record
	   from the sensor. */
	sleep(1);
	return 1;
}

