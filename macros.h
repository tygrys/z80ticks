#ifndef __MACROS_H__
#define __MACROS_H__

#define RET(n)                   \
          st += n,               \
          mp = mem[sp++],        \
          pc = mp |= mem[sp++]<<8

#define LDRIM(r)                 \
          st += 7,               \
          r = mem[pc++]

#define LDRRIM(a, b)             \
          st += 10,              \
          b = mem[pc++],         \
          a = mem[pc++]

#define LDRP(a, b, r)            \
          st += 7,               \
          r = mem[mp = b|a<<8],  \
          ++mp

#define LDRPI(a, b, r)          \
          st += 15,             \
          r = mem[((mem[pc++]^128)-128+(b|a<<8))&65535]

#define LDPR(a, b, r)               \
          st += 7,                  \
          t = b|a<<8,               \
          t >= romp && (mem[t]=r), \
          mp = ((b+1)&255) | a<<8

#define LDPRI(a, b, r)           \
          st += 15,              \
          t = ((mem[pc++]^128)-128+(b|a<<8))&65535, \
          t >= romp && (mem[t]= r)

#define LDRR(a, b, n)            \
          st += n,               \
          a = b

#define LDPNNRR(a, b, n)            \
          st += n,                  \
          t = mem[pc++],            \
          t|= mem[pc++]<<8,         \
          mp = t+1,                 \
          t >= romp && (mem[t]= b), \
          mp >= romp && (mem[mp]= a)

#define LDPIN(a, b)              \
          st += 15,              \
          t = mem[pc++],         \
          t = ((t^128)-128+(b|a<<8))&65535, \
          t >= romp && (mem[t]= mem[pc]), \
          pc++

#define INCW(a, b)               \
          st += 6,               \
          ++b || a++

#define DECW(a, b)               \
          st += 6,               \
          b-- || a--

#define INC(r)                   \
          st += 4,               \
          ff = (ff&256)          \
            | (fr = r = (fa = r)+(fb = 1))

#define DEC(r)                   \
          st += 4,               \
          ff = (ff&256)          \
            | (fr = r = (fa = r)+(fb = -1))

#define INCPI(a, b)              \
          st += 19,              \
          fa = mem[t = (mem[pc++]^128)-128+(b|a<<8)], \
          ff = (ff&256)          \
            | (fr = fa+((fb = 1)&255)), \
          t >= romp && (mem[t]= fr)

#define DECPI(a, b)              \
          st += 19,              \
          fa = mem[t = (mem[pc++]^128)-128+(b|a<<8)], \
          ff = (ff&256)          \
            | (fr = fa+((fb = -1)&255)), \
          t >= romp && (mem[t]= fr)

#define ADDRRRR(a, b, c, d)        \
          st += 11,                \
          v= b+d+                  \
            ((a+c) << 8),          \
          ff = (ff & 128)          \
            | ((v>>8) & 296),      \
          fb = (fb&128)            \
            | (((v>>8)^a^c^fr^fa)&16), \
          mp = b+1+(a<<8),         \
          a = v>>8,                \
          b = v

#define JRCI(c)                  \
          if (c)                 \
            st += 12,            \
            pc += (mem[pc]^128)-127; \
          else                   \
            st += 7,             \
            pc++

#define JRC(c)                   \
          if (c)                 \
            st += 7,             \
            pc++;                \
          else                   \
            st += 12,            \
            pc += (mem[pc]^128)-127

#define LDRRPNN(a, b, n)         \
          st += n,               \
          t = mem[pc++],         \
          b = mem[t|= mem[pc++]<<8], \
          a = mem[mp = t+1]

#define ADDISP(a, b)             \
          st += 11,              \
          v= sp+(b|a<<8),        \
          ff = (ff&128)          \
            | ((v>>8)&296),      \
          fb = (fb&128)          \
            | (((v>>8)^(sp>>8)^a^fr^fa)&16), \
          mp = b+1+(a<<8),       \
          a = v>>8,              \
          b = v

#define ADD(b, n)                \
          st += n,               \
          fr = a = (ff = (fa = a)+(fb = b))

#define ADC(b, n)                \
          st += n,               \
          fr = a = (ff = (fa = a)+(fb = b)+(ff>>8&1))

#define SUB(b, n)                \
          st += n,               \
          fr = a = (ff = (fa = a)+(fb = ~b)+1)

#define SBC(b, n)                \
          st += n,               \
          fr = a = (ff = (fa = a)+(fb = ~b)+(((ff>>8)&1)^1))

#define AND(b, n)                \
          st += n,               \
          fa = ~(a = ff = fr = (a&b)),\
          fb = 0

#define XOR(b, n)                \
          st += n,               \
          fa = 256               \
            | (ff = fr = a^= b), \
          fb = 0

#define OR(b, n)                 \
          st += n,               \
          fa = 256               \
            | (ff = fr = a |= b),  \
          fb = 0

#define CP(b, n)                 \
          st += n,               \
          fr = (fa = a)-b,       \
          fb = ~b,               \
          ff = (fr & -41)        \
            | (b & 40),          \
          fr &= 255

#define RETC(c)                  \
          if (c)                 \
            st += 5;             \
          else                   \
            st += 11,            \
            mp = mem[sp++],      \
            pc = mp|= mem[sp++]<<8

#define RETCI(c)                 \
          if (c)                 \
            st += 11,            \
            mp = mem[sp++],      \
            pc = mp|= mem[sp++]<<8;\
          else                  \
            st += 5

