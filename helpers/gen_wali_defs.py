import re
import pandas as pd
import csv

BASIC_TYPES = ["int", "char", "long", "void", "..."]
COMPLEX_TYPES = {
    "off_t": "long long",
    "size_t": "long", 
    "mode_t": "int",
    "nfds_t": "int",
    "socklen_t": "long",
    "uid_t": "int",
    "pid_t": "int",
    "gid_t": "int"
}

# long long in WASM is really a long in 64-bit machine
WASM_TO_NATIVE_SIZES = {
    "long long": "long"
}


def gen_syscall_list():
    input_file = "syscallnrs/x86-64.h"
    out_file = "syscall_list.txt"
    defs = []

    with open(input_file, "r") as f:
        pattern = re.compile(r"__NR_(\S*)");
        matches = [pattern.search(line) for line in f.readlines()]
        defs = [match.group(1) for match in matches if match is not None]
            
    with open(out_file, "w") as f:
        f.writelines([x+'\n' for x in defs])
    
    return defs


def gen_args(x):
    if not x['# Args']:
        return [], False

    args = [x["a"+str(i+1)] for i in range(int(x['# Args']))]
    arg_sub = []
    for arg in args:
        if arg[-1] == '*': 
            arg_sub.append(arg[:-1]+'*' if arg[:-1] in BASIC_TYPES else "void*")
        elif arg not in BASIC_TYPES:
            arg_sub.append(COMPLEX_TYPES.get(arg, "UNDEF"))
        else:
            arg_sub.append(arg)
    
    return arg_sub, True


def main():
    out_file = "wali_syscall_defs.txt"
    out_case_file = "wali_case_defs.txt"
    out_declr_file = "wali_syscall_declr.txt"

    defs = gen_syscall_list()
    
    format_file = "syscall_format.csv"
    df = pd.read_csv(format_file, skiprows=1, keep_default_na=False)
    df_dict = df.to_dict(orient='records')

    syscall_info = df_dict
    
    append_def_fn = lambda name, args: wali_defs.append(f"WALI_SYSCALL_DEF ({name}, {','.join(args)});")
    append_case_fn = lambda name, fn_name, args: \
        case_list.append("\t\tCASE_SYSCALL ({name}, {fn_name}, {arglist});".format(
                            name = name, 
                            fn_name = fn_name, 
                            arglist = ','.join(['({})a{}'.format(j, i+1) \
                                if j != '...' else 'a{}'.format(i+1) for i, j in enumerate(args)])))


    append_declr_fn = lambda fn_name, args: \
        declr_list.append("long wali_syscall_{fn_name} (wasm_exec_env_t exec_env{arglist});".format(
            fn_name = fn_name,
            arglist = ''.join([', long a{}'.format(i+1) for i, j in enumerate(args)])))

    wali_defs = []
    case_list = []
    declr_list = []

    for item in syscall_info:
        args, valid = gen_args(item)
        print("{}: {}".format(item['Syscall'], args))
        
        fn_name = item['Aliases'] if item['Aliases'] else item['Syscall']

        append_def_fn(fn_name, args)
        append_declr_fn(fn_name, args)

        if valid:
            append_case_fn(item['Syscall'], fn_name, args)


    with open(out_file, "w") as f:
        f.writelines('\n'.join(wali_defs))

    with open(out_case_file, "w") as f:
        f.writelines('\n'.join(case_list))

    with open(out_declr_file, "w") as f:
        f.writelines('\n'.join(declr_list))

if __name__ == '__main__':
    main()
