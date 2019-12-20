import cs50

def main():
    while True:
        print("Height:", end="")
        h = cs50.get_int()
        if h>=0 and h<=23:
            break
    
    printpyramid(h)
    
def printpyramid(h):
    row=0
    for row in range (h):
        for space in range (h-row-1):
            print(" ", end="")
        for hex1 in range (row+1):
            print("#", end="")
        print("  ", end="")
        for hex2 in range (row+1):
            print("#", end="")
        print()
        

if __name__ == "__main__":
    main()
    
        