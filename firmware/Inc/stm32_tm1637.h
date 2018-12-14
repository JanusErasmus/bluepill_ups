#ifndef _STM32_TM1637
#define _STM32_TM1637

#ifdef __cplusplus
 extern "C" {
#endif

void tm1637Init(void);
void tm1637DisplayDecimal(int v, int displaySeparator);
void tm1637SetBrightness(char brightness);
#ifdef __cplusplus
 }
#endif
#endif //_STM32_TM1637
