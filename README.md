# servo-midi-music
use arduino and pca9685 with servomotor to play midi message on instrument

Servo Pluck Instrument

Ce projet implémente un instrument de musique électronique contrôlé par un Arduino Leonardo. L'instrument utilise des servomoteurs pour simuler le mouvement des cordes en réponse aux messages MIDI, permettant une reproduction précise des notes.
Principales caractéristiques :

    Structure modulaire : Le code est organisé en trois classes principales - Instrument, MidiHandler, et ServoController - pour une gestion claire et modulaire.
    Servomoteurs contrôlés par PCA9685 : Les 16 servomoteurs sont contrôlés par un seul PCA9685, facilitant le câblage et la gestion.
    Gestion des notes : L'instrument prend en charge les messages MIDI Note On et Note Off, permettant une expérience de jeu réaliste.
    Adaptabilité au nombre de notes : La gestion des servomoteurs est dynamique et peut s'adapter à différents nombres de notes grâce à l'utilisation de plusieurs PCA9685 en fonction du besoin.

Structure du code :

    settings.h : Contient les paramètres du projet, tels que les angles de servo, les adresses PCA9685, etc.
    MidiHandler : Gère la réception des messages MIDI et les transmet à l'instrument.
    ServoController : Contrôle les servomoteurs, initie les positions, et gère le grattage des cordes.
    Instrument : La classe principale qui interagit avec les autres classes pour gérer les événements MIDI et contrôler les servomoteurs.

Utilisation :

    Téléchargez et installez les bibliothèques nécessaires : MIDIUSB et Adafruit_ServoDriver et MIDIUSB
    Connectez les servomoteurs au PCA9685 selon la configuration spécifiée dans settings.h.
    Alimentez l'Arduino Leonardo et téléversez le code.
    Contrôlez l'instrument en envoyant des messages MIDI depuis un logiciel ou un contrôleur MIDI.
