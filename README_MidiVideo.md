# 🎛️ MidiVideo

**MidiVideo** est une application modulaire et légère, écrite en C, qui permet: 

- la lecture précise de vidéos MP4 à 25 fps,
- l’interaction en temps réel avec des événements MIDI (note et contrôleurs),
- l’affichage d’effets visuels simples avec SDL2,

## 🧱 Structure du projet

midivideo/
├── include/
│   ├── core/        # définitions principales
│   ├── ffmpeg/      # en-têtes pour la gestion vidéo
│   ├── midi/        # en-têtes pour le MIDI
│   ├── sdl/         # rendu graphique avec SDL
│   ├── userinput/   # gestion clavier / événement midi
│   └── ui/          # (à venir) mini interface
├── source/
│   ├── core/        # moteur principal
│   ├── ffmpeg/      # lecture vidéo
│   ├── midi/        # traitement MIDI
│   ├── sdl/         # effets visuels
│   ├── userinput/   # gestion clavier / Midi
│   └── ui/          # (à venir) interface utilisateur
├── Makefile
└── README.md


## ⚙️ Dépendances

```bash
sudo apt install
 libsdl2-dev libavformat-dev libavcodec-dev libavutil-dev libportmidi-dev

## 🧠 Fonctionnement

**MidiVideo** 
Les notes midi déclenchent la lecture ou des effets simples ou les deux 
(Notes in lecture frames  notes off lecture off) ce peut être des controleurs .

### 🎹 Gestion MIDI :

- `Note On` → déplace la lecture vidéo à une **frame correspondant
     au numéro de note** (ex. : note 60 = frame 60).
- `Note Off` → **arrête la lecture** à la frame en cours.
- Les **10 dernières notes MIDI** (note 117 à 127) sont réservées
     au déclenchement d'**effets visuels simples** (cercles, ondes, etc.).
- Une **table de correspondance MIDI → frame** sera bientôt
         chargée depuis un fichier externe pour éviter le codage en dur.

## 🚀 Utilisation

```bash
make
./midivideo
```
- Prochainement : en **fenêtré auto-adapté à la vidéo**, avec **UI minimale**.

## 🎬 Lecture vidéo

- Format recommandé : **MP4 encodé en H.264**
- Utilisation de **FFmpeg/libav** pour la lecture image par image.
- Optimisé pour un usage **en live**.

## 🔧 Fonctionnalités à venir

- 🔳 **Mini interface utilisateur** (fenêtré, adaptable à la vidéo).
- 📄 Fichier de configuration **MIDI → frame** externe.
- 🎛️ Simplification de l’interaction en live

## 👤 Auteur

Développé par **JM** salut :) 

Un projet né pour la scène, pensé pour être modulaire, rapide, et autonome.

Cet outil était pour mes besoins scéniques 
sous linux et un ordi deporté portable à 100 balles
géré en entrée midi via live ableton .

to be conitued ....
