import re

def main():
    input_file = open("syscallnrs.h", "r").readlines()
    
    pattern = re.compile(r"__NR_(\S*)");

    defs = []
    with open("wali_syscall_defs.txt", "w") as f:
        for line in input_file:
            match = pattern.search(line)
            if match:
                defs.append(match.group(1))

        f.writelines(["WALI_SYSCALL_DEF ({});\n".format(x) for x in defs])

if __name__ == '__main__':
    main()
