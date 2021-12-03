#!/usr/bin/env python3

import sys

if len(sys.argv) < 2:
    print('Provide input file as first argument to program')
    sys.exit(1)

filename = sys.argv[1]

binaries = []

try:
    with open(filename) as file:
        binaries = file.readlines()
        binaries = [[char for char in bin.rstrip()]for bin in binaries]
except IOError:
    print("Could not read file: ", filename)
    sys.exit(1)
except Exception as e:
    print(e)
    print("Could not read integers in file: ", filename)
    sys.exit(1)

def binaryToDecimal(binary):
    binary1 = binary
    decimal, i, n = 0, 0, 0
    while(binary != 0):
        dec = binary % 10
        decimal = decimal + dec * pow(2, i)
        binary = binary//10
        i += 1
    return decimal

def get_occurency(type, bins, i = 0):
    counts = [{"1": 0, "0": 0} for x in bins[0]]

    if(len(bins) == 1):
        return bins[0]

    for bin in bins:
        bit_count = counts[i]
        bit_count[bin[i]] += 1

    one_sum = list(map(lambda x: x['1'], counts))
    zero_sum = list(map(lambda x: x['0'], counts))

    is_one_most = one_sum >= zero_sum

    one_first = list(filter(lambda x: x[i] == '1', bins))
    zero_first = list(filter(lambda x: x[i] == '0', bins))

    if type == 'most':
        return get_occurency(type, one_first if is_one_most else zero_first, i+1)
    else:
        return get_occurency(type, zero_first if is_one_most else one_first, i+1)

oxygen_rate = ''.join(get_occurency('most', binaries))
dec_oxygen_rate = binaryToDecimal(int(oxygen_rate))

co2_rate = ''.join(get_occurency('least', binaries))
dec_co2_rate = binaryToDecimal(int(co2_rate))

print(oxygen_rate, co2_rate)
print(dec_oxygen_rate, dec_co2_rate)
print(dec_oxygen_rate*dec_co2_rate)
