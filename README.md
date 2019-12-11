# Advent of code 2019

I will post my solutions to the 2019 Advent of code here, as well as post explaination for specific choices made
I will try to make all solutions generally applicable, to be functional with arbitrary inputs, [mostly] regardless of length. As long as the input follows the rules of the problem given, these solutions should work.

Every program will be in C using the standard library. If I need to use extra header files they will all be provided and built myself.

# Day 1
__Part 1__

Simple enough, I pass the input through the command line and do the arithmetic required.

__Part 2__

I felt like a recursive approach made sense here, so that's the approach I took. Again, a simple problem, but it is still only day 1 after all.

__Post Completion Clean Up__

For some reason in my original solution, I did `i /= 3` and `i -= 2` as two seperate expressions. I simplified it to `i = i/3 - 2`

# Day 2
__Part 1__

Good practice for Malloc and pointers, though in retrospect I really didn't need dedicated functions for addition and multiplication. It felt right at the time to do it that way, more in the spirit of making an Intcode computer

__Part 2__

Not much had to be changed here, In retrospect I would have saved some performance by instead of reading the file every time simply copying `*arr` to `*arr_original` or something along those lines, but I think the performance benefits wouldn't be very noticable as long as I `free()` the memory before performing `readFile` again. 

__Post Completion Clean up__

Most of the cleaning up I did post initial completion revolved around the phrase `add(ip + *(ip+i+1), ip + *(ip+i+2), ip + *(ip+i+3));` that was in the original code. I went through a few revisions deciding how to alter it, and eventually decided on making `ip` an actual pointer, and finalize the expression as `add(program[*(ip+1)], program[*(ip+2)], program + *(ip + 3))`.

I also cleaned up the while loop in `readFile()`. Instead of using a sentinel I use the return value of `fscanf` itself, terminating only when it no longer is able to parse the input in the format `%d,`. 

I switched to using `memcpy` so that the code looked nicer and was less prone to leaks

# Day 3

__Part 1__

This one was a struggle for me. I initially tried using a 2D array, but that was not going anywhere so I switched to using Structs to store all the points. I still have a ~2 minute runtime though. I think I could improve it by using `realloc` less not searching the entire `points` array every time I add a point.


__Part 2__

Once I had part 1 finished this one was really easy. Add an intersections Struct and record distances. Piece of cake. Maybe I could use that intersection struct as an idea to improve the performance of part 1 (and also this part. Same underlying code after all)

__Post Completion Clean up__

__TODO__: Make run faster, it is *abysmally* slow right now

  More specifically, remove the check for *every* node; rather. Simply add all nodes from wire 1 without question, and then only add nodes from wire 2 to the ints struct iff they are an intersection. 

# Day 4

__Part 1__

This was a really easy problem. Simply seperate out the digits (with `/` and `%`) and do the some basic logic.

__Part 2__

This solution relies on the probability of the out of bounds array values not being exactly equal to `num[j]`. I figure the probility is so low that it's not a problem.

# Day 5

__Part 1__

Yay! More Intcode computer! I love this problem. This did take me longer than expected though, mostly dealing with minor things involving the paramater modes.

__Part 2__

This was a pretty simple extension from part 1, once that was complete it was pretty simple to add more opcodes and alter the IP

# Day 6

__Part 1__

This was a pretty simple problem that just took a while to type. Essentially I create a tree of `struct planet`, where each planet holds it's own id and it's parents. I then go through every planet, working up the tree until I hit `COM`, adding up all the steps along the way.

__Part 2__

During the reading of the file and the creation of `struct planet* map` I store the index of `YOU` and `SAN` respectively. Then I work up from `YOU` and `SAN` until I hit `COM`, adding the distance traversed to each planet along the way in a new part of the struct. Then I go through every planet, finding adding up `planet.distSAN + planet.distYOU`. The smallest one is the correct answer.

# Day 7

__Part 1__

This one wasn't too hard to figure out. The 5 for loops look ugly, but they're pretty efficient. Adding a return value to the intcode machine made a lot of sense for this problem.

__Part 2__

This one was only hard to wrap my head around how to implement. Once I figured out how I wanted to do it (storing 5 seperate ip's to essentially be able to recall the exact state) it was mostly just making sure the pointers were being handled properly.

# Day 8

__Part 1__

This was a nice break, as it was really easy. I simply count, and reset the counter every `LENGTH * WIDTH` elements, keeping track of the numbers if they are the new candidates.

__Part 2__

Initially I thought I was going to have to do crazy 3D array stuff here, but then I realized, since Layer 1 is the first in the text file and also had display priority. Once that connection was made, it was a very simple program.

# Day 9

__Part 1__

Intcode keeps coming back and I love it. I had to switch from `int` to `long long int` because of the new demands, and it was tedious just making that change, but other than that it was a simple program. I was already well set up to add new addressing modes, so it was very simple to make base addressing work.

__Part 2__

There wasn't a problem here, it simply verified that my intcode machine worked fully

# Day 10

__Part 1__

Today was rough, but it might just be that geometry is a weakness of mine. The first part wasn't too bad, I just needed to remember to allow 2 instances of the same slope if they are on opposite sides of the origin point.

__Part 2__

I'm really bad at triginometry, and this one took me ages. The biggest catch though was that I neglected to think about how the Y value as stored in an array is backwards from how it works on a graph (That is, increases in Y lower the value on the 2d Array). Once I got that fixed it worked fine.
