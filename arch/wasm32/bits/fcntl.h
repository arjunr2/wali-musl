/* Virtualize fcntl flags across architectures: mainly differs for aarch64
* x86_64, aarch64, riscv64 
* Runtime maps to true flags 
* Used by syscalls:
*   fcntl
*   open
*   openat
*   pipe2
* Not supported:
*   dup3
*   mq_open
*   signalfd
*   */

/* These map commonly */
#define O_CREAT        0100 // 6
#define O_EXCL         0200 // 7
#define O_NOCTTY       0400 // 8
#define O_TRUNC       01000 // 9
#define O_APPEND      02000 // 10
#define O_NONBLOCK    04000 // 11
#define O_DSYNC      010000 // 12
#define O_SYNC     04010000 // 12 | 21 
#define O_RSYNC    04010000 // 12 | 21

#define O_CLOEXEC  02000000 // 20

#define O_ASYNC      020000 // 13
#define O_NOATIME  01000000 // 19
#define O_PATH    010000000 // 22
#define O_NDELAY O_NONBLOCK // 11

/* These are arch-specific */
/* Aarch64 swaps O_DIRECTORY <-> O_DIRECT 
*           and  O_NOFOLLOW <-> O_LARGEFILE
* O_TMPFILE only differs because O_DIRECTORY flags also set
* If WALI handles this correctly, no changes need to be made to it
* Check these in the WALI runtime implementation to adjust accordingly
* */
#define O_DIRECTORY 0200000
#define O_NOFOLLOW  0400000

#define O_DIRECT     040000
#define O_LARGEFILE 0100000
#define O_TMPFILE 020200000
/* */

/* These are all common across archs */
#define F_DUPFD  0
#define F_GETFD  1
#define F_SETFD  2
#define F_GETFL  3
#define F_SETFL  4
#define F_GETLK 5
#define F_SETLK 6
#define F_SETLKW 7
#define F_SETOWN 8
#define F_GETOWN 9
#define F_SETSIG 10
#define F_GETSIG 11

#define F_SETOWN_EX 15
#define F_GETOWN_EX 16

#define F_GETOWNER_UIDS 17
