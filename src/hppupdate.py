import re
from pathlib import Path

# --- Configuration ---
TARGET_DIRECTORY = '.'  # The folder to scan ('.' means current directory)
SOURCE_EXTENSIONS = {'.cpp', '.c', '.cc', '.cxx', '.hpp', '.h'} 

# --- Regex Patterns ---
# Matches: #include "file.h" or #include <file.h>
# Group 1: Everything up to the period (e.g., '#include "my_file')
# Group 2: The closing quote or bracket (e.g., '"' or '>')
INCLUDE_PATTERN = re.compile(r'(#include\s*[<"][^>"]+)\.h([>"])')

# ALTERNATIVE: If you want to replace .h literally everywhere (including strings like "config.h")
# Use this instead. It looks for .h preceded by a word character and followed by a word boundary.
GENERAL_PATTERN = re.compile(r'(?<=\w)\.h\b')

def update_includes(directory):
    dir_path = Path(directory)
    total_replacements = 0
    files_changed = 0

    print(f"Scanning for source files in '{dir_path.resolve()}'...")
    
    # rglob('*') recursively iterates through all files and folders
    for filepath in dir_path.rglob('*'):
        if filepath.is_file() and filepath.suffix in SOURCE_EXTENSIONS:
            try:
                with open(filepath, 'r', encoding='utf-8') as f:
                    content = f.read()
                
                # Perform the regex substitution
                # \g<1> refers to Group 1, \g<2> refers to Group 2
                new_content, num_subs = INCLUDE_PATTERN.subn(r'\g<1>.hpp\g<2>', content)
                
                # If changes were made, write them back to the file
                if num_subs > 0:
                    with open(filepath, 'w', encoding='utf-8') as f:
                        f.write(new_content)
                    print(f"[*] Updated {num_subs} instance(s) in: {filepath.name}")
                    total_replacements += num_subs
                    files_changed += 1
                    
            except UnicodeDecodeError:
                print(f"[!] Skipping {filepath.name} (Not valid UTF-8)")

    print(f"\nDone! Made {total_replacements} replacements across {files_changed} files.")

def rename_header_files(directory):
    dir_path = Path(directory)
    count = 0
    
    for filepath in dir_path.rglob('*.h'):
        new_filepath = filepath.with_suffix('.hpp')
        filepath.rename(new_filepath)
        print(f"[-] Renamed file: {filepath.name} -> {new_filepath.name}")
        count += 1
        
    print(f"Renamed {count} header files.")


if __name__ == '__main__':
    update_includes(TARGET_DIRECTORY)
    rename_header_files(TARGET_DIRECTORY)