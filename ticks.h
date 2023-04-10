#ifndef __TICKS_H__
#define __TICKS_H__

extern long tapcycles(void);

extern int in(int port);

extern void out(int port, int value);

extern int f(void);

extern void setf(int a);

#endif