#ifndef _LCD_AP_H
#define _LCD_AP_H

//**************************************************************************
// Title	:   LCD-AP: home-brewed LCD routines
// Author:    Aiko Pras
//
//*****************************************************************************/
void init_lcd(void);

void write_lcd_char(unsigned char value);
void write_lcd_char2(unsigned char value);

void write_lcd_int(unsigned int value);
void write_lcd_int2(unsigned int value);

void write_lcd_string(const char *s);
void write_lcd_string1(const char *s);
void write_lcd_string2(const char *s);

void write_lcd_string_line(unsigned char line, const char *s);

#endif
