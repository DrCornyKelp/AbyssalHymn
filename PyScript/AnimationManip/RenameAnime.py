'''
The purpose of this function is to
rename every file in an animation folder
to suit the cpp decoration animation directory
'''

import os

directory_path = 'Decoration/City/'
old_part_1 = "ezgif-frame-"
old_part_2 = "";

def convert(number, max_number):
    num_digits = len(str(max_number))
    return str(number).zfill(num_digits)

def rename_files(directory):
    files = os.listdir(directory)

    f_len = len(files)
    for f in range(f_len):
        os.rename(  directory + old_part_1 + convert(f, f_len) + old_part_2 + ".png",
                    directory + "frame_" + convert(f, f_len) + ".png")

rename_files(directory_path)