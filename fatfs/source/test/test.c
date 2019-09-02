#include <stdio.h>
#include <stdint.h>
#include "ff.h"
#include "test.h"

#define ERROR_PRINT(x)       if ((x)) { printf("error in %d\n", __LINE__); goto error; }

static int32_t create_file(const char *name) {
    FIL fil;

    if (f_open(&fil, name, FA_OPENALWAYS)) {
        return 1;
    }
    f_close(&fil); 
    return 0;
}

static int32_t create_folder(const char *name) {
    if (f_mkdir(name)) {
        return 1;
    }
    return 0;
}

static int32_t write_file(const char *name, const void *p, uint32_t len) {
    FIL fil;
    uint32_t bw;

    if (f_open(&fil, name, FA_WRITE)) {
        return 1;
    }
    if (f_write(&fil, p, len, &bw)) {
        f_close(&fil);
        return 1;
    }
    f_close(&fil);
    return 0;
}

static int32_t read_file(const char *name, void *p, uint32_t len) {
    FIL fil;
    uint32_t br;

    if (f_open(&fil, name, FA_READ)) {
        return 1;
    }
    if (f_read(&fil, p, len, &br)) {
        f_close(&fil);
        return 1;
    }
    f_close(&fil);
    return 0; 
}

static int32_t delete_folder(const char *name) {
    DIR dir;
    FILINFO fno;

    if (f_opendir(&dir, name)) {
        return 1;
    }

    for (i = 0; i < 100; i++) {
        if (f_readdir(&dir, &fno)) {
            goto error;
        }

        if (fno.
    }

    return 0;

error:
    f_closedir(&dir);
    return 1;
}

static int32_t delete_file(const char *name) {
    if (f_unlink(name)) {
        return 1;
    } 
    return 0; 
}

static int32_t is_file_exist(const char *name) {
    if (f_stat(name, NULL)) {
        return 1;
    }
    return 0;
}

int main(void) {
    uint32_t i;
    uint32_t max = 90;
    char name[100];
    char *rbuf;

    printf("start...\n");
    if ((rbuf = malloc(sizeof(testbuf))) == NULL) {
        ERROR_PRINT();
    }

    if (is_file_exist("/data") == 0) {
        if (create_folder("/data")) {
            ERROR_PRINT();
        }
    }
 
    for (i = 0; i < max; i++) {
        memset(name, 0, sizeof(name));
        snprintf(name, sizeof(name), "0:/data/%014d", i);
        if (create_folder(name)) {
            ERROR_PRINT();
        }
        snprintf(name, sizeof(name), "0:/data/%014d/CIM_ECG_PARM_WW.txt", i);
        if (create_folder(name)) {
            ERROR_PRINT();
        }   

        if (create_file(name)) {
            ERROR_PRINT();
        }

        if (write_file(name, testbuf)) {
            ERROR_PRINT();
        }

        if (read_file(name, rbuf)) {
            ERROR_PRINT();
        }

        if (verify_buf(testbuf, rbuf)) {
            ERROR_PRINT();
        }
    }

    free(rbuf);
    printf("OK\n");
    return 0;
int main(void) {
    uint32_t i;
    uint32_t max = 90;
    char name[100];
    char *rbuf;

    printf("start...\n");
    if ((rbuf = malloc(sizeof(testbuf))) == NULL) {
        ERROR_PRINT();
    }

    if (f_stat("/data", NULL)) {
        if (create_folder("/data")) {
            ERROR_PRINT();
        }
    }

    for (i = 0; i < max; i++) {
        memset(name, 0, sizeof(name));
        snprintf(name, sizeof(name), "0:/data/%014d", i);
        if (create_folder(name)) {
            ERROR_PRINT();
        }
        snprintf(name, sizeof(name), "0:/data/%014d/CIM_ECG_PARM_WW.txt", i);
        if (create_folder(name)) {
            ERROR_PRINT();
        }   

        if (create_file(name)) {
            ERROR_PRINT();
        }

        if (write_file(name, testbuf)) {
            ERROR_PRINT();
        }

        if (read_file(name, rbuf)) {
            ERROR_PRINT();
        }

        if (verify_buf(testbuf, rbuf)) {
            ERROR_PRINT();
        }
    }

    free(rbuf);
    printf("OK\n");
    return 0;

error:
    if (rbuf) {
        free(rbuf);
    }
    printf("failure\n");
    return 1; 
}

