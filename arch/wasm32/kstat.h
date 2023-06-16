/* This is the x86-64 kstat struct
* Aarch64/Riscv64 requires explicit conversion in
* WALI syscall interface
*   blksize_t = long (x86-64), int (aarch64, riscv64) 
*   nlink_t = long (x86-64), int (aarch64, riscv64) */

struct __attribute__((packed)) kstat {
	dev_t st_dev;
	ino_t st_ino;
	nlink_t st_nlink;

	mode_t st_mode;
	uid_t st_uid;
	gid_t st_gid;
	unsigned int    __pad0;
	dev_t st_rdev;
	off_t st_size;
	blksize_t st_blksize;
	blkcnt_t st_blocks;

	long st_atime_sec;
	long st_atime_nsec;
	long st_mtime_sec;
	long st_mtime_nsec;
	long st_ctime_sec;
	long st_ctime_nsec;
	long __unused[3];
};