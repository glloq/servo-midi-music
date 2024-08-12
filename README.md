> [!NOTE]
> pas fini!


# servo-midi-music

l'objectif est d'avoir jusqu'a 5 pca9685 donc un total de 80 servomoteurs qui peuvent etre utilisé pour actionner des cordes ou autres mecanismes afin de faire la note demandé.
chaque servomoteur sera initialisé a sa position "noteOff" et le deplacement se fera a la reception d'une noteOn.

# applications
l'objectif principal etait ce controller une lyre ou harpe mais ce code est adaptable a beaucoup d'autre cas d'utilisations.  
Le code est capable de jouer un instrument chromatique ou diatonique en indiquant simplement le numero midi de la note la plus grave, le type d'accords et le nombres de servo/cordes disponible (puis le reglage de l'angle NoteOff de chaque servo)  
  
il y a deux type d'actions pour les messages notesOn/noteOff :
- le grattage => le servo alterne en + /- un certain angle de grattage pour une noteOn et revient a la position zero a une noteOff
- l'activation => le servo se deplace d'un certain angle a noteOn et revient a la position zero a une noteOff

#  Servo Pluck Instrument

## Principales caractéristiques du code:

Le code est organisé en trois classes principales 
- Instrument : La classe principale qui interagit avec les autres classes pour gérer les événements MIDI et contrôler les servomoteurs.
- MidiHandler : Gère la réception des messages MIDI et les transmet à l'instrument.  
- ServoController : Contrôle les servomoteurs, initie les positions, et gère le grattage des cordes.  

Tout les reglages seront regroupé dans le fichier settings.h. (les angles de servo, les adresses PCA9685, etc.  )
  
La gestion des servomoteurs est dynamique et peut s'adapter à différents nombres de notes grâce à l'utilisation de plusieurs PCA9685 en fonction du besoin.

## Utilisation :

Téléchargez et installez les bibliothèques nécessaires : MIDIUSB et Adafruit_ServoDriver et MIDIUSB  
Dans settings :
 - Reseigner la premiere note midi (FIRST_MIDI_NOT )
 - mettre DIATONIC_OCTAVE a  1 si vous utiliser un accordage diatonique a 0 si chromatique
 - renseigner le nombre de corde/note midi jouable (NUM_SERVO) et l'angle "zero" pour chaque servomoteur dans le tableau initialAngles[]
   
Connectez les servomoteurs au PCA9685 selon la configuration spécifiée dans settings.h. (de la plus grave a la plus aigue)
Alimentez l'Arduino Leonardo et téléversez le code.  
Adapter l'angle des servomoteurs pour initialiser 
Contrôlez l'instrument en envoyant des messages MIDI depuis un logiciel ou un contrôleur MIDI.  
