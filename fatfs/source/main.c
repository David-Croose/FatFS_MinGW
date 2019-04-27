#include <stdio.h>
#include <string.h>
#include "ff.h"

static FATFS FatFs;   /* Work area (filesystem object) for logical drive */

int main(void)
{
    FIL fil;
    char buffer[100];
    UINT br, bw;
    FRESULT res;
    BYTE work[FF_MAX_SS];

    if (res = f_mkfs("0:", FM_ANY, 0, work, sizeof(work))) {
        printf("mkfs error! res=%d\n", res);
        return 1;
    }
    printf("mkfs successfully\n");

    if (res = f_mount(&FatFs, "0:", 1)) {
        printf("mount error! res=%d\n", res);
        return 1;
    }
    printf("mount successfully\n");

    if ((res = f_open(&fil, "message.txt", FA_WRITE | FA_CREATE_ALWAYS))) {
        printf("open error! res=%d\n", res);
        return 1;
    }
    printf("open successfully\n");

    if ((res = f_write(&fil, "hello fatfs", strlen("hello fatfs"), &bw))) {
        printf("write error! res=%d\n", res);
        return 1;
    }
    printf("write successfully, wrote: %s\n", "hello fatfs");

    f_close(&fil);

    if ((res = f_open(&fil, "message.txt", FA_READ))) {
        printf("open error! res=%d\n", res);
        return 1;
    }
    printf("open successfully\n");

    if ((res = f_read(&fil, buffer, sizeof(buffer), &br))) {
        printf("read error! res=%d\n", res);
        return 1;
    }
    printf("read successfully, read: %s\n", buffer);

    f_close(&fil);

    return 0;
}

