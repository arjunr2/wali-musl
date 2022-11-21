import re
import pandas as pd
import csv

BASIC_TYPES = ["int", "char", "long", "void", "..."]
COMPLEX_TYPES = ["off_t"]


def gen_syscall_list():
    input_file = "syscallnrs_x86_64.h"
    out_file = "syscall_list.txt"
    defs = []

    with open(input_file, "r") as f:
        pattern = re.compile(r"__NR_(\S*)");
        matches = [pattern.search(line) for line in f.readlines()]
        defs = [match.group(1) for match in matches if match is not None]
            
    with open(out_file, "w") as f:
        f.writelines([x+'\n' for x in defs])
    
    return defs



def main():
    out_file = "wali_syscall_defs.txt"
    defs = gen_syscall_list()
    
    format_file = "syscall_format.csv"
    df = pd.read_csv(format_file, skiprows=1, keep_default_na=False)
    df_dict = df.to_dict(orient='records')

    syscall_info = df_dict #[i for i in df_dict if i['# Args'] != ""]
    
    append_fn = lambda name, args: wali_defs.append("WALI_SYSCALL_DEF ({}, {});".format(name, ','.join(args)))
    gen_args = lambda x: [] if not x['# Args'] else [x["a"+str(i+1)] for i in range(int(x['# Args']))]

    wali_defs = []
    for item in syscall_info:
        args = gen_args(item)
        append_fn(item['Syscall'], args)
        for i in filter(None, item['Aliases'].split(',')):
            append_fn(i, args)


    with open(out_file, "w") as f:
        f.writelines('\n'.join(wali_defs))

    print(wali_defs)


if __name__ == '__main__':
    main()
