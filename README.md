# Gestore Post-It

Un'applicazione semplice scritta in C per gestire post-it virtuali. Permette di aggiungere, visualizzare, modificare ed eliminare post-it, con salvataggio persistente su file.

## Funzionalità

- Aggiungere nuovi post-it con titolo e contenuto
- Visualizzare tutti i post-it
- Modificare post-it esistenti
- Eliminare post-it
- Salvataggio automatico su file `postits.txt`

## Compilazione

Assicurati di avere GCC installato. Poi:

```bash
make
```

## Esecuzione

```bash
./postit_manager
```

## Struttura del progetto

- `main.c`: Codice principale dell'applicazione
- `Makefile`: Script per la compilazione
- `postits.txt`: File di salvataggio (generato automaticamente)

## Requisiti

- GCC o un compilatore C compatibile
- Sistema operativo con supporto per file I/O

## Licenza

Questo progetto è distribuito sotto licenza MIT.