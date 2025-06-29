while(True):
    try:
        height = int(input("Height: "))
        if height > 8 or height < 1:
            continue
        else:
            break
    except ValueError or TypeError:
        continue


for col in range(height):

    for row in range(col, height -1):
        print(" ", end="")

    for star in range(col+1):
        print("#", end="")

    print()
