# 🐍 Snake en console

Refonte du jeu classique **Snake**, jouable directement dans la console Windows, en C/C++.

## 🎮 Jeu

- Diriger le serpent avec les **flèches du clavier** ↑ ↓ ← →
- Chaque pomme mangée rapporte **10 points**
- Toutes les **3 pommes**, le serpent grandit d'un segment
- La partie s'arrête si le serpent touche un mur ou sa propre queue

Affichage façon écran LCD (texte vert) avec un cadre ASCII, score et compteur de pommes.

## 🛠️ Technologies

C / C++ · API console Windows (`windows.h`, `conio.h`)

## 🚀 Compiler et jouer

> Le jeu utilise des fonctions propres à Windows, il faut donc le compiler **sous Windows**.

**Avec MinGW (g++) :**
```bash
g++ snake.cpp -o snake.exe
./snake.exe
```

**Avec Visual Studio :** créer un projet console, ajouter `snake.cpp`, puis compiler et exécuter.

`Snake.zip` contient le projet d'origine complet.

## 👤 Auteur

**Idir Sehrane**
