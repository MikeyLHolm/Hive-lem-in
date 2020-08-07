# Hive-lem-in
Elementary max flow algorithmic project. Guiding ants thru ant farm. Collaboration with [Eino Lindberg](https://github.com/einoob).

## Objectives
The goal of this project is to find the quickest way to get n ants across the farm. Quickest way means the solution with the least number of lines, respecting the output format requested below. Ants will also need to avoid traffic jams as well as walking all over their fellow ants.

## Example map input with explanations
```
4          <------------  N of ants
3 2 2 ------------\
##start           |
start 4 0         |
##end             |
end 4 6           |---->  Room names and coordinates.
4 0 4             |       ##command apply to next row.
1 4 2             |
2 4 4             |
5 8 2             |
6 8 4 ------------/
start-1 ----------\
3-4               |
2-4               |
1-5               |
6-5               |---->  Links between rooms
end-6             |
1-2               |
2-end             |
3-start ----------/
```
This input will translate into:
```
   [start] 
    / |
 [3] [1]--[5]
 /    |    | 
[4]--[2]  [6]
      |  /
     [end]
```
## Algorithm

## How to use
```
make
```
```
./lem-in [-flags] < [map]
```
Running with in-built map generator:
```
./generator --flow-one | ./lem-in [-flags]
./generator --flow-ten | ./lem-in [-flags]
./generator --flow-thousand | ./lem-in [-flags]
./generator --big | ./lem-in [-flags]
./generator --big-superposition | ./lem-in [-flags]
```
Available flags:
```
-a    : input N of ants manually. N must come as an argument after flags. [./lem-in -a -ep N].
-e    : improved error management.
-h    : help menu.
-l    : prints out lines used.
-p    : prints out paths used.
-v    : verbose mode
-x    : checks for mem leaks
```

## Disclaimer
This project has to be completed respecting our schools norme. Here is some of the rules:
```
* Each function must be maximum 25 lines, not counting the function’s own curly brackets.
* Each line must be at most 80 columns wide, comments included.
* One instruction per line.
* One single variable declaration per line.
* No declaration and an initialisation on the same line.
* A function can take 4 named parameters maximum.
* You can’t declare more than 5 variables per function.
```
Available library functions for this project:
```
* malloc
* free
* read
* write
* strerror
* perror
* exit
```

## Possible Improvements and problems
* Flags accept wrong letters at end.
* Implementing residual flows to links would increase accuracy.

## Grade
** 109 / 100**

_Completed 4.8.2020_
