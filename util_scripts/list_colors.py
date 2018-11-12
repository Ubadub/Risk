"""
A little script to list all colors in the given image.
"""

from PIL import Image

def main():
    colors = set()
    im = Image.open(input("Enter file location: "))
    data = im.getdata()
    for pixel in data:
        colors.add(pixel)

    sorted_colors = sorted(colors)
    print(',\n'.join(str(t) for t in sorted_colors))
    print(len(sorted_colors))

if __name__ == '__main__':
    main()