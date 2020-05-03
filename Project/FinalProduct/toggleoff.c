#include "unistd.h"

#define PATH_TO_BLUETOOTH_SERVICE "/etc/init.d/bluetooth"
#define STOP_CMD "stop"

int main(void)
{
    execl(PATH_TO_BLUETOOTH_SERVICE, PATH_TO_BLUETOOTH_SERVICE, STOP_CMD, NULL);
    return 0;
}