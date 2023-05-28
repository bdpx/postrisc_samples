#include <unistd.h>
#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <sys/syscall.h>

#include "doomkeys.h"
#include "doomgeneric.h"
#include "i_video.h"

#define KEYQUEUE_SIZE 16

#define SYS_doom_Init            2001
#define SYS_doom_DrawFrame       2002
#define SYS_doom_SleepMs         2003
#define SYS_doom_GetTicksMs      2004
#define SYS_doom_GetKey          2005
#define SYS_doom_SetWindowTitle  2006

#undef syscall

extern uint64_t __syscall_postrisc(int n, uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e, uint64_t f);

void DG_Init(void)
{
    // printf("DG_Init\n");
    __syscall_postrisc(SYS_doom_Init, DOOMGENERIC_RESX, DOOMGENERIC_RESY, 0L, 0L, 0L, 0L);
}

void DG_DrawFrame(void)
{
    __syscall_postrisc(SYS_doom_DrawFrame, (uint64_t)I_VideoBuffer, SCREENWIDTH, SCREENHEIGHT, (uint64_t)colors, 0L, 0L);

    // __syscall_postrisc(SYS_doom_DrawFrame, (uint64_t)DG_ScreenBuffer, DOOMGENERIC_RESX, DOOMGENERIC_RESY, 0L, 0L, 0L);
    //printf("DG_DrawFrame\n");
    //struct timespec spec = { .tv_sec = 0, .tv_nsec = 10000000U };
    //nanosleep(&spec, &spec);
}

void DG_SleepMs(uint32_t ms)
{
    __syscall_postrisc(SYS_doom_SleepMs, (uint64_t)ms, 0L, 0L, 0L, 0L, 0L);
    //printf("DG_SleepMs: %u ms\n", (unsigned)ms);
    //struct timespec spec = { .tv_sec = 0, .tv_nsec = 100000U * ms };
    //nanosleep(&spec, &spec);
}

void print_current_time_with_ms (void)
{
}

uint32_t DG_GetTicksMs(void)
{
    return __syscall_postrisc(SYS_doom_GetTicksMs, 0L, 0L, 0L, 0L, 0L, 0L);
/*
    long            ms; // Milliseconds
    time_t          s;  // Seconds
    struct timespec spec;

    clock_gettime(CLOCK_REALTIME, &spec);
    printf("DG_GetTicksMs time: %lu.%03lu seconds\n", spec.tv_sec, spec.tv_nsec / 1000000);
    return spec.tv_sec * 1000 + spec.tv_nsec / 1000000;
*/
}

int DG_GetKey(int* pressed, unsigned char* doomKey)
{
    return __syscall_postrisc(SYS_doom_GetKey, (uint64_t)pressed, (uint64_t)doomKey, 0L, 0L, 0L, 0L);
    //printf("DG_GetKey\n");
    //key queue is empty
    //return 0;
}

void DG_SetWindowTitle(const char * title)
{
    __syscall_postrisc(SYS_doom_SetWindowTitle, (uint64_t)title, 0L, 0L, 0L, 0L, 0L);
    // printf("DG_SetWindowTitle %s\n", title);
}

int main(int argc, char **argv)
{
    // printf("main called\n");
    doomgeneric_Create(argc, argv);

    for (volatile long i=0; i < 2000000000L; i++) {
        doomgeneric_Tick();
    }
    // printf("main exited\n");
    return 0;
}
