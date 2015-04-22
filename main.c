#include <stdio.h>
#include <unistd.h>
#include "vectornav.h"
#include "sensorenv.h"

/* Change the connection settings to your configuration. */
const char* const COM_PORT = "//dev//ttyUSB0";
const int BAUD_RATE = 115200;

int main()
{
	
	VN_ERROR_CODE errorCode;
	Vn200 vn200;
	int i;
	//initialize the sensor, return if not succeeded.
	if (initAsyncSensors(&vn200) == -1)
		return 0;
	
	//example
	for (i = 0; i < 10; i++) {

		VnDeviceCompositeData data;

		/* The library is handling and storing asynchronous data by itself.
		   Calling this function retrieves the most recently processed
		   asynchronous data packet. */
		vn200_getCurrentAsyncData(&vn200, &data);

		printf("INS Solution:\n"
			"  YPR.Yaw:                %+#7.2f\n"
			"  YPR.Pitch:              %+#7.2f\n"
			"  YPR.Roll:               %+#7.2f\n"
			"  LLA.Latitude:           %+#7.2f\n"
			"  LLA.Longitude:          %+#7.2f\n"
			"  LLA.Altitude:           %+#7.2f\n"
			"  Velocity.North:         %+#7.2f\n"
			"  Velocity.East:          %+#7.2f\n"
			"  Velocity.Down:          %+#7.2f\n",
			data.ypr.yaw,
			data.ypr.pitch,
			data.ypr.roll,
			data.latitudeLongitudeAltitude.c0,
			data.latitudeLongitudeAltitude.c1,
			data.latitudeLongitudeAltitude.c2,
			data.velocity.c0,
			data.velocity.c1,
			data.velocity.c2);

		printf("\n\n");

		sleep(1);
	}
	
	errorCode = vn200_disconnect(&vn200);
	
	if (errorCode != VNERR_NO_ERROR)
	{
		printf("Error encountered when trying to disconnect from the sensor.\n");
		
		return 0;
	}

	return BT_connect();
}
