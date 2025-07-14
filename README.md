# Hangman on arduino
This is a little hangman game coded for the arduino using an 16x2 lcd display.

Required Material:
- 1x Arduino
- 1x USB type-B cable
- Jumper wires
- 1x Button
- 1x 1k potentiometer
- 1x 10k potentiometer
- 1x 220 omhs resistance
- 1x 10k omhs resistance
- 1x Breadboard
- 1x 16x2 LCD HD47780 compatible

How to play:
Roll the potentiometer on the right to select a letter, shown at the bottom left then hit the bottom. That letter will be marked with and 'X', if that letter is in the word, every occurence of this letter will be revealed on the hidden word on the first row, otherwise the counter at the bottom right will increase. If the word is completed you win, and if you run out of tries you lose. The answer is revealed if you lose. Then the game restart with a new word.

Notes:
Other values of potentiometers might be used but might need changes in the code.
Base LCD setup from arduino documentation : 
  https://docs.arduino.cc/learn/electronics/lcd-displays/

Images:

<img width="1498" height="789" alt="image" src="https://github.com/user-attachments/assets/21cbdf81-1dd5-48aa-bc3b-223b0c534e93" />
![arduinoHangmanPic](https://github.com/user-attachments/assets/8fdb1893-4d62-40e0-b7ee-b72b822b4706)
