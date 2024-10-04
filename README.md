> [!NOTE]
> code non testé pour l'instant !

# servo-midi-music

l'objectif est d'avoir un code pour actionner des servomoteurs en utilisant des cartes pca9685 a partir de messages midi recu via usb.  
Tout les reglages seront regroupé dans le fichier settings.h. (le nombre de servo a utiliser, les angles de servo, parametres de controle des servo pour le pca, le type de gamme utilisé, etc.  )  
La gestion des servomoteurs est dynamique et peut s'adapter à différents nombres de notes grâce à l'utilisation de plusieurs PCA9685 en fonction du besoin.  
les servomoteurs seront branché en commencant avec la note la plus grave sur le pin 0 du premier pca utilisé, la seconde note sur le pin 1 du pca et ainsi de suite 
<img src="https://github.com/glloq/servo-midi-music/blob/main/img/SchemaElec.png" alt="pluck" width=100% height=100%/>  
Pour limiter le bruit des servomoteurs nous utiliserons la broche OE des pca pour desactiver l'alimentation des servomoteurs lorsqu'ils ne sont pas utilisé


# applications

il y a 3 types d'actions pour les messages notesOn/noteOff :
- le grattage => le servo alterne en + /- un certain angle de grattage pour une noteOn et revient a la position zero a une noteOff
- l'activation => le servo se deplace d'un certain angle a noteOn et revient a la position zero a une noteOff
- Impulsion => le servo se deplace d'un certain angle a noteOn et revient a la position zero après un certain temps

## ServoPluck
ce codes et contruit pour gratter des cordes (lyre, harpe,etc) ou autres systeme de grattage et viendra alterner le sens de grattage a chaque message noteOn.  
<img src="https://github.com/glloq/servo-midi-music/blob/main/img/grattage.png" alt="pluck" width=40% height=40%/>  

Il suffit d'adapter les reglages suivant dans settings.h :
- le nombre de servo utilisé ( NUM_SERVOS ) 
- le type de gamme utilisé ( DIATONIC_OCTAVE a 1 si on utilise un accordage diatonique et a 0 si chromatique)
- les angles d'initialisation des servomoteurs ( dans le tableau  initialAngles[] )
- l'angle de grattage des servomoteurs ( PLUCK_ANGLE )

## ServoOnOff

ce codes et contruit pour actionner le servomoteur dans un sens a la reception d'un message midi noteOn puis remet le servomoteur a la position initale a la reception d'un message noteOff  
<img src="https://github.com/glloq/servo-midi-music/blob/main/img/OnOff.png" alt="OnOff" width=30% height=30%/>  

Il suffit d'adapter les reglages suivant dans settings.h :
- le nombre de servo utilisé ( NUM_SERVOS ) 
- le type de gamme utilisé ( DIATONIC_OCTAVE a 1 si on utilise un accordage diatonique et a 0 si chromatique)
- les angles d'initialisation des servomoteurs ( dans le tableau  initialAngles )
- le sens pour l'action du servomoteur ( dans le tableau DirectionServo[] )
- l'angle de grattage des servomoteurs ( PLUCK_ANGLE )
  

## ServoImpulsion

ce codes et contruit pour actionner le servomoteur dans un sens a la reception d'un message midi noteOn puis remet le servomoteur a la position initale après un certain temps defini dans settings.h  
les parametres sont les meme que dans le code pour ServoOnOff avec le temps d'impulsion avant de remettre de servo a sa position initale (TIME_IMPULSION) 
  

# Calibration des servomoteurs

Afin de simplifier l'utilisation des code il est possible d'utiliser le code dans le fichier calibration afin de connaitre les position de chaque servomoteurs.
Il suffit de renseigner le nombre de servomoteur utilisé puis d'uploader le code dans l'arduino.   


on pourra modifier la position de chaque servomoteur l'un après l'autre depuis la console serial de l'IDE arduino, une fois que tout les servomoteurs seront initialisé, il faudra copier coller le tableau des angles dans le fichier settings.h utlisé 
