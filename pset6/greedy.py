import cs50

def main():
    while True:
        print("How much change is owed (in dollars):", end="")
        c=cs50.get_float()
        if c>=0:
            break
        
    givechange(c)
    
def givechange(c):
    cents=c*100
    a=0
    while True:
        cents-=25
        a=a+1
        if cents<25:
            break
    b=0
    while True:
        cents-=10
        b=b+1
        if cents<10:
            break
    d=0
    while True:
        cents-=5
        d=d+1
        if cents<5:
            break
    e=0
    while True:
        cents-=1
        e=e+1
        if cents<1:
            break
    print("No. of 25c: {}".format(a))
    print("No. of 10c: {}".format(b))
    print("No. of 5c: {}".format(d))
    print("No. of 1c: {}".format(e))
    
if __name__ == "__main__":
    main()
    
    