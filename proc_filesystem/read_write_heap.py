#!/usr/bin/python3
"""
Python - /proc filesystem - task 0. Hack the VM

    Searches the heap of a process for a given string and replaces it with
another.
"""

from sys import argv


def read_write_heap(pid, get_str, give_str):
    """
    Search the heap from `pid` for `get_str` and replace
    it with `give_str`.

    Args:
        pid (int): process id of currently ongoing process' heap to search
        get_str (str): string to search for in heap
        give_str (str): string to replace `read_str` with
    """

    flag = False
    try:
        num_pid = int(pid)
    except (TypeError, ValueError):
        flag = True
    if num_pid < 0:
        flag = True

    if flag:
        print("Bad or missing PID")
        print("Usage: read_write_heap(pid, get_str, give_str)")
        exit(1)

    if type(get_str) != str or get_str == "":
        print("Bad or missing string to find")
        print("Usage: read_write_heap(pid, get_str, give_str)")
        exit(1)

    if type(give_str) != str:
        print("Missing string to insert")
        print("Usage: read_write_heap(pid, get_str, give_str)")
        exit(1)

    try:
        map_file = open("/proc/{}/maps".format(pid), 'r')
    except OSError as error:
        print("Can't open file /proc/{}/maps: OSError: {}".format(pid, error))
        exit(1)
    print("[*] maps: /proc/{}/maps".format(pid))
    print("[*] mem: /proc/{}/mem".format(pid))

    current_heap = None
    for line in map_file:
        if "heap" in line:
            current_heap = line.split()
    map_file.close()

    if current_heap is None:
        print("No heap found!")
        exit(1)
    else:
        print('\n'.join(("[*] Found: {}:".format(current_heap[-1]),
                         "\tpathname = {}".format(current_heap[-1]),
                         "\taddress range = {}".format(current_heap[0]),
                         "\tpermissions = {}".format(current_heap[1]),
                         "\toffset (in bytes) = {}".format(current_heap[2]),
                         "\tinode = {}".format(current_heap[4]))))

    addr_locate = current_heap[0].split('-')
    print(
        "[*] Addresses start [{}] | end [{}]".format(
            addr_locate[0].lstrip('0'), 
            addr_locate[1].lstrip('0')
        )
    )

    perms = current_heap[1]
    if 'r' not in perms:
        print("Heap does not have read permission")
        exit(0)
    if 'w' not in perms:
        print("Heap does not have write permission")
        exit(0)

    try:
        mem = open("/proc/{}/mem".format(pid), 'rb+')
    except OSError as error:
        print("Can't open file /proc/{}/maps: OSError: {}".format(pid, error))
        exit(1)

    heap_start = int(addr_locate[0], 16)
    heap_end = int(addr_locate[1], 16)
    mem.seek(heap_start)
    heap = mem.read(heap_end - heap_start)
    str_offset = heap.find(bytes(get_str, "ASCII"))
    if str_offset == -1:
        print("Can't find {} in /proc/{}/mem".format(get_str, pid))
        exit(1)
    else:
        print("[*] Found '{}' at {}".format(get_str, hex(str_offset)[2:]))

    mem.seek(heap_start + str_offset)
    mem.write(bytes(give_str + '\0', "ASCII"))
    print("[*] Writing '{}' at {}".format(give_str,
                                          hex(heap_start + str_offset)[2:]))


if __name__ == "__main__":

    if (len(argv) != 4):
        print("Usage: {} <pid> <string to read> "
              "<string to write>".format(argv[0]))
        exit(1)
    else:
        pid = argv[1]
        target_str = argv[2]
        new_str = argv[3]
        read_write_heap(pid, target_str, new_str)
