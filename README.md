# Projet - 8INF935

Membres du Groupe :

- Alaoui, Mohamed-Wajih
- Delort, Tristan
- Miras, Lucas

## Build & Run

```sh
mkdir build && cd build
cmake ..
cmake --build .
cd Debug/
./PhysicsEngineTests.exe ../../teapot.obj
```

## Bibliothèque externes

Les bibliothèques suivantes ont du être ajoutées pour le bon fonctionnement du programme :

- **GLFW** pour la gestion des events et des fenetres.
- **ImGUI** pour créer une interface utilisateur graphique (en utilisant les bindings *imgui_opengl3* et *imgui_glfw*
- **OpenGL** pour effectuer le rendu 3D (pour l'instant c'est une projection orthographique simple)
- **GLM** pour créer des matrices pour OpenGL
- **GLAD** pour pouvoir loader les fonctions OpenGL3 pour pouvoir les utiliser dans le programme.
