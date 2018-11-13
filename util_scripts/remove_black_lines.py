"""
A little script to remove the black lines between map territories on an image of a map.
"""
from PIL import Image

def targets(x,y, max_x, max_y):
    """
    Yield potential targets to search for non-black pixels
    """
    xp1 = x+1
    xm1 = x-1
    yp1 = y+1
    ym1 = y-1
    for x_val in (x, xp1, xm1):
        if x_val > 0 and x_val < max_x:
            for y_val in (y, yp1, ym1):
                if y_val > 0 and y_val < max_y:
                    if x_val != x or y_val != y: # don't yield (x,y) itself
                        yield (x_val, y_val)

def main():
    im = Image.open(input("Enter file location: "))
    data = im.load()
    new_im_data = []
    black = (0,0,0)
    white = (255,255,255)
    for row in range(im.size[1]):
        for col in range(im.size[0]):
            if data[col,row] == black:
                candidate_found = False
                for cc, rr in targets(col, row, im.size[0], im.size[1]):
                    if data[cc, rr] not in (black, white):
                        new_im_data.append(data[cc, rr])
                        candidate_found = True
                        break
                if not candidate_found:
                    print("couldn't find valid target at ", col, ',', row)
            else:
                new_im_data.append(data[col,row])

    im2 = Image.new(im.mode, im.size)
    im2.putdata(new_im_data)
    im2.show()
    im2.save(input("Enter file save destination (w/ extension): "))

if __name__ == '__main__':
    main()