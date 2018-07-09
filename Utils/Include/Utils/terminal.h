#ifndef KSES_UTILITIES_TERMINAL_H_
#define KSES_UTILITIES_TERMINAL_H_
#include <stdint.h>
#ifdef __cplusplus
extern "C"
{
#endif

void terminal_run(void);
void terminal_handleByte(uint8_t byte);
#ifdef __cplusplus
}
#endif
#endif /* KSES_UTILITIES_TERMINAL_H_ */
