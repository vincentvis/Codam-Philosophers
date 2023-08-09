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

## Codam project FAQ

All Codam projects are written within the 42/codam styleguide called The Norm. The intention is that it should force you to write clean code and make everybody write in the same style so evaluations and code reviews are easier.
This gives guidelines on maximum lines per function (25), maximum characters per line (80), maximum functions per file (5), maximum number of parameters per function (4) etc.
Although these guidelines are highly debated and do not always serve their intented function of clean code, they are non negotionable in the projects, 1 small mistake and you have to redo the project.

Thus the "cleanness" of the code in these projects are within the scope of The Norm. More information about the norm can be found in [this repository](https://github.com/42School/norminette/)
