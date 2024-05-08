text = "Lmoa"

for i in range(48):
    print(f'{i}. \033[{i}m{text}\033[0m')