#!/usr/bin/env python3
"""Python Template for CS4238 Assignment3
    Usage: A3.py <pe_file>
    Dependency:  python3, pefile, requests(optional) [May require installing them on your computer]
"""

# Import Python Utils
import os.path
import sys

# Import Pefile related pacakges
import pefile
import peutils

def get_file_type(pe):
    # Example function
    if pe.is_exe():
        return "PE"
    if pe.is_dll():
        return "DLL"
    if pe.is_driver():
        return "SYS"
    return "UNKNOWN"

def count_dlls(pe):
    return len(pe.DIRECTORY_ENTRY_IMPORT)

def count_fns(pe):
    x = 0
    for entry in pe.DIRECTORY_ENTRY_IMPORT:
        for fn in entry.imports:
            x += 1
    return x

def get_compile_time(pe):
    return pe.FILE_HEADER.dump_dict()["TimeDateStamp"]["Value"]


def get_entry_point_section_name(pe):
    valid_sections = [".text",".code","CODE","INIT"]
    entry = pe.OPTIONAL_HEADER.AddressOfEntryPoint
    for section in pe.sections:
        section_name = section.Name.decode().rstrip('\x00')
        if section_name in valid_sections:
            if section.contains_rva(entry):
                return section_name
    return ""

def signature_match(pe, PEiD_database):

    matches = []
    signatures = peutils.SignatureDatabase(data=PEiD_database)
    matches = signatures.match(pe)
    return matches

def get_entropy(section):
    section_name = section.Name.decode().rstrip('\x00')

    entropy = section.get_entropy()
    suspect_packed = entropy >= 6

    print("\t ", section_name, ": {:.2f}".format(entropy), end=" ")
    if suspect_packed:
        print("(Packed?)")
    else:
        print()
    return


def verify_checksum(pe):
    return pe.verify_checksum()


def get_database():
    # Here we use requests package. 
    # If you prefer offline access, just rewrite this function.
    import requests
    database = 'https://raw.githubusercontent.com/cuckoosandbox/cuckoo/master/cuckoo/private/peutils/UserDB.TXT'
    request = requests.get(database, allow_redirects = True)
    return request.text


def main():
    # 0. Print you Matrix ID and name
    student_id = "A0216695U"
    student_name = "Edward Ng"
    print("Assignment 3:", student_id, student_name)


    print("[1]\tAnalysing file", os.sys.argv[1])
    pe = pefile.PE(os.sys.argv[1])

    # 1. Output the following to standard output:
    #   a. Identify the file type as DLL or EXE or SYS regardless of the file’s extension.
    print("[2.a]\tFile type:", get_file_type(pe))
    #   b. Total number of imported DLLs.
    print("[2.b]\t#DLLs:", count_dlls(pe))
    #   c. Total number of imported functions.
    print("[2.b]\t#FNs:", count_fns(pe))

    #   d. Output the compile time.
    print("[3]\tCompile Time:", get_compile_time(pe))

    # 2. Alert the user if the entry point of the code is not in a section with 
    #    the name “.text”, “.code”, “CODE”, or “INIT”.
    section_name = get_entry_point_section_name(pe)
    if not section_name:
        print("[4]\tEntry point not found in valid sections.")
    else:
        print("[4]\tEntry point found in", section_name)

    # 3. Automatically use the PEiD database that comes with pefile to identify 
    #    packers. Confirm that this works with UPX. Output the detection to standard output.
    PEiD_database = get_database()
    print("[5]\tPacker detected:", signature_match(pe, PEiD_database))

    # 4. Calculate and output the entropy for each section. Alert the user when you 
    #    suspect that a section maybe packed or compressed.
    print("[6]\tEntropy for sections...")
    for section in pe.sections:
        get_entropy(section)
    
    

    # 5. Compare the PE Optional Header checksum with the actual checksum. Alert the user
    #    when they don’t match up.
    print("[8]\tChecksum matched:", verify_checksum(pe))


    # End of script. Well done!
    return


if __name__ == "__main__":
    main()