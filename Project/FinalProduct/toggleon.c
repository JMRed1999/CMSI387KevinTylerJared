#include "unistd.h"

#define PATH_TO_BLUETOOTH_SERVICE "/etc/init.d/bluetooth"
#define START_CMD "start"

int main(void)
{
    execl(PATH_TO_BLUETOOTH_SERVICE, PATH_TO_BLUETOOTH_SERVICE, START_CMD, NULL);
    return 0;
}