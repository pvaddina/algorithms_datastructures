import random

MAX_SIZE = 10000

dataTypeProps = {
            "array": {
                        "open_brace": "{",
                        "start": 0,
                        "stop": MAX_SIZE,
                     },
            "vec": {
                        "open_brace": "{",
                        "start": 0,
                        "stop": MAX_SIZE,
                   },
            "std_array": {
                        "open_brace": "{",
                        "start": 0,
                        "stop": MAX_SIZE,
                        "length": MAX_SIZE,
                         },
                }

def add_data_to_file(fp, start, stop):
    for i in range(start, stop):
        fp.write(str(random.randint(start, stop)))
        if i < stop-start-1:
            fp.write(', ')
    fp.write(" };\n\n")


def create_data(file_name, prefix, filler):
    fp = open(file_name, 'w')
    prefix = prefix.format(**filler)
    fp.write(prefix)
    start = filler["start"]
    stop = filler["stop"]
    max_range = stop 
    iterations = int((stop-start)/max_range)

    for i in range(0,iterations):
        localStart = i*max_range
        localEnd = localStart + max_range
        add_data_to_file(fp, localStart, localEnd)

    fp.close()


create_data("data_array.h", "int data_array[] = {open_brace} ", dataTypeProps["array"])
create_data("data_vec.h", "#include<vector>\n\nstd::vector<int> data_vec {open_brace} ", dataTypeProps["vec"])
create_data("data_std_array.h", "#include<array>\n\nstd::array<int,{length}> data_std_array {open_brace} ", dataTypeProps["std_array"])

