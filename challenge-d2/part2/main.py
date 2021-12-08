#!/usr/bin/env python3

import sys

if len(sys.argv) < 2:
    print('Provide input file as first argument to program')
    sys.exit(1)

filename = sys.argv[1]

commands = []

try:
    with open(filename) as file:
        commands = file.readlines()
        commands = [cmd.rstrip().split(' ') for cmd in commands]
except IOError:
    print("Could not read file: ", filename)
    sys.exit(1)
except Exception:
    print("Could not read integers in file: ", filename)
    sys.exit(1)

aim = 0
depth = 0
horizontal = 0

def step_forward(v):
    global horizontal
    global depth
    global aim

    horizontal += int(v)
    depth += aim * int(v)

def step_down(v):
    global aim

    aim += int(v)

def step_up(v):
    global aim

    aim -= int(v)

command_handler = {
    "forward": step_forward,
    "down": step_down,
    "up": step_up
}

for (cmd_type, cmd_value) in commands:
    cmd_function = command_handler.get(cmd_type)

    if(cmd_function):
        cmd_function(cmd_value)

print("DEPTH: ", depth)
print("HORIZONTAL: ", horizontal)
print("TOTAL: ", horizontal * depth)
