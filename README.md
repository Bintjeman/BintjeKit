# BintjeKit

**BintjeKit** est une bibliothèque C++ modulaire conçue pour gérer les différents composants d'une application ou simulation (jeu, interface graphique, système de rendu, etc.). Elle fournit une architecture flexible et extensible grâce à des modules C++20, une classe centrale (`Core`) et un système de `Factory` permettant de personnaliser ou d'utiliser les composants existants par défaut.

---

## 🌟 Fonctionnalités

- **Architecture centralisée via `Core`** :
    - Une classe centrale (`Core`) agit comme chef d'orchestre, propriétaire et gestionnaire des différents sous-systèmes (fenêtre, simulation, interface, renderer...).
    - Simplifie les cycles de vie (initialisation, mise à jour, destruction) des composants.
- **Composants personnalisables** :
    - Tous les sous-systèmes (comme `Window`) peuvent être remplacés par des implémentations personnalisées définies par l’utilisateur.
    - La personnalisation est facilitée par un système de `Factory`.
- **Utilitaires Tools** :
    - Inclut des outils pour le logging (`spdlog`), la sérialisation JSON (`nlohmann::json`), et autres fonctionnalités utilitaires.
    - Ces outils sont isolés dans un module `Tools` pour éviter un couplage direct avec les dépendances externes.
- **Support des modules C++20** :
    - Utilise pleinement les modules pour maximiser les temps de compilation et la modularité du projet.

---

## 📁 Structure générale
BintjeKit/
├── Core/ # Gestionnaire central (orchestrateur)
│ ├── Core.cppm # Module principal
│ ├── Factory.cppm # Factory pour créer des composants personnalisés
├── Window/ # Gestion des fenêtres
│ ├── Window.cppm # Module gérant les fenêtres
├── Tools/ # Utilitaires du projet
│ ├── Tools.cppm # Logging, JSON, etc.
└── Renderer/ # (Facultatif, gestion du rendu futur)


---

## 🔧 Classes principales

### Core
La classe principale `Core` est responsable de :
1. Créer et détenir les différents sous-systèmes (fenêtre, etc.).
2. Fournir un point d'accès unique à leurs fonctionnalités.
3. Gérer leur cycle de vie grâce à des fonctions `Initialize`, `Update`, et `Shutdown`.

#### Exemple :
```cpp
BintjeKit::Core::Core engine;
engine.Initialize();
engine.Update();
engine.Shutdown();
```

---

### Factory
Une `Factory` séparée permet de :
- Créer des composants personnalisés.
- Utiliser des composants par défaut si aucune personnalisation n'est nécessaire.

#### Exemple :
```cpp
auto customWindow = BintjeKit::Core::Factory::CreateWindow<MyCustomWindow>();
engine.SetCustomWindow<MyCustomWindow>();
```

---

### Window
Le module fenêtre fournit une implémentation de fenêtre par défaut (`BaseWindow`) et permet à l'utilisateur de créer des fenêtres personnalisées si nécessaire en héritant de `BaseWindow`.

#### Classe de base :
```cpp
class BaseWindow {
public:
    virtual void Open() {
        std::cout << "Fenêtre générique !\n";
    }
    virtual ~BaseWindow() = default;
};
```

#### Exemple d'héritage utilisateur :
```cpp
class MyWindow : public BintjeKit::Window::BaseWindow {
    void Open() override {
        std::cout << "Ma fenêtre sur mesure !";
    }
};
```

---

## 🏗️ Exemple d'utilisation basique

Voici un exemple de programme simple utilisant BintjeKit.

```cpp
#include <iostream>
import BintjeKit.Core;

int main() {
    BintjeKit::Core::Core app;

    // Initialise le système (avec ses composants par défaut)
    app.Initialize();

    // Met à jour les composants
    app.Update();

    // Termine correctement
    app.Shutdown();

    return 0;
}
```

**Sortie attendue** :

```
Logger initialisé ! Fenêtre : Ouverture de la fenêtre par défaut. Core Update: Appel de boucles des composants... Core Shutdown: Nettoyage des composants...
```

---

## 📐 Exemple avec personnalisation

Voici un exemple où l’utilisateur remplace la fenêtre par une implémentation personnalisée qu'il a définie.

```cpp
#include <iostream>
import BintjeKit.Core;
import BintjeKit.Core.Factory;

class CustomWindow : public BintjeKit::Window::BaseWindow {
    void Open() override {
        std::cout << "Ouverture de *ma* fenêtre personnalisée !" << std::endl;
    }
};

int main() {
    BintjeKit::Core::Core app;

    // Remplace la fenêtre par une fenêtre personnalisée
    auto customWindow = BintjeKit::Core::Factory::CreateWindow<CustomWindow>();
    app.SetCustomWindow<CustomWindow>();

    // Initialise et lance l'application
    app.Initialize();
    app.Shutdown();

    return 0;
}
```

---

## 🔨 Compilé avec CMake

Voici un exemple de fichier **CMakeLists.txt** pour compiler BintjeKit :

```cmake
cmake_minimum_required(VERSION 3.26)
project(BintjeKit LANGUAGES CXX)

# Modules en C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

# Ajout de bibliothèques
add_library(BintjeKit STATIC
    Core/Core.cppm
    Core/Factory.cppm
    Window/Window.cppm
    Tools/Tools.cppm
)

# Indique que nous utilisons les modules
target_precompile_headers(BintjeKit PRIVATE Core/Core.cppm)

# Ajout des dépendances externes
find_package(spdlog REQUIRED)
target_link_libraries(BintjeKit PRIVATE spdlog::spdlog)
```

---

## 🚀 Fonctionnalités futures (idées)

1. **Renderer** : Ajout d'un module de gestion graphique (par ex. OpenGL, Vulkan).
2. **Math Utilities** : Fournir des outils pour gérer des vecteurs, matrices, transformations, etc.
3. **IO Module** : Ajouter des fonctionnalités pour la gestion des fichiers et ressources.
4. **Documenter avec Doxygen** pour une meilleure intégration.

---

## 📜 Licence

BintjeKit est distribué sous [MIT License](LICENSE).

