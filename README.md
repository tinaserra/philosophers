# philosophers
I’ve never thought philosophy would be so deadly

## questce qu'un thread ?

les thread sont des programmes qui vont demarrer au sein d'un premier et qui vont se separer pour accomplir des taches / effectuer leurs instructions simultanement / en meme temps, sans forcement etre lies sauf en terme de memoire. c'est de la programmation dite asynchrone.

### library

```
#include <pthread.h>
```

### variable

```
pthread_t t1; #type pthread_t
pthread_t t2;
```
### creer un thread

