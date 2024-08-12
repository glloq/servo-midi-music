> [!NOTE]
> pas fini!


# servo-midi-music

l'objectif est d'avoir jusqu'a 5 pca9685 donc un total de 80 servomoteurs qui peuvent etre utilisé pour actionner des cordes ou autres mecanismes afin de faire la note demandé.
chaque servomoteur sera initialisé a sa position "noteOff" et le deplacement se fera a la reception d'une noteOn.

# applications
l'objectif principal etait ce controller une lyre ou harpe mais ce code est adaptable a beaucoup d'autre cas d'utilisations

#  Servo Pluck Instrument

## Principales caractéristiques du code:

Structure modulaire : 
Le code est organisé en trois classes principales 
- Instrument
- MidiHandler
- ServoController
  
Adaptabilité au nombre de notes : La gestion des servomoteurs est dynamique et peut s'adapter à différents nombres de notes grâce à l'utilisation de plusieurs PCA9685 en fonction du besoin.

## Structure du code :

settings.h : Contient les paramètres du projet, tels que les angles de servo, les adresses PCA9685, etc.
MidiHandler : Gère la réception des messages MIDI et les transmet à l'instrument.
ServoController : Contrôle les servomoteurs, initie les positions, et gère le grattage des cordes.
Instrument : La classe principale qui interagit avec les autres classes pour gérer les événements MIDI et contrôler les servomoteurs.

## Utilisation :

Téléchargez et installez les bibliothèques nécessaires : MIDIUSB et Adafruit_ServoDriver et MIDIUSB
Connectez les servomoteurs au PCA9685 selon la configuration spécifiée dans settings.h.
Alimentez l'Arduino Leonardo et téléversez le code.
Contrôlez l'instrument en envoyant des messages MIDI depuis un logiciel ou un contrôleur MIDI.
