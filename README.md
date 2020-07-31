# Hive-lem-in
Elementary max flow algorithmic project. Guiding ants thru ant farm.

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

```
./generator --flow-one | ./lem-in [-flags]
```


## Disclaimer

## Improvements

## Grade
** ??? / 100**

_Completed 31.7.2020_
