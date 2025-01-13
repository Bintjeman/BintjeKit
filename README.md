# BintjeKit


Le Kit de travail.

## Objectif
Une petite bibliothèque pour m'aider à commencer des projet sfml plus rapidement... Et tester les module c++20...


## Contenu

### Base du programme
Un module général qui sert de squelette au programme qui contient :

1. Une classe Core
2. Une class Factory 
3. Une classe Window
4. une classe Renderer
5. une classe UI
6. une classe simulation

Core gère tous les composants et les class dont il est propriétaire.
L'utilisateur peututilsée une propre implémentation de Factory et redéfinir les méthodes de création des composants avec des composants eux-mêmes hérités.

### Des outils
 - Un wrapper de spdlog sous la forme d'une class pour logger en interne et donner à l'utilisateur la possibilité de choisir les fichiers, le level, etc.
L'utilisateur peut aussi utiliser ce même logger pour ces propres messages

 - Un gestionnaire de configurations qui permet de charger un fichier json, de créer des "enfants" (qui partagent le même json). Chacun de ces nœuds peut set, get ou get_or_set chaque item.

## Dépendances

 - https://github.com/nlohmann/json
 - https://github.com/gabime/spdlog
 - https://www.sfml-dev.org/ (3)

Et utilise Dear-ImGui et sfml-ImGui

## ToDo
