#ifndef __EXECUTE_H__
#define __EXECUTE_H__

extern unsigned short
        pc
      , start
      , endd
      , sp
      , mp
      , t
      , u
      , ff
      , ff_
      , fa
      , fa_
      , fb
      , fb_
      , fr
      , fr_
      , romp
      ;
extern unsigned long long
        st
      , sttap
      , stint
      , counter
      ;
extern unsigned char
        a
      , c
      , b
      , e
      , d
      , l
      , h
      , a_
      , c_
      , b_
      , e_
      , d_
      , l_
      , h_
      , xl
      , xh
      , yl
      , yh
      , i
      , r
      , rs
      , prefix
      , iff
      , im
      , w
      , halted
      ;

extern unsigned int
        v
      , intr
      , tap
      ;

extern unsigned char *mem;

extern void execute(void);

#endif