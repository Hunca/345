# COSC345 Year Long Project - 8 Ball Pool

An 8 ball pool game which follows the concept of 'Small Is Beautiful'. We are aiming to create a program which is very lite, challenging, but enjoyable to play. Our game is for offline play, allowing for local player versus player, and a puzzle trickshot 
mode.

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

The program takes inputs from the keyboard and will not require the use of a mouse.

Player one  | depicted as a black circle when aiming.

Player two  | depicted as a magenta circle when aiming.

#### Here is a list of input keys for our program:
```
Left/Right Arrow Keys   | Changes direction of the cue on the cue ball.
Up/Down Arrow Keys      | Changes the power input of the shot.
Spacebar                | Initiates the shot to be made.
R                       | Resets the game state to the start state.
```
Exiting the program can be done by pressing:
#### On Windows:
```
alt + f4
```
#### On Mac:
```
Pressing the stop button on the Xcode project window.
```
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

Using SFML a program window and a rectangle table shape is created.
* main()
    - Draws the table shape onto the window.
    - Creates an array of ball objects.
        - The ball constructor initialises each object with an ID number, radius, and initial positions.
            - Gets positions of the ball objects through a preset array of vector positions.
            - The cue ball and 8 ball are coloured white and black
            - Ball objects with ID value that are not the cue ball and 8 ball are coloured accordingly 
    - Sets up the cue (aimer) around the cue ball.
    - Begins the game loop
    - Runs playerTurn():
        - Takes in keyboard input (arrow keys) to set direction and power of the cue ball.
        - If spacebar is pressed, takes the vector value of the cue and then runs the moveBall() method.
    - moveBall():
        - Takes in the ball ID, the velocity of the cue ball. 
        - Sets the velocity of the cue ball (The distance between the cue and the cue ball).
        - Method loops through while balls are moving.
        - Loops through every ball, ignoring those with 0 velocity (Balls that dont move).
        - Checks to see if any balls hits a wall, if so, bounce off at the opposite angle.
        - Changes the speed of the balls with given friction (drag).
        - Checks against all other balls to see if there is collision.
            - If so, updates both collided balls' velocities.
        - When balls slows down to a certain velocity, stop the ball movement.
* main()
    - Once all the balls stop moving, resets the cue at the cue balls new position.
    - Sets up again for player input.
    - Repeats.

* switchPlayer()
        - Used to swap players, currently not implemented for use.
        

---
## Built With:

* [Visual Studio Code](https://code.visualstudio.com/) - IDE for Windows
* [SFML](https://www.sfml-dev.org/) - External GUI Library (Both Windows and MacOS)
* [MingW](http://www.mingw.org/) - Minimalist GNU for Windows
* [Make](https://www.gnu.org/software/make/) - GNU Make application for Windows
* [Xcode](https://itunes.apple.com/nz/app/xcode/id497799835?mt=12) - IDE for MacOS

---
## Version:

Beta release.

---
## Project Changes:
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
* COSC 345 Lecture slides
* *Many thanks to Google.*
* *Shout out to caffeine.*
