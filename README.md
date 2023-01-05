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
     
## How you are breaking down the project and who is responsible for which parts.
  
## What data structures you will be using and how.
     
## What algorithms and /or data structures you will be using, and how.
    
# A timeline with expected completion dates of parts of the project.
