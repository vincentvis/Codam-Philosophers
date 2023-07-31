# Philosophers

**A Codam project**

> Project summary:
> In this project, you will learn the basics of multi threaded processes. You will learn how to make threads and how to work with mutexes.

The program should run a simulation of philosophers eating at a table. Between each philosopher there is 1 fork. Each philosopher needs 2 forks to eat, only allowed to pick up forks directly next to them, so they can not eat all at the same time.
The philosophers have a set rhythm: sleep -> think -> eat -> sleep -> think -> eat ...

## Personal goals

-   [x] Work in a TDD manner
-   [x] Write tests in a Codam style acceptable way
-   [x] Understand how to avoid race conditions
-   [x] Make the simulation work with large numbers of philosophers/threads (200+)
