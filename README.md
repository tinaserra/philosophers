# philosophers
I’ve never thought philosophy would be so deadly

## Le sujet

### Fonctions autorisées

```memset```, ```printf```, ```malloc```, ```free```, ```write``` </br>
```usleep``` </br>```gettimeofday``` </br>```pthread_create``` </br>```pthread_detach``` </br>```pthread_join``` </br>```pthread_mutex_init``` </br>```pthread_mutex_destroy``` </br>```pthread_mutex_lock``` </br>```pthread_mutex_unlock```

## questce qu'un thread ?

les thread sont des programmes qui vont demarrer au sein d'un premier et qui vont se separer pour accomplir des taches / effectuer leurs instructions simultanement / en meme temps, sans forcement etre lies sauf en terme de memoire. c'est de la programmation dite asynchrone.

### library

```
#include <pthread.h>
```

### variable

```c++
pthread_t t1; //type pthread_t
pthread_t t2;
```
### creer un thread

la fonction ```pthread_create``` permet de creer des thread. 

```c++
pthread_create(&t1, NULL, funct1, NULL);
```
on lui envoi en premier parametre l'adresse du thread, en troisieme une fonction et en dernier l'argument de la fonction.

#### exemple

```c++
void  *funct1(void *arg)
{
	int i;
	i = 0;
	while(i < 10)
	{
		printf("\033[91mthread 1: %d\033[0m\n", i);
		i++;
	}
	pthread_exit(NULL);
}

int		main(void)
{
	pthread_t	t1;

	pthread_create(&t1, NULL, funct1, NULL);
	return (0);
}
```

### attendre un thread

le probleme c'est que le programme main n'affiche rien car il est arrive au return (0) avant que les thread n'ai eu le temps de s'executer.

pthread_join() permet d'attendre la fin des thread.

```c++
int		main(void)
{
	pthread_t	t1;
	pthread_t	t2;

	pthread_create(&t1, NULL, funct1, NULL);
	pthread_create(&t2, NULL, funct2, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	return (0);
}
```

le programme s'arrete donc au ```pthread_join(t1, NULL);``` juqu'a ce que les thread soit fini puis il continue.

## questce qu'un mutex ?

si deux thread utilisent la meme variable en meme temps ca peut faire des problemes. pour que les thread utilisent la variable chacun leur tour on peut les bloquer temporairement grace aux **mutex**.

un mutex peut prendre deux etats : un etat bloque et un etat pas bloque.

### les fonctions

```c++
pthread_mutex_lock(&mutex);
pthread_mutex_unlock(&mutex);
```