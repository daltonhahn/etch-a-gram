import numpy as np

comp_file = open("Compressed/twitter_compressed.txt", "w")

line_list = []
with open("Out/twitter_out.txt", "r") as file:
    for line in file:
        line_list.append(line.split())


lines_to_delete = []
for i in range(len(line_list) - 1):
        line1 = line_list[i]
        line2 = line_list[i+1]

        x1 = int(line1[0])
        y1 = int(line1[1])

        x2= int(line2[0])
        y2 = int(line2[1])

        if(x1 == 0 and x2 == 0):
            if((y1 > 0 and y2 > 0) or (y1 < 0 and y2 < 0)):
                y2 = y2 + y1
                lines_to_delete.append(i)
                line_list[i+1][1] = y2
        elif(y1 == 0 and y2 == 0):
            if(np.sign(x1) == np.sign(x1)):
                x2 = x2 + x1
                lines_to_delete.append(i)
                line_list[i+1][0] = x2

for i in reversed(lines_to_delete):
    del line_list[i]

for i in line_list:
    comp_file.write("takeSteps({}, {});\n".format(i[0], i[1]))

comp_file.close()
