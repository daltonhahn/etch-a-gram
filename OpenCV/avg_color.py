import cv2
import numpy
myimg = cv2.imread('./figures/lisa.png')
avg_color_per_row = numpy.average(myimg, axis=0)
avg_color = numpy.average(avg_color_per_row, axis=0)
print(avg_color)
