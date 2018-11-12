"""
Find all black pixels in an image.
"""

from PIL import Image

def find_black_pixels(fname):
    im = Image.open(fname)
    data = im.load()
    black = (0,0,0)
    found = False
    for col in range(im.size[0]):
        for row in range(im.size[1]):
            if data[col,row] == black:
                found = True
                print("Black found at: ", col, ", ", row)
    if not found:
        print("None found!")

def main():
    find_black_pixels(input("Enter file location: "))

if __name__ == '__main__':
    main()