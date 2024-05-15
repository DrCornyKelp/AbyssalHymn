'''
The purpose of this function is to
rename every file in an animation folder
to suit the cpp decoration animation directory
'''

import os

directory_path = 'Menu/Background/'

def convert(number, max_number):
    num_digits = len(str(max_number))
    return str(number).zfill(num_digits)

def rename_files(directory):
    files = os.listdir(directory)

    f_len = len(files)
    f = 0
    for filename in files:
        os.rename(f"{directory}{filename}", f"{directory}frame_{convert(f, f_len)}.png")
        f += 1

rename_files(directory_path)