import re
import csv

BASIC_TYPES = ["int", "char", "long", "void", "..."]
COMPLEX_TYPES = ["off_t"]


def gen_syscall_list():
    input_file = "syscallnrs_x86_64.h"
    out_file = "syscall_defs.txt"
    defs = []

    with open(input_file, "r") as f:
        pattern = re.compile(r"__NR_(\S*)");
        matches = [pattern.search(line) for line in f.readlines()]
        defs = [match.group(1) for match in matches if match is not None]
            
    with open(out_file, "w") as f:
        f.writelines([x+'\n' for x in defs])
    
    return defs


def main():
    defs = gen_syscall_list()
    #with open(csv.DictReader

    #wali_defs = []
    #PL_VAL = 12345
    #append_fn = lambda names, args: [wali_defs.append("WALI_SYSCALL_DEF ({}, {});".format(name, ','.join(args))) for name in names]
    #
    #with open("wali_syscall_defs.txt", "w") as f:
    #    for x in defs:
    #        map_val = mapping.get(x, [PL_VAL, ()])
    #        args = map_val[1]

    #        append_fn([x], args)

    #        if len(map_val) == 3:
    #            append_fn(map_val[2], args)


    #    f.writelines('\n'.join(wali_defs))





if __name__ == '__main__':
    main()
