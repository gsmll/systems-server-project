# LezHangum!

# Gabriel Small, Jawad (Jamie) Sifat
        
## Project info

A multiplayer, network-based hangman, with various players with realtime gameplay (TCP). This will consist of a server host and clients for each player (dynamic).
 
## A description as to how the project will be used (describe the user interface).

- The host starts the hangman server

- Players connect to the server lobby via the hangman client which itself is a TUI 
interface for interacting with the server.

```bash
$ lezhangum                                      # Starts the server
$ lez-join --name Geek-Smasher --server <Server> # Client connects to server based on serverID 
```

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
|    Players: Stack-Smasher, ThiccTux, HOpleSS           |           
|                                                        | 
|    INPUT: |CHARACTER| |WORD|                           |
|    -----------------------------                       |
|       [INPUT FIELD]                                    |
|     ----------------------------                       |
_________________________________________________________
```
    
## How you will be using the topics covered in class in the project.
   We will be using...
   - Forking for the host and client relations.
   - Sockets for tcp connections to send hangman answers and results.
   - Memory allocation for almost all of the information, such as guesses, players, and words. 
   - Signals to handle closed clients and leaving players.
   - files for list of words such that the server can choose word to guess and a `.conf` file for configuration.
    
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
```
`termbox.h`: A suckless TUI library based on a simple abstraction

[Suckless](https://suckless.org/philosophy/) (adj. ) - Simple, concise, fast, and memory safe with minimal dependencies. 

### Why SUCKLESS termbox2 and not ncurses
ncurses is a very old library that was used to build a lot of TUI applications
in the Linux userspace. However, ncurses itself is not part of clib and is 
an external library with its own set of issues and flaws. Termbox2 is a 
suckless successor. 

Termbox2 defines the terminal screen as a grid of cells. It supports UTF-8 characters and
has more robust error checking than libcurses. The source code is small and can easily 
be emedded into other projects (like this one)!
 
### Game/Server logic
At most I believe we'll just understand if a character is in a string as the 
most algorthimically intensive task. 

Networking is just *slightly* more complicated, though we will be using a TCP protocol.

On other note, temporary files will be used for storage of guesses and characters. tmp files allow us to encode gamestate outside of the process. Here's a small synopsis of game state.

```
# On server startup
1. Open a file that contains all the possible words that the hangman game can use.
2. Pick a random word from that file (DO NOT READ THE FILE INTO RAM, just the word)
3. set up gamestate files (i.e. guesses, players, hangman health, etc.)
4. Create a lobby for clients to conenct to. 
5. Appoint a 'host' for the game (i.e. the person who connected first to the server)
6. Host prompts the server to start the game once all the players have connected.

# In a single turn (player move): 

1. Player will either guess a letter or a word. 
----> user_input will be placed into temporary files, this is to ensure greater parity with
the networking portion of the project.

----> In essence, the gamestate will be determined by files and not internal program memory.
2. Game interprets that input (via reading the file) and updates game state (hangman health, revealed characters)
3. Turn will pass to next player (a wrap-around queue).

# On Gameover
The gameover state is defined by if the Hangman health reaches 0, or the word has been
guessed. The server will then dq all the clients and then create a new lobby and wait
for connections
```




# A rough timeline with expected completion dates of parts of the project.
- 1-9 network and host basic functionality
- 1-11 base game functionality
- 1-15 graphic part of game
- 1-17 extra stuff
