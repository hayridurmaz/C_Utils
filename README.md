# PERSONAL C LIBRARY

This is a personal c library consisting of frequently used basic functions beloging to @hayridurmaz

## Usage

Normal run:

```
gcc  -o test.out test.c  personal_utils.h personal_utils.c
```

With MPI, run:

```
mpicc -fopenmp -g -ggdb -o test.out test.c  personal_utils.h personal_utils.c parallel_utils.h parallel_utils.c
```

If makefile gives;

```
makefile:15: *** missing separator.  Stop.
```

Then, run;

```
perl -pi -e 's/^  */\t/' makefile
```
