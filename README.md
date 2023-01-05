# LezHangum!

# Gabriel Small, Jawad (Jamie) Sifat
        
## Project info

A multiplayer, network-based hangman, with various players in realtime. This will consist of a server host and clients for each player (dynamic).



    
## A description as to how the project will be used (describe the user interface).

- The host starts the hangman server

- Players connect to the server lobby via the hangman client which itself is a TUI 
interface for interacting with the serve.

- Once the server starts the hangman game, no other players can join in. Players
who disconnect will be marked as 'left'. Players send responses to the server
via the TUI interface in turns. The server updates state accordingly based on the
player guess (reveal letters, end the game, etc)

- Once the game is finished (via gameover or the word was guessed), the server will
disconnect all clients and start up a new hangman lobby, in which all the clients
will have to reconnect. 


```
_________________________________________________________
|       HANGMAN-ART         _ _ _ _ _ _ _                | 
|                                                        |  
|       LETTERS GUESSED: ' ' ' '                         | 
|       WORDS GUESSED:                                   | 
|                                                        |
|    Players: Geek-Smasher, A-Real-Life-GNU, HOpleSS     |           
|                                                        | 
|    INPUT: |CHARACTER| |WORD|                           |
|    -----------------------------                       |
|       [INPUT FIELD]                                    |
|     ----------------------------                       |
_________________________________________________________
```
## A description of your technical design. This should include:
   
   
## How you will be using the topics covered in class in the project.
   We will be using forking for the host and client relations.
   We will be using sockets for tcp connections to send hangman answers and results.
   We will allocate memory for almost all of the information, such as guesses, players, and words. 
   We will use signals to handle closed clients and leaving players.
   We will use file for list of words such that the server can choose word to guess.
   
     
## How you are breaking down the project and who is responsible for which parts.
  Jamie is responsible for visuals and game mechanics -- CLIENTS
  
  Gabriel is responsible for networking and file management -- HOST

## What implementations/data structures will be using. 

`utiltype.h`: A header file that defines these types and MACROS
```C
/* From <stdint.h> / <utiltype.h> */
u8  - unsigned  8  bit decimal
u16 - unsigned 16  bit decimal
u32 - unsigned 32  bit decimal
u64 - unsigned 64  bit decimal

i8  - signed  8  bit integer
i16 - signed 16  bit integer
i32 - signed 32  bit integer
i64 - signed 64  bit integer

str - A pointer to a buffer of unsigned 8 bit decimals (unsigned char).

/* From <stdbool.h> */
bool - A truth value

#include <termbox.h>
- A library for writing text-based interfaces based on a simple abstraction

``` 
At most I believe we'll just understand if a character is in a string as the 
most algorthimically intensive task.

# A timeline with expected completion dates of parts of the project.
- 1-9 network and host basic functionality
- 1-11 base game functionality
- 1-15 graphic part of game
- 1-17 extra stuff
