# philosophers
I’ve never thought philosophy would be so deadly

## Le sujet

### Fonctions autorisées

```memset```, ```printf```, ```malloc```, ```free```, ```write``` </br>
```usleep``` </br>```gettimeofday``` </br>```pthread_create``` </br>```pthread_detach``` </br>```pthread_join``` </br>```pthread_mutex_init``` </br>```pthread_mutex_destroy``` </br>```pthread_mutex_lock``` </br>```pthread_mutex_unlock```

## qu'est-ce qu'un thread ?

les thread sont des programmes qui vont demarrer au sein d'un premier et qui vont se separer pour accomplir des taches / effectuer leurs instructions simultanement / en meme temps, sans forcement etre lies sauf en terme de memoire. c'est de la programmation dite asynchrone.

### library

```
#include <pthread.h>
```

### variable

```c++
pthread_t t1;
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

## qu'est-ce qu'un mutex ?

si deux thread utilisent la meme variable en meme temps ca peut faire des problemes. pour que les thread utilisent la variable chacun leur tour on peut les bloquer temporairement grace aux **mutex**.

### initialiser

il existe deux manieres d'initialiser un mutex :

1. en variable globale
```c++
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
```

2. avec ```pthread_mutex_init```
```c++
pthread_mutex_init(&mutex, NULL);
```

a 42 tu dois initialiser les mutex de cette maniere.

### lock & unlock

un mutex peut prendre **deux etats** : un **etat bloque** et un **etat pas bloque**.

```c++
pthread_mutex_lock(&mutex);
pthread_mutex_unlock(&mutex);
```

### destroy

tu peux detruire le mutex apres utilisation (je n'ai pas vu de difference lorsqu'on detruit le mutex mais c'est une bonne pratique)

```c++
pthread_mutex_destroy(&mutex);
```

### exemple

```c++
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct	s_philo
{
	pthread_t		t1;
	pthread_t		t2;
	pthread_mutex_t	mutex;
}				t_philo;

void	*ciao(void *data)
{
	t_philo *philo;
	char *s1;

	philo = (t_philo *)data;
	int i = 0;
	s1 = "Ciao ciao !";
	pthread_mutex_lock(&philo->mutex); // bloquer le mutex pendant que tue execute
	while (i < 11)
	{
		fprintf(stderr, "%c", s1[i]);
		usleep(100000);
		i++;
	}
	fprintf(stderr, "\n");
	fprintf(stderr, "end1\n");
	pthread_mutex_unlock(&philo->mutex); // c bon tu peux debloquer
	pthread_exit(NULL);
}

void	*bye(void *data)
{
	t_philo *philo;
	char *s2;

	philo = (t_philo *)data;
	int i = 0;
	s2 = "Bye bye";
	pthread_mutex_lock(&philo->mutex);
	while (i < 7)
	{
		fprintf(stderr, "%c", s2[i]);
		usleep(100000);
		i++;
	}
	fprintf(stderr, "\n");
	fprintf(stderr, "end2\n");
	pthread_mutex_unlock(&philo->mutex);
	pthread_exit(NULL);
}

int		main(void)
{
	t_philo	philo;

	/* obligatoire de init le mutex */
	pthread_mutex_init(&philo.mutex, NULL);

	pthread_create(&philo.t1, NULL, hello1, &philo);
	pthread_create(&philo.t2, NULL, hello2, &philo);

	pthread_join(philo.t1, NULL);
	pthread_join(philo.t2, NULL);

	pthread_mutex_destroy(&philo.mutex);
	return (0);
}
```

**resultat :**
```sh
$ gcc mutex.c -lpthread && a.out

Ciao ciao !
end1
Bye bye
end2
```

tu peux t'amuser a commenter les ```pthread_mutex_lock(&philo->mutex);```
et ```pthread_mutex_unlock(&philo->mutex);```

**resultat :**
```sh
$ gcc mutex.c -lpthread && a.out

BCyiea ob ycei
end2
ao !
end1
```
sans les mutex les threads s'executent en meme temps

#### attention a printf !

dans l'exemple d'avant j'utilise ```fprintf```.</br>
si tu utisile la fonction ```printf``` tu peux avoir l'impression que tout fonctionne correctement **sans les mutex**.</br>
je pense que c'est du au fait que ```printf``` ecrit la string dans un buffer avant de la print. donc tu ne verra pas les caracteres de la string dans le desordre meme si tu n'utilise pas les mutex dans ton code.</br>

#### pour 42
pour le projet philosopher a 42, la plupart des gens utilisent ```write```.
egalement, la fonction ```pthread_exit``` n'est pas autorisé pour le projet de 42 tu peux mettre tout simplement un ```return ;```
