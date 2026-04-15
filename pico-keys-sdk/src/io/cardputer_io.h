#ifndef CARDPUTER_IO_H
#define CARDPUTER_IO_H

#ifdef __cplusplus
extern "C" {
#endif

void init_cardputer_hw();
bool wait_for_keypress();
void show_message(char *message);

#ifdef __cplusplus
}
#endif

#endif