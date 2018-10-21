import numpy as np
import cv2 #this is the main openCV class, the python binding file should be in /pythonXX/Lib/site-packages
from matplotlib import pyplot as plt

# THESE DIMENSIONS ARE TRUE DIMENSIONS - SMALLEST DESIRED BORDER SIZE
MAX_HEIGHT = 240
MAX_WIDTH = 360



#FROM: https://www.pyimagesearch.com/2015/04/06/zero-parameter-automatic-canny-edge-detection-with-python-and-opencv/
def auto_canny(image, sigma=0.33):
	# compute the median of the single channel pixel intensities
	v = np.median(image)

	# apply automatic Canny edge detection using the computed median
	lower = int(max(0, (1.0 - sigma) * v))
	upper = int(min(255, (1.0 + sigma) * v))
	edged = cv2.Canny(image, lower, upper)

	# return the edged image
	return edged

#
#
# IF TIME SCALE PHONE IMAGES DOWN THEN DO STUFF AND SCALE BACK UP
#


image = cv2.imread("./figures/tree.png") #import image
hsv = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

# FROM: https://www.pyimagesearch.com/2015/04/06/zero-parameter-automatic-canny-edge-detection-with-python-and-opencv/
# load the image, convert it to grayscale, and blur it slightly
blurred = cv2.GaussianBlur(hsv, (3, 3), 0)

# apply Canny edge detection using a wide threshold, tight
# threshold, and automatically determined threshold
wide = cv2.Canny(blurred, 10, 200)
tight = cv2.Canny(blurred, 225, 250)
auto = auto_canny(blurred)




imageneg = cv2.bitwise_not(auto)

img_height,img_width= imageneg.shape
scale_factor = min((MAX_HEIGHT)/img_height, (MAX_WIDTH)/img_width)

resized_image = cv2.resize(imageneg, (0,0), fx=scale_factor, fy=scale_factor)
resize_height, resize_width = resized_image.shape

bordersize_top = ( ( MAX_HEIGHT - resize_height)/2 )
bordersize_bottom = ( ( MAX_HEIGHT - resize_height)/2 )
bordersize_right = ( ( MAX_WIDTH - resize_width ) /2 )
bordersize_left = ( ( MAX_WIDTH - resize_width ) /2 )

if((MAX_WIDTH - resize_width) % 2 == 1):
    bordersize_right = ( (MAX_WIDTH - resize_width - 1)/2 )
    bordersize_left = bordersize_right + 1

if((MAX_HEIGHT - resize_height) % 2 == 1):
    bordersize_bottom = ( (MAX_HEIGHT - resize_height - 1)/2 )
    bordersize_top = bordersize_bottom + 1


border = cv2.copyMakeBorder(resized_image, top=int(bordersize_top), bottom=int(bordersize_bottom), left=int(bordersize_left), right=int(bordersize_right),
        borderType= cv2.BORDER_CONSTANT, value=[255,255,255] )

cv2.imwrite("./figures/tree_out.png", border)

outputfile = open("./binary_output/tree_out.txt", "w")

neg_img_data = np.asarray(border)
for row in range(len(neg_img_data)):
    for col in range(len(neg_img_data[0])):
        pixel_val = neg_img_data[row][col]
        if(pixel_val == 255):
            outputfile.write("0")
        else:
            outputfile.write("1")
    outputfile.write("\n")
