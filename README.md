# Informatik_Praesentation
Der Code zu meiner Präsentation in Informatik. Die meisten Funktionen sind kommentiert, außer Get- und Set- Funktonen, das diese klar sind.
Beschrieben ist hauptsächlich in den Source-Files.

Zum kompilieren auf Windows:  
  Benötigt wird:  
    gcc / g++ (Am besten g++)  
    make  
    
  Am besten installiert man diese Programme mit Msys2 und MingW.  

  Sobald alles installiert ist muss man noch die entsprechenden Bibliotheken hinzufügen.
  Dazu lädt man sie bitte herunter (Bei Releases auf die zip für windows-x64 drücken dann entsprechend in die src Ordner reinlegen):
  
  SDL: (letzte 2. Version) https://github.com/libsdl-org/SDL/releases  
  SDL_image: (für SDL2) https://github.com/libsdl-org/SDL_image/releases  
  SDL_ttf: (für SDL2) https://github.com/libsdl-org/SDL_ttf/releases  

  Sobald alles in den richtigen Ordnern ist, noch die dll Dateien in build hinzufügen.
  Dann öffnet man den Ordner wo die Makefile ist in der Kommandozeile und gibt ein:
  ```
  make
  ```

Dieser Code ist nur ein PROTOTYP. Es ist kein Programm, dass professionel zu Stande gekommen ist und bietet daher keine große Qualität. Einige Dinge sind noch sehr umständlich geschrieben jedoch dadurch einfacher zu verstehen.
