# COSC345 Year Long Project - 8 Ball Pool

An 8 ball pool game which follows the concept of 'Small Is Beautiful'. We are aiming to create a program which is very lite, challenging, but enjoyable to play. Our game is for offline play, allowing for local player versus player, and a puzzle trickshot 
mode.

---
### Prerequisites:
---

Our team is currently building this project using the C++ language on Windows(x86) based computers. However we will supply instructions on how to build our project in both Windows(x86) and MacOS(x64). We include the [SFML](https://www.sfml-dev.org/) libraries for both Windows and MacOS versions of our project.

For MacOS you will require to have [Xcode](https://itunes.apple.com/nz/app/xcode/id497799835?mt=12) installed.

For Windows you will require to have [Make](https://www.gnu.org/software/make/) installed, and have [Visual Studio Code setup with MinGW.](https://code.visualstudio.com/docs/cpp/config-mingw)

---
### Installing:
---

#### For MacOS Users:

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
#### For Windows:

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
## Running the program.
---

The program takes inputs from the keyboard and will not require the use of a mouse.
#### Here is a list of input keys for our program:
```
Left/Right Arrow Keys   | Changes direction of the cue on the cue ball.
Up/Down Arrow Keys      | Changes the power input of the shot.
Spacebar                | Initiates the shot to be made.
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
### Testing:
---

Our code base is currently too small for any automated testing.

---
### Coding Style:
---

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

---
## Built With
---

* [Visual Studio Code](https://code.visualstudio.com/) - IDE for Windows
* [SFML](https://www.sfml-dev.org/) - External GUI Library (Both Windows and MacOS)
* [MingW](http://www.mingw.org/) - Minimalist GNU for Windows
* [Make](https://www.gnu.org/software/make/) - GNU Make application for Windows
* [Xcode](https://itunes.apple.com/nz/app/xcode/id497799835?mt=12) - IDE for MacOS

---
## Version
---

Alpha release.

---
## Authors
---

* **Liam Chapman**
* **Calum Hunter**
* **John Kim**

---
## License
---

Current there is no license, but if required we will use the MIT License.

---
## Acknowledgments
---

*Many thanks to Google.*
