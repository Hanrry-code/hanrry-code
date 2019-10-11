#ifndef __MUSIC_H_
#define __MUSIC_H_
#include "hannan.h"
void music_play(void *pmusic_path);

void music_pause(void);
void music_continue(void);
void music_stop(void);
void music_exit(void);
void music_next(int mp3_numbers);
void music_prev(int mp3_numbers);
void cd_music(int sig, siginfo_t *info, void *arg);
#endif