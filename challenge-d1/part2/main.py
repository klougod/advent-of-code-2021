#!/usr/bin/env python3

import sys

if len(sys.argv) < 2:
    print('Provide input file as first argument to program')
    sys.exit(1)

filename = sys.argv[1]

measurements = []

try:
    with open(filename) as file:
        measurements = file.readlines()
        measurements = [int(m.rstrip()) for m in measurements]
except IOError:
    print("Could not read file: ", filename)
    sys.exit(1)
except Exception:
    print("Could not read integers in file: ", filename)
    sys.exit(1)

increase_count = 0
total = len(measurements)

def safe_get_measuremnt(idx, increment = 0):
  try:
    return measurements[idx+increment]
  except IndexError:
    return measurements[idx-increment]

last_trio = [safe_get_measuremnt(0), safe_get_measuremnt(1), safe_get_measuremnt(2)]

for actual_index, measurement in enumerate(measurements):
    if actual_index + 3 > total:
        continue

    actual_trio = [safe_get_measuremnt(actual_index), safe_get_measuremnt(actual_index, 1), safe_get_measuremnt(actual_index, 2)]

    if sum(actual_trio) > sum(last_trio):
        increase_count += 1

    last_trio = actual_trio

print(increase_count)
