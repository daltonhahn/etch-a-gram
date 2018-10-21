

path_file = open("path.txt", "r")

comp_file = open("compressed.txt", "w")

comp_file.write("")


cur_line = path_file.readline()
for i in range(len(path_file)):
    next_line = path_file.readline()
    next_elems = next_line.split()
    print(next_elems)

    next_x = next_elems[0]
    next_y = next_elems[1]

    elems = cur_line.split()
    print(elems)
    x_val = elems[0]
    y_val = elems[1]

