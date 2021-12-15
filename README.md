# Philosophers 
I’ve never thought philosophy would be so deadly

### Usage

```s
make && ./philo 4 310 200 200
```
### Sommaire

1. [Le sujet](https://github.com/tinaserra/philosophers#1-sujet)
2. [Les threads](https://github.com/tinaserra/philosophers#2-quest-ce-quun-thread-)
3. [Les mutex](https://github.com/tinaserra/philosophers#3-quest-ce-quun-mutex-)

## 1. Sujet

* [Sujet 42](https://cdn.intra.42.fr/pdf/pdf/34923/en.subject.pdf)
* Scale de correction -> [EN](https://github.com/tinaserra/philosophers/blob/main/links/scale_philo.pdf) | [FR](https://github.com/tinaserra/philosophers/blob/main/links/scale_philo.md)

### Description
* Chaque philosophe est un **thread**, et chaque fourchette est un **mutex**
* Ils font dans l'ordre : **manger ➜ dormir ➜ penser.**
* Il y a une seule fourchette par philisophe et ils doivent avoir deux fourchettes pour manger (ils empruntent une fourchette a leur voisin).
* si un philosophe meurt la simulation s'arrête et on doit afficher la mort dans maximum 10 millisecondes.
* On doit écrire chaque changement de statut de philosophe.

### Fonctions autorisées

* ```memset```, ```printf```, ```malloc```, ```free```, ```write```
* ```usleep```
* ```gettimeofday``` permet de lire l'heure actuelle. la fonction prend en parametre l'argument ```tv```, une structure timeval (décrite dans <sys/time.h>), et ```tz``` une structure timezone. L'utilisation de la structure timezone est obsolète, le fuseau horraire n'est pas gere sous linux. l'argument ```tz``` doit etre ```NULL```.
* ```pthread_create``` cree un thread et prend en parametre une fonction
* ```pthread_detach``` -> [man](http://manpages.ubuntu.com/manpages/bionic/fr/man3/pthread_detach.3.html) Ici on utilise pour le thread **death**
* ```pthread_join``` premet d'attendre un thread
* ```pthread_mutex_init```
* ```pthread_mutex_destroy```
* ```pthread_mutex_lock``` bloque / verouille le mutex prendant qu'on l'utilise dans un tread x et empecher les threads y, z, ... de l'utiliser simultanément.
* ```pthread_mutex_unlock```

### Fonction non autorisée

* la fonction ```pthread_exit``` n'est pas autorisé pour le projet de 42 tu peux mettre tout simplement un ```return ;```

## 4. Tests, leaks & data race

### Tests

- 1 402 200 200

## 2. Qu'est-ce qu'un thread ?

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

### pour compiler

```sh
gcc tuto/mutex2.c -lpthread && ./a.out
```

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

voir [thread.c](https://github.com/tinaserra/philosophers/blob/main/tuto/thread.c) pour un exemple avec des chaines de caracteres

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

## 3. Qu'est-ce qu'un mutex ?

si deux thread utilisent la meme variable en meme temps ca peut faire des problemes. pour que les thread utilisent la variable chacun leur tour on peut les bloquer temporairement grace aux **mutex**.

### variable

```c++
pthread_mutex_t	mutex;
```

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
}				t_env;

void	*ciao(void *data)
{
	t_env *philo;
	char *s1;

	philo = (t_env *)data;
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
	t_env *philo;
	char *s2;

	philo = (t_env *)data;
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
	t_env	philo;

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
voir [mutex2.c](https://github.com/tinaserra/philosophers/blob/main/tuto/mutex2.c) & [mutex.c](https://github.com/tinaserra/philosophers/blob/main/tuto/mutex.c)</br>

**resultat :**
```sh
$ gcc tuto/mutex.c -lpthread && a.out

Ciao ciao !
end1
Bye bye
end2
```

tu peux t'amuser a commenter les ```pthread_mutex_lock(&philo->mutex);```
et ```pthread_mutex_unlock(&philo->mutex);```

**resultat :**
```sh
$ gcc tuto/mutex.c -lpthread && a.out

BCyiea ob ycei
end2
ao !
end1
```
sans les mutex les threads s'executent en meme temps