#define PUSH(a, b)               \
          st += 11,              \
          --sp >= romp && (mem[sp]= a), \
          --sp >= romp && (mem[sp]= b)

#define POP(a, b)                \
          st += 10,              \
          b = mem[sp++],         \
          a = mem[sp++]

#define JPC(c)                   \
          st += 10;              \
          if (c)                 \
            pc += 2;             \
          else                   \
            pc = mem[pc] | mem[pc+1]<<8

#define JPCI(c)                  \
          st += 10;              \
          if (c)                 \
            pc = mem[pc] | mem[pc+1]<<8; \
          else                  \
            pc += 2

#define CALLC(c)                 \
          if (c)                 \
            st += 10,            \
            pc += 2;             \
          else                   \
            st += 17,            \
            t = pc+2,            \
            mp = pc = mem[pc] | mem[pc+1]<<8, \
            --sp >= romp && (mem[sp]= t>>8), \
            --sp >= romp && (mem[sp]= t)

#define CALLCI(c)                \
          if (c)                 \
            st += 17,            \
            t = pc+2,            \
            mp = pc = mem[pc] | mem[pc+1]<<8, \
            --sp >= romp && (mem[sp]= t>>8), \
            --sp >= romp && (mem[sp]= t); \
          else                   \
            st += 10,            \
            pc += 2

#define RST(n)                   \
          st += 11,              \
          --sp >= romp && (mem[sp]= pc>>8), \
          --sp >= romp && (mem[sp]= pc), \
          mp = pc = n

#define EXSPI(a, b)              \
          st += 19,              \
          t = mem[sp],           \
          sp >= romp && (mem[sp]= b), \
          b = t,                 \
          t = mem[sp+1],           \
          sp+1>= romp && (mem[sp+1]= a), \
          a = t,                 \
          mp = b | a<<8

#define RLC(r)                   \
          st += 8,               \
          ff = (r*257)>>7,       \
          fa = 256               \
            | (fr = r = ff),     \
          fb = 0

#define RRC(r)                    \
          st += 8,                \
          ff =  (r >> 1)          \
              | ((((r&1)+1) ^ 1)<<7), \
          fa = 256                \
            | (fr = r = ff),      \
          fb = 0

#define RL(r)                    \
          st += 8,               \
          ff = (r << 1)            \
            | ((ff >> 8) & 1),       \
          fa = 256               \
            | (fr = r = ff),     \
          fb = 0

#define RR(r)                    \
          st += 8,                \
          ff = ((r*513) | (ff&256))>>1, \
          fa = 256               \
            | (fr = r = ff),     \
          fb = 0

#define SLA(r)                   \
          st += 8,               \
          ff = r<<1,             \
          fa = 256               \
            | (fr = r = ff),     \
          fb = 0

#define SRA(r)                   \
          st += 8,               \
          ff = (((r*513)+128)^128)>>1, \
          fa = 256               \
            | (fr = r = ff),     \
          fb = 0

#define SLL(r)                   \
          st += 8,               \
          ff = (r<<1) | 1,         \
          fa = 256               \
            | (fr = r = ff),     \
          fb = 0

#define SRL(r)                   \
          st += 8,               \
          ff = (r*513) >> 1,       \
          fa = 256               \
            | (fr = r = ff),     \
          fb = 0

#define BIT(n, r)                \
          st += 8,               \
          ff = (ff  & -256)      \
            | (r & 40)           \
            | (fr = r & n),      \
          fa = ~fr,              \
          fb = 0

#define BITHL(n)                 \
          st += 12,              \
          t = mem[l | h<<8],     \
          ff = (ff & -256)       \
            | ((mp>>8) & 40)     \
            | (-41 & (t &= n)),  \
          fa = ~(fr = t),        \
          fb = 0

#define BITI(n)                  \
          st += 5,               \
          ff = (ff & -256)       \
            | ((mp>>8) & 40)     \
            | (-41 & (w &= n)),   \
          fa = ~(fr = w),        \
          fb = 0

#define RES(n, r)                \
          st += 8,               \
          r&= n

#define RESHL(n)                 \
          st += 15,              \
          w= mem[t = l|h<<8] & n,\
          t >= romp && (mem[t] = w)

#define SET(n, r)                \
          st += 8,               \
          r|= n

#define SETHL(n)                 \
          st += 15,              \
          w= mem[t = l|h<<8] | n,\
          t >= romp && (mem[t] = w)

#define INR(r)                    \
          st += 12,               \
          r = in(mp = b<<8 | c),  \
          ++mp,                   \
          ff = (ff & -256)        \
            | (fr = r),           \
          fa = r | 256,           \
          fb = 0

#define OUTR(r)                   \
          st += 12,               \
          out(mp = c | (b<<8), r),  \
          ++mp

#define SBCHLRR(a, b)            \
          st += 15,              \
          v= l-b+(h-(a<<8))-((ff>>8)&1),\
          mp = l+1+(h<<8),       \
          ff = v>>8,             \
          fa = h,                \
          fb = ~a,               \
          h = ff,                \
          l = v,                 \
          fr = h|l<<8

#define ADCHLRR(a, b)            \
          st += 15,              \
          v= l+b+(h+(a<<8))+((ff>>8)&1),\
          mp = l+1+(h<<8),       \
          ff = v>>8,             \
          fa = h,                \
          fb = a,                \
          h = ff,                \
          l = v,                 \
          fr = h|(l<<8)

#endif