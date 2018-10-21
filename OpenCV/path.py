import numpy as np


# Takes a file and turns it into a 2-D array
screen = [] # the 2-D array containing the file

with open("./binary_output/tree_out.txt", "r") as file: # open file
    for line in file: # loop through file lines
        readLine = []
        for c in line.strip(): # removes newline characters
            readLine.append(c) # append each character of the line
        screen.append(readLine) # append each line, as a list, to screen

plane = np.asarray(screen, dtype=int)
coordinates = np.argwhere(plane==1)
print(coordinates)
print('\n\n\n\n\n\n\n\n\n')

path = []

# special case: calculating the shortest distance from (0,0) to closest 1
# origin = np.array([0,0])
current_coord = [0, 0] # start at the origin
path.append(current_coord) # make the origin the start of the path

next_coord = [0, 0] # initialize next_coord

# i represents the number of times calculating the distance between each coordinates
# or making a step in the path
for i in range(len(coordinates)):
    min_dist = 4500 # close enough to max distance you can get to

    # going through coordinates we haven't gone to
    for j in range(len(coordinates)):
        coord = coordinates[j];
        dist = np.linalg.norm(coord - current_coord)
        if min_dist > dist:
            min_dist = dist
            next_coord = coord
            min_list_count = j

    path.append(next_coord) # add the next step in our path
    current_coord = next_coord # use to calculate where to go next
    coordinates = np.delete(coordinates, min_list_count, axis=0) # remove the step we took

f = open("../draw/path.txt", "w")
for i in range(len(path) - 1):
    step1 = path[i]
    step2 = path[i+1]
    x_dist = step2[1] - step1[1]
    y_dist = step2[0] - step1[0]
    f.write("{0} {1}\n".format(x_dist, y_dist))

f.close()
