#ifndef __OLED_H
#define __OLED_H

static void oled_init(void);
void oled_const_display(void);
void oled_update_display(u16 *data);
void oled_poweron_display(void);
void oled_clear_diplay(void);
void oled_para_unset_display(void);


#endif
