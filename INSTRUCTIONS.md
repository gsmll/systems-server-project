# Instructions

Instructions:

1. Run `make` to generate both the client and server executable
2. Start the server and input a word.
3. Clients can now be executed and be given a IPV4 address (or localhost) and port (54321)
4. Follow game rules as shown on the screen.


Known Bugs:
- Acts wonky around the first and last letters of the guessing word. Sometimes it picks up a match
and sometimes it doesn't. Undefined behavior mostly.

- Undefined behavior also occurs when entering a word that is capitalized or contains capitalized letters

- When the game ends, the server does not immediately terminate itself. 

- If you give the server a blank word, then it will accept it without question. 

- Double letters that are seperated by a character (ex: cocaine), will exhibit undefined behavior
