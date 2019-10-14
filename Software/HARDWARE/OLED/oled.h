#ifndef __OLED_H
#define __OLED_H

void oled_initDev(void);
void oled_const_display(void);
void oled_update_display(u16 *data);
void oled_clear_diplay(void);

#endif
