while(True):
    try:
        height = int(input("Height: "))
        if height > 8 or height < 1:
            continue
        else:
            break
    except ValueError or TypeError:
        continue



for rows in range(height):
    for cols in range(rows, height - 1):
        print(" ", end='')

    for hash1 in range(rows + 1):
        print("#", end='')

    print("  ",end='')

    for hash2 in range(rows + 1):
        print("#",end='')

    print()










