# Philosophers : scale de correction

## Introduction

*Merci de respecter les règles suivantes :*
* Rester poli, courtois, respectueux et constructif
tout au long du processus d'évaluation. Le bien-être de la communauté en dépend.
* Identifier avec la personne (ou le groupe) évaluée les éventuels dysfonctionnements du travail. Prenez le temps de discuter
et débattre des problèmes que vous avez identifiés.
* Vous devez considérer qu'il peut y avoir une certaine différence dans la façon dont vos pairs ont pu comprendre les instructions du projet et la portée de ses fonctionnalités. Gardez toujours l'esprit ouvert et notez-le le plus honnêtement possible. La pédagogie n'est valable et seulement si l'évaluation par les pairs est menée sérieusement.

## Des lignes directrices
* Ne notez que le travail qui se trouve dans le référentiel GiT de l'étudiant ou du groupe.
* Vérifiez que le référentiel GiT appartient à l'étudiant ou au groupe. Assurez-vous que le travail est pour le projet concerné et vérifiez également que "git clone" est utilisé dans un dossier vide.
* Vérifiez bien qu'aucun alias malveillant n'a été utilisé pour vous tromper et vous faire évaluer autre chose que le contenu du référentiel officiel.
* Pour éviter toute surprise, vérifiez soigneusement que tant les élèves évaluateurs que les élèves évalués ont revu les scripts possibles utilisés pour faciliter la notation.
* Si l'étudiant évaluateur n'a pas encore terminé ce projet particulier, il est obligatoire pour cet étudiant de lire l'intégralité du sujet avant de commencer la soutenance.
* Utiliser les drapeaux disponibles sur cette échelle pour signaler un référentiel vide, un programme non fonctionnel, une erreur de norme, une triche etc. Dans ces cas, la notation est terminée et la note finale est 0 (ou -42 en cas de triche). Cependant, sauf pour tricher, vous êtes
encouragés à continuer à discuter de votre travail (même si vous ne l'avez pas terminé) pour identifier les problèmes qui pourraient avoir causé
cet échec et éviter de répéter la même erreur à l'avenir.
* N'oubliez pas que pendant la durée de la soutenance, aucune faute de segmentation, aucune autre interruption imprévue, prématurée, incontrôlée ou inattendue du programme, sinon la note finale est de 0. Utilisez le drapeau approprié.
Vous ne devriez jamais avoir à modifier un fichier à l'exception du fichier de configuration s'il existe. Si vous souhaitez éditer un fichier, prenez le temps d'expliquer les raisons avec l'étudiant évalué et assurez-vous que vous êtes tous les deux d'accord avec cela.
* Vous devez également vérifier l'absence de fuites mémoire. Toute mémoire allouée sur le tas doit être correctement libérée avant la fin de l'exécution.
Vous êtes autorisé à utiliser l'un des différents outils disponibles sur l'ordinateur, tels que
fuites, valgrind ou e_fence. En cas de fuite de mémoire, cochez le drapeau approprié.

## Partie obligatoire
La gestion des erreurs
Ce projet est à coder en C, suivant la Norme.
Tout plantage, comportement indéfini, fuite de mémoire ou erreur de norme signifie 0 pour le projet.
Sur certains matériels lents, le projet peut ne pas fonctionner correctement.
Si certains tests ne fonctionnent pas sur votre machine, essayez d'en discuter honnêtement avant de le considérer comme faux.

## Code philo
Vérifiez le code de Philo pour les choses suivantes et demandez une explication.
- [ ] Vérifiez s'il y a un **thread** par philosophe.
- [ ] Vérifiez qu'il n'y a qu'une **fourchette** par philosophe.
- [ ] Vérifiez s'il y a un **mutex** par fourchette et qu'il est utilisé pour vérifier la valeur de la fourchette et/ou la modifier. 
- [ ] Vérifiez que la sortie ne doit jamais produire une vue brouillée.
- [ ] Vérifier comment la mort d'un philosophe est vérifiée et s'il y a un **mutex** pour protéger qu'un philosophe meurt et commence à manger en même temps.

## Test de philosophie
- [ ] Ne pas tester avec plus de 200 philosophes
- [ ] Ne pas tester avec ```time_to_die``` ou ```time_to_eat``` ou ```time_to_sleep``` sous **60 ms**
- [ ] Testez au ```1 800 200 200```, le philosophe ne doit pas manger et doit mourir !
- [ ] Test avec ```5 800 200 200```, personne ne doit mourir !
- [ ] Test avec ```5 800 200 200 7```, personne ne doit mourir et la simulation doit s'arrêter lorsque tous les philosophes ont mangé au moins 7 fois chacun.
- [ ] Test avec ```4 410 200 200```, personne ne doit mourir !
- [ ] Test avec ```4 310 200 100```, un philosophe devrait mourir !
- [ ] Testez avec **2 philosophes** et vérifiez les différents temps (un décès retardé de plus de 10 ms est inacceptable).
- [ ] **Testez avec vos valeurs** pour vérifier toutes les règles. Vérifiez si un philosophe meurt au bon moment s'il ne vole pas des fourchettes, etc.