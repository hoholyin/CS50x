import cs50
import sys

def main():
    if len(sys.argv)==2:
        print("Plaintext:", end="")
        t=cs50.get_string()
        key=int(sys.argv[1])
        if key>26:
            while True:
                key=key-26
                if key<=26:
                    break
        elif key<0:
            while True:
                key=key+26
                if key>=0:
                    break
        
        encrypt(t,key)
        exit(0)
    else:
        print("Invalid Input")
        exit(1)

def encrypt(t,key):
    print("Ciphertext:", end="")
    for i in range(len(t)):
        z=t[i]
        #check if its lowercase and change all to uppercase
        if ord(z)>=ord('a') and ord(z)<=ord('z'):
            z=ord(z)-(ord('a')-ord('A'))
        elif ord(z)>=ord('A') and ord(z)<=ord('Z'):
            z=z
        else:
            exit(1)
        
        c=z+key
        if c>ord('Z'):
            c=c-26
        #if it was lowercase change it back to lowercase
        if t[i]>='a' and t[i]<='z':
            c=c+(ord('a')-ord('A'))
            print("{}".format(chr(c)),end="")
        else:
            print("{}".format(chr(c)),end="")
    print()
    
if __name__ == "__main__":
    main()
    
    