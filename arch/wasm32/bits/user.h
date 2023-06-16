/* Non-portable across architectures
* No support for procfs yet */
#undef __WORDSIZE
#define __WORDSIZE 64

#define PAGE_MASK   (~(PAGESIZE-1))
#define NBPG        PAGESIZE
#define UPAGES      1
