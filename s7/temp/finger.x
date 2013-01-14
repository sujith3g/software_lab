struct finger_out{
	char message[1024];
};
program FINGER
{
	version FINGER_VERSION
	{
		finger_out MyFinger() = 1;
	} = 1;
} = 0x21230000;

