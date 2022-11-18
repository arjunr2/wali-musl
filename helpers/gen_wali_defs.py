import re

def main():
    input_file = open("syscallnrs_x86_64.h", "r").readlines()
    
    pattern = re.compile(r"__NR_(\S*)");

    defs = []
    with open("syscall_defs.txt", "w") as g:
        for line in input_file:
            match = pattern.search(line)
            if match:
                defs.append(match.group(1))
        g.writelines([x+'\n' for x in defs])


    wali_defs = []
    PL_VAL = 12345
    append_fn = lambda names, args: [wali_defs.append("WALI_SYSCALL_DEF ({}, {});".format(name, ','.join(args))) for name in names]
    
    with open("wali_syscall_defs.txt", "w") as f:
        for x in defs:
            map_val = mapping.get(x, [PL_VAL, ()])
            args = map_val[1]

            append_fn([x], args)

            if len(map_val) == 3:
                append_fn(map_val[2], args)


        f.writelines('\n'.join(wali_defs))


INT="int"
_CHAR="char*"
SIZE_T="long"
_VOID="void*"
LONG="long"
VAR="..."

mapping = {
    "read"      :   [0, (INT,    _VOID,  SIZE_T )],
    "write"     :   [1, (INT,    _VOID,  SIZE_T )],
    "open"      :   [2, (_CHAR,  INT,    INT    )],
    "close"     :   [3, (INT,                   )],
    "stat"      :   [4, (_CHAR,  _VOID          )],
    "fstat"     :   [5, (INT,    _VOID          )],
    "lstat"     :   [6, (_CHAR,  _VOID          )],
    "poll"      :   [7, (_VOID,  INT,    LONG   )],
    "lseek"     :   [8, (INT,    LONG,   INT    )],
    "mmap"      :   [9, (_VOID,   LONG,   LONG,   LONG,   LONG,   LONG)],

    "mprotect"  :   [10,    (LONG,   SIZE_T, LONG)],
    "rt_sigprocmask"    :   [14,    (INT,    _VOID,  _VOID,  SIZE_T)],

    "fcntl"     :   [72,    (INT, INT, VAR)],

    # Mode_t check
    "fchmodat"  :   [268,   (INT,    _CHAR,  INT,   INT)],
    "newfstatat":   [262,   (INT,    _CHAR,  _VOID,  INT),  ("fstatat",)],
    "futex"     :   [202,   ("volatile "+_VOID, INT,    VAR)],

    "fadvise64" :   [221,   (INT,    LONG,   SIZE_T, INT),  ("fadvise",)]

}

if __name__ == '__main__':
    main()
