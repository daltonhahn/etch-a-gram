import cv2
import numpy as np

BLACK = (255,255,255)
WHITE = (0,0,0)

outputfile = open("output.txt", "w")

img = cv2.imread('square.png')
retval, threshold = cv2.threshold(img, 12, 255, cv2.THRESH_BINARY)
cv2.imshow('original',img)
cv2.imshow('threshold',threshold)
imageneg = cv2.bitwise_not(threshold)
cv2.imshow('negative', imageneg)


neg_img_data = np.asarray(imageneg)
for row in range(len(neg_img_data)):
    for col in range(len(neg_img_data[0])):
        pixel_val = neg_img_data[row][col]
        if(pixel_val[0] == pixel_val[1] == pixel_val[2] == 255):
            outputfile.write("0")
        else:
            outputfile.write("1")
    outputfile.write("\n")

cv2.waitKey(0)
cv2.destroyAllWindows()
