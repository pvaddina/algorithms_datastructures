import random

MAX_SIZE = 20

dataTypeProps = {
            "array": {
                        "open_brace": "{",
                        "start": 0,
                        "stop": MAX_SIZE,
                        "length": MAX_SIZE,
                     },
            "vec": {
                        "open_brace": "{",
                        "start": 0,
                        "stop": MAX_SIZE,
                        "length": MAX_SIZE,
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
    fp.write(" };\n\n") # close the array


def create_data(file_name, prefix, filler):
    newFN = file_name.format(**filler)
    fp = open(newFN, 'w')
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

    fp.write(" }\n\n") # close the namespace
    fp.close()


create_data("data_array_{length}.h", "namespace Data{open_brace} int data_array_{length}[] = {open_brace} ", dataTypeProps["array"])
create_data("data_vec_{length}.h", "#include<vector>\n\nnamespace Data{open_brace} std::vector<int> data_vec_{length} {open_brace} ", dataTypeProps["vec"])
create_data("data_std_array_{length}.h", "#include<array>\n\nnamespace Data{open_brace} constexpr size_t NUM_ITEMS={length};\n\nusing MyStdArray{length} = std::array<int,NUM_ITEMS>;\n\n MyStdArray{length} data_std_array_{length} {open_brace} ", dataTypeProps["std_array"])

