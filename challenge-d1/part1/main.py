#!/usr/bin/env python3

import sys

if len(sys.argv) < 2:
    print('Provide input file as first argument to program')
    sys.exit(1)

filename = sys.argv[1]

measurements = []
increase_count = 0

try:
    with open(filename) as file:
        measurements = file.readlines()
        measurements = [m.rstrip() for m in measurements]
except IOError:
    print("Could not read file: ", filename)
    sys.exit(1)

last_measurement = int(measurements[0])

for measurement in measurements:
    temp_measurement = int(measurement)

    if(temp_measurement > last_measurement):
        increase_count += 1
    
    last_measurement = temp_measurement

print(increase_count)
