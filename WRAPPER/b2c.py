import sys
def b2c():
    if (len(sys.argv) > 2):
        print('arg error!')
        return
    b_name = str(sys.argv[1])
    file = open(b_name, mode='rb')
    binary = file.read()
    size = len(binary)
    file.close()
    out_array = 'unsigned char arr[] = {'
    for b in binary:
        out_array += str(b) + ', '
    out_array = out_array[:-2]
    out_array += '};'
    outfile = open('./char.h', mode='w')
    outfile.write(out_array)
    outfile.close()
    print('size: ' + str(size))
if __name__ == "__main__":
    b2c()