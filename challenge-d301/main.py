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

gamma_rate_counts = [{"1": 0, "0": 0} for x in binaries[0]]

for bin in binaries:
    for i, bit in enumerate(bin):
        gamma_bit_count = gamma_rate_counts[i]
        gamma_bit_count[bit] += 1

gamma_rate = ""

for counts in gamma_rate_counts:
    gamma_rate += "1" if counts["1"] > counts["0"] else "0"

power_rate = ''.join(['1' if i == '0' else '0' for i in gamma_rate])

print(gamma_rate, power_rate)
print(binaryToDecimal(int(gamma_rate))*binaryToDecimal(int(power_rate)))