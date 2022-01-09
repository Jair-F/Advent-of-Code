import os
import sys


input_data = str()
with open("part1 - input.txt") as input:
    input_data += input.readline()
latern_fish = input_data.split(',')

for i in range(len(latern_fish)):
    latern_fish[i] = int(latern_fish[i])

print(latern_fish)


for i in range(256): # number of days part 1: 80 part2: 256(takes a lot of memory and time!!)
    fish_to_add = list()
    for i in range(len(latern_fish)):
        if latern_fish[i] == 0:
            fish_to_add.append(8)
            latern_fish[i] = 6
        else :
            latern_fish[i] -= 1
    for x in fish_to_add:
        latern_fish.append(x)
    #print(latern_fish)

print(len(latern_fish))