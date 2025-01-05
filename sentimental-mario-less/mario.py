while True:
    try:
        height = int(input("Height: "))
        if height in range(1, 9):
            break
        raise ValueError()
    except ValueError:
        print("Input must be an integer between 1 and 8.")

for i in range(height):
    print(f"{(height - 1) * ' ' + (i + 1) * '#'}")
    height -= 1
