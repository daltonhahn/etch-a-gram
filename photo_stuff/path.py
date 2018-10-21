import numpy as np


# Takes a file and turns it into a 2-D array
screen = [] # the 2-D array containing the file

with open("./binary_output/square_output.txt", "r") as file: # open file
    for line in file: # loop through file lines
        readLine = []
        for c in line.strip(): # removes newline characters
            readLine.append(c) # append each character of the line
        screen.append(readLine) # append each line, as a list, to screen




plane = np.asarray(screen, dtype=int)
coordinates = np.argwhere(plane==1)
print(coordinates)


















# Writes the results of the 2-D array to a file.
# Saved for testing
# f = open("text_to_array.txt", "w")
# for row in screen:
#     for col in row:
#         f.write(col)
#     f.write('\n')
#
# f.close()
