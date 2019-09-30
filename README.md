# COSC345 Year Long Project - 8 Ball Pool

An 8 ball pool game which follows the concept of 'Small Is Beautiful'. We are aiming to create a program which is very lite, challenging, but enjoyable to play. Our game is for offline play, allowing for local player versus player mode. ~~a puzzle trickshot 
mode.~~

---
## Prerequisites:

Our team is currently building this project using the C++ language on Windows(x86) based computers. However we will supply instructions on how to build our project in both Windows(x86) and MacOS(x64). We include the [SFML](https://www.sfml-dev.org/) libraries for both Windows and MacOS versions of our project.

For MacOS you will require to have [Xcode](https://itunes.apple.com/nz/app/xcode/id497799835?mt=12) installed.

For Windows you will require to have [Make](https://www.gnu.org/software/make/) installed, and have [Visual Studio Code setup with MinGW.](https://code.visualstudio.com/docs/cpp/config-mingw)

---
## Installing:

### For MacOS Users:

**_Please note that these instructions are for Mac users using the Xcode IDE._**

**_We will assume you have [Xcode installed](https://itunes.apple.com/nz/app/xcode/id497799835?mt=12) on your computer._**

**Step1:**

Clone or download this Github repository to your local computer.

**Step2:**

*If you have cloned the repository, skip to Step3*

Move zip file to desired directory and unzip.

**Step3:**

Navigate through the project directory to the Apple_Build directory which contains the Xcode project file *Apple_Build.xcodeproj*
```
345-master/Apple_Build/Apple_Build/Apple_Build.xcodeproj
```
Then open the *Apple_Build.xcodeproj* with Xcode.

**Final Step:**

Once open, to build the project, press the build and run button (Located top left of the Xcode project window).

_A new window will pop up with the application running._

To stop the application from running, return to the Xcode project window and press the stop button which is next to the run button.

**NB: If you edit the code, you will need to clean the build folder before building the project again for it to run.
This can be done by using the following keyboard shortcut:**
```
Command + Alt + Shift + k
```
---
### For Windows:

***We will assume you have properly installed [Make](https://www.gnu.org/software/make/) and [setup Visual Studio Code with MinGW.](https://code.visualstudio.com/docs/cpp/config-mingw)***

**Step1:**

Clone or download this Github repository to your local computer.

**Step2:**

*If you have cloned the repository, skip to Step3*

Move zip file to desired location and unzip.

**Step3:**

Open the command prompt and navigate to the project source directory.

**Final Step:**

Once in the project directory, you should now be able to build the program by entering:
```
make
```
and then run the program by entering:
```
app
```
**NB: If you edit the code, you will need to re-build the project before running it again (_Repeat the final step_)**

---
### Running the program:

The program takes inputs from the keyboard and a mouse.
Once run, you will be presented with a start menu screen.
```
Player 1 | Depicted by red triangles on the cue.
Player 2 | Depicted by blue triangles on the cue.
```

#### Here is a list of input keys for our program:
```
Mouse left click & drag | Changes direction of the cue on the cue ball.
Up/Down Arrow Keys      | Changes the power input of the shot.
Spacebar                | Initiates the shot to be made.
R                       | Resets the game state to the start state.
```
#### Exiting the program can be done by pressing:
###### On Windows:
```
alt + f4
Exit button from start menu screen.
```
###### On Mac:
```
Pressing the stop button on the Xcode project window.
Exit button from start menu screen.
```

---
### Game functionality:
###### The game window currently displays:
```
Player      | Which player turn it is.
Suit        | The players suit.
Remaining   | Number of player balls remaining on table.
```
~~*__NB: The current version of our game will display 'Remaining: Black' after all balls have been sunk for the player. This is not a bug, but an intentional "feature" of sorts at this stage.__*~~

###### Currently implemented game rules:
- Player one initiates the break.
- Sinking a ball will initialise the players suit (solids or stripes).
- If two balls of different suits are sunk in a single turn:
    - The suit of the first ball sunk will be chosen as the players suit.
    - Player ones turn ends.
- Each player turn ends if they sink an opponents ball or the cue ball.
- Each player turn continues if they sink a ball of their own suit.
- If the black ball is sunk prior to sinking the remain players balls, then 'Loser' is printed to the console.
- If the black ball is sunk after sinking the reamining players balls, then 'Winner' is printed to the console.
- While the table has the cue ball and black ball remaining, if the white ball is sunk, then 'Loser' is printed to the console.

~~*__NB: The current version of our game will continue to allow the players to play until only the cue ball remains. This is not a bug, but an intentional "feature" of sorts at this stage.__*~~

---
## Testing:

Our code base is currently too small for any automated testing to be implemented.

---
## Coding Style:

We will be coding our program following the K & R standard layout. 
```C++
void checknegative(x) {
    if (x < 0) {
        puts("Negative");
    } else {
        nonnegative(x);
    }
}
```
---
## Source Code Breakdown:

Using SFML a program window, a rectangle table shape, sockets, and cushions are created.
* Main()
    - Contains the main game loop which performs different functions depending on the game state.
    - After a single tick of the game loop, the method draws the graphical components.
        - Certain SFML graphical objects will be drawn dependant on the game state.
   
* PlayerManager()
    - Handles user inputs.
        - Aiming input for the cue ball via mouse.
            - Cue ball aimer displays trajectory of the shot.
        - Input for placement of the cue ball via key press.
        - Power level of the shot via key press.
        
* GameManager()
    - Initialises all the objects to the game screen at their default positions and initialises UI elements.
    - Contains placeholder methods for winning and losing states.
    
    ballSunk():
    - Function which handles the game state when a ball is sunk.
        - Assigning suits to the players.
        - Issuing fouls if a player makes an illegal move.
        - Removes balls from the table if sunk.
        - Decrements counter for how many balls each player has remaining.
        
    swapPlayer():
    - Called to determine which player will have the next shot.
        - Dependant on the ballSunk():
            - Whether there has been a foul or not.
            - Whether a correct ball has been sunk or not.

* MovementManager()
    - moveTick():
        - Sets the velocity of the cue ball (The distance between the cue and the cue ball).
        - Loops through all of the balls remaining on the table.
            - If balls are moving, calls collisionCheck() and ballMove() methods.
        - Keeps track of the current moving balls.
        - Ends turn when all balls are stationary.
       
    - ballMove():
        - Calculates movement of ball based on acceleration and velocity.
        - Uses DeltaTime for synchronous movement speed.
          
    - collisionCheck():
        - Checks a given ball against all other balls for collision.
        - Checks a given ball against the sockets of the table for collision.
          
* Ball() & Player()
    - Classes used for holding data.
    
* Physics()
    - boxCollision():
        - Loops through an array of lines (edges of the cushions).
        - Calculates whether a ball is colliding with the line.
        - Changes the balls velocity appropriately.
    - ballCollision():
        - Handles collisions between balls.
        - Displaces each colliding ball by the amount of overlap which they collide with.
        - Changes the balls velocity appropriately.
        
    - cushionCollision():
        - Handles collisions between the balls and the cushions.
        - Creates a temporary ball at the x & y coordinates of the collision.
        - Calls the ballCollision() with the ball and temporary ball.
        
    - overLapDetection():
        - Places the cue ball (checks whether if it has collided with another ball).
    
        
---
## Built With:

* [Visual Studio Code](https://code.visualstudio.com/) - IDE for Windows
* [SFML](https://www.sfml-dev.org/) - External GUI Library (Both Windows and MacOS)
* [MingW](http://www.mingw.org/) - Minimalist GNU for Windows
* [Make](https://www.gnu.org/software/make/) - GNU Make application for Windows
* [Xcode](https://itunes.apple.com/nz/app/xcode/id497799835?mt=12) - IDE for MacOS

---
## Version:

Final release.

---
## Project Changes:
**__ Final release changes: __**
* Addition of mouse input
    - Testing using the keyboard controls for the cue direction proved to be too difficult and inaccurate for aiming.
    - We have implemented a mouse input which allows for left click and dragging the cue around the cue ball in order to aim.
* Cue alterations and aimer
    - The cue will display red or blue triangles to represent each player during their turn.
    - Power can be set pior to aiming or after aiming.
    - The aimer has been implemented to rotate smoothly around the cue ball
* Fixed physics overlap collisions with walls
    - Ball collisions and movement look and interact realistically.
* Physics for ball-pocket interactions
    - The pocket interaction with incoming balls required specific implementation to account for the various angles of which the ball could collide with.
* Addition of sprites and textures
* Removal of Trickshot levels.
    - After encountering difficulties from prior to the Beta release, we regrettably had to exclude the trickshot functionality due to continuous errors and due to our imposed line contraint of 1000 lines of code. 

**__ Beta release changes: __**
* Refactoring of code
    - The code in our Alpha release was very primitive and lacked proper structure.
    - We have refactored it to provide code that is easier to read.
    - Refactoring of the code has also improved the performance of our program due to improvements on the execution of our methods.
* Delayed trickshot levels
    - We have had to delay implementation of our trickshot levels due to major bugs when attempting to implement physics with our environments.

**__ Alpha release changes: __**
* Removal of AI
    - We decided to remove the AI feature as it was too ambitious for us to implement into our project while remaining under our limit of 1000 lines of code.

---
## Authors:

* **Liam Chapman**
* **Calum Hunter**
* **John Kim**

---
## License:

Current there is no license, but if required we will use the MIT License.

---
## Acknowledgments:
* Used javidx9's [youtube tutorial](https://www.youtube.com/watch?v=LPzyNOHY3A4) as a reference in creating circle collisions.
* [Arial font](https://github.com/JotJunior/PHP-Boleto-ZF2/blob/master/public/assets/fonts/arial.ttf) from JotJunior's github
* Used Ivan Voirol's [tileset](https://opengameart.org/sites/default/files/Slates%20%5B32x32px%20orthogonal%20tileset%20by%20Ivan%20Voirol%5D.png) for sprite creation.
* COSC 345 Lecture slides
* *Many thanks to Google.*
* *Shout out to caffeine.*
