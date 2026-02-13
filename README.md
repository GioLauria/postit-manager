# Gestore Post-It

Un'applicazione grafica scritta in C per gestire post-it virtuali. Permette di aggiungere, visualizzare, modificare ed eliminare post-it, con salvataggio persistente su file.

## Funzionalità

- Aggiungere nuovi post-it con titolo e contenuto
- Visualizzare tutti i post-it in una lista
- Modificare post-it esistenti selezionandoli dalla lista
- Eliminare post-it selezionati
- Salvataggio automatico su file alla chiusura

## Compilazione

Assicurati di avere GCC (MinGW su Windows) installato. Poi:

```bash
make
```

## Esecuzione

```bash
./postit_manager
```

Si aprirà una finestra grafica con l'interfaccia per gestire i post-it.

## Struttura del progetto

- `main.c`: Punto di ingresso dell'applicazione (WinMain)
- `postit.h`: Header con definizioni e prototipi per la gestione dei post-it
- `postit.c`: Implementazione delle funzioni per caricare, salvare e manipolare i post-it
- `gui.c`: Codice per l'interfaccia grafica Windows
- `Makefile`: Script per la compilazione
- `postits.txt`: File di salvataggio (generato automaticamente)

## Requisiti

- GCC con supporto Win32 API (MinGW su Windows)
- Sistema operativo Windows

## Licenza

Questo progetto è distribuito sotto licenza MIT.