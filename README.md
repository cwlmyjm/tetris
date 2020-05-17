# Tetris

## Notes

You can write your program by using any language you’d like. Preferably it’s an object-oriented language: eg, Java, C++, Python (written in an object-oriented way).

## Description

Let’s consider the most famous video game in the world: Tetris.

![image](https://raw.githubusercontent.com/cwlmyjm/tetris/master/README/1.jpg)

Some random tetrominoes (shapes each composed of four square blocks) will fall down sequentially into the playing field. The objective of the game is to manipulate those tetrominoes, by moving each one sideways and/or rotating it, with the aim of creating a horizontal line of blocks without gaps. When such a line is created, it disappears, and any block above that line will fall until it hits an obstacle. See the sample test case for further details.

Tetris game manuals refer to the seven one-side tetrominoes in Tetris as I, J, L, O, S, T and Z (due to their resembling letters of the alphabet). All are capable of single and double clears. I, J and L are able to clear triples. Only the I tetromino has the capacity to clear four lines simultaneously, and this is referred to as a “tetris”.
<p align="right">Wikipedia (http://en.wikipedia.org/wiki/Tetris)</p>

The scoring formula for the majority of Tetris products is based on the idea that more difficult line clears should be awarded more points. Specifically, a single clear will be awarded 100 points, 250 points for a double clear, 400 points for a triple clear, and 1000 points for a “tetris”.
Now you are given the width of the playing field and a sequence of tetrominoes with the position and degrees it rotated. The task is to calculate how many points will be awarded.

You can assume the playing field is high enough, so that tetrominoes will not overlap each other even when a tetromino is created at the top of the playing field.

## Input 

There are multiple test cases.

The first line of the input contains an integer T, meaning the number of the test cases.
The first line of each case contains two integers W and N (1≤W ≤30000, 0≤N≤30000), where W is the width of the playing field and N is the number of tetrominoes.

Then N lines follow. Each line contains the description of a single tetromino. The type of the tetromino (I, J, L, O, S, T or Z) comes first, followed by an integer ID, meaning the id of the column of the leftmost square block in the tetromino. The columns are numbered in increasing order from left to right, beginning with zero. The last number shows the degree the tetromino should be rotated; it can only be 0, 90, 180 or 270. The one with 0-degree rotation is shown in the above picture.

Note that the rotate operations are in clockwise. And the order of tetrominoes is the same as the input sequence. See the sample input for further details.

## Output 
For each test case you should output three lines.

The first line contains the case number. The second line contains a single integer which is the points awarded in total. The third line contains W integers, the i-th number is the height of the highest square block in the i-th column, separated by a single whitespace.

## Sample Input 
```
2
6 9
I 0 0
S 3 90
T 4 270 
J 0 0 
J 2 90 
S 0 0 
Z 3 0 
O 0 0
L 4 270 
1 1
I 0 90
```

## Sample Output
```
Case #1: 
200 
6 6 4 4 6 6 
Case #2: 
1000 
0 
```

## Hint 
The final state of the game field is shown below.

![image](https://raw.githubusercontent.com/cwlmyjm/tetris/master/README/2.jpg)
 
## Submission

1. Please make sure your code is readable and well-documented.
2. You will also receive three input files: small_input.txt, medium_input.txt, and big_input.txt. Please run your program on these input files to generate their output files: small_output.txt, medium_output.txt, and big_output.txt.
3. Also, for each output file, please compute the sum of all points of the test cases. So, for each output file, you will produce one number (total points). 
4. Please also record the amount of time it takes your program to generate each output file. Ideally, time for each program should be below say 20 minutes.
5. Finally, submit your source code, the three output files, three total points, and three run times.

## Question Source
2009 Asia Shanghai Regional Contest Host by DHU  
[杭州电子科技大学](http://acm.hdu.edu.cn/showproblem.php?pid=3224)  
[南京理工大学](http://icpc.njust.edu.cn/Problem/Hdu/3224/)
