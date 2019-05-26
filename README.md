# COSC345 Year Long Project - 8 Ball Pool

An 8 ball pool game which follows the concept of 'Small Is Beautiful'. We are aiming to create a program which is very lite, challenging, but enjoyable to play. Our game is for offline play, allowing for local player versus player, and a puzzle trickshot 
mode.

### Prerequisites

We are building this program using the C++ language on Windows based computers. However we will supply instructions on how to install the various components onto both Windows and MacOS.

### Installing
**For MacOS Users:**

**_Please note that these instructions are for Mac users using the Xcode IDE_**
**_We will assume you have Xcode installed, otherwise please install Xcode before proceeding; [Download Xcode](https://itunes.apple.com/nz/app/xcode/id497799835?mt=12)_**

**Step1:**

Clone or download this Github repository to your local computer.

**Step2:**

*If you have cloned the repository, skip to Step3*
Move zip file to desired location and unzip.

**Step3:**

Navigate through the project to the Apple_Build folder which contains the Xcode project file *Apple_Build.xcodeproj*
```
345-master/Apple_Build/Apple_Build/Apple_Build.xcodeproj
```
Then open the *Apple_Build.xcodeproj* with Xcode.

**Step4:**

Once open, to build the project, press the build and run button (found on the top left of the project window).
_A new window will pop up with the application running._
To stop the application from running, return to the Xcode project window and press the stop button which is next to the run button.

**NB: If you edit the code, you will need to clean the build folder before building the project again for it to run.
This can be done by pressing:
```
Command + Alt + Shift + k
```

***For Windows:***

**Step 1:**
Make sure to have the following 

```
Give the example
```

And repeat

```
until finished
```
Final Step:
You should now be able to build the program by entering:
```
make
```
in the directory of the project, and then run the program by entering:
```
app
```

## Running the program.

The program takes inputs from the keyboard and will not require the use of a mouse.
Here is a list of input keys for our program:
```
Left/Right Arrow Keys   | Changes direction of the cue on the cue ball.
Up/Down Arrow Keys      | Changes the power input of the shot.
Spacebar                | Initiates the shot to be made.
```
Exiting the program can be done by pressing:
```
alt + f4
```

### Break down into end to end tests

Explain what these tests test and why

```
Give an example
```

### Coding Style

We will be coding our program following the K & R standard layout. 

```
void checknegative(x) {
    if (x < 0) {
        puts("Negative");
    } else {
        nonnegative(x);
    }
}
```

## Built With

* [Visual Studio Code](https://code.visualstudio.com/) - IDE used
* [SFML](https://www.sfml-dev.org/) - External GUI Library
* [MingW](http://www.mingw.org/) - Minimalist GNU for Windows
* [Make](https://www.gnu.org/software/make/) - GNU Make application

## Version

Alpha release.

## Authors

* **Liam Chapman**
* **Calum Hunter**
* **John Kim**

## License

Current there is no license, but if required we will use the MIT License.

## Acknowledgments

*Many thanks to the internet.*
