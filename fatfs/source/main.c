#include <stdio.h>
#include <string.h>
#include "ff.h"

#define FILE_NAME       "message.txt"
#define WRITE_TEXT      "hello fatfs 0123456789 +_<>"
#define WRITE_TEXT_LEN  strlen((WRITE_TEXT))

static FATFS FatFs;   /* Work area (filesystem object) for logical drive */

int main(void)
{
    FIL fil;
    char buffer[100];
    UINT br, bw;
    FRESULT res;
    BYTE work[FF_MAX_SS];

    if ((res = f_mkfs("0:/", FM_ANY, 0, work, sizeof(work))) != FR_OK) {
        printf("mkfs error! res=%d\n", res);
        return 1;
    }
    printf("mkfs successfully\n");

    if ((res = f_mount(&FatFs, "0:", 1)) != FR_OK) {
        printf("mount error! res=%d\n", res);
        return 1;
    }
    printf("mount successfully\n");

    if ((res = f_open(&fil, FILE_NAME, FA_WRITE | FA_CREATE_ALWAYS)) != FR_OK) {
        printf("open error! res=%d\n", res);
        return 1;
    }
    printf("open successfully\n");

    if ((res = f_write(&fil, WRITE_TEXT, WRITE_TEXT_LEN, &bw)) != FR_OK) {
        printf("write error! res=%d\n", res);
        return 1;
    }
    printf("write successfully, wrote: %s\n", WRITE_TEXT);

    f_close(&fil);

    if ((res = f_open(&fil, FILE_NAME, FA_READ)) != FR_OK) {
        printf("open error! res=%d\n", res);
        return 1;
    }
    printf("open successfully\n");

    if ((res = f_read(&fil, buffer, sizeof(buffer), &br)) != FR_OK || br == 0
        || br > sizeof(buffer)) {
        printf("read error! res=%d\n", res);
        return 1;
    }
    buffer[br] = 0;
    printf("read successfully, read: %s\n", buffer);

    if (strcmp(WRITE_TEXT, buffer)) {
        printf("the read buffer is not equal to write buffer\n");
        return 1;
    }

    f_close(&fil);

    return 0;
}

