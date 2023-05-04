# IR Acrylic Lamp
This is our EE2361 final project code repository.  Contained in the plsWork.X folder are the various C files (both .c and .h).  By opening the .x project folder in MPLab XIDE (ver. 5.50 verified working), you may view these files and even flash your microcontroller with the appropriate software.  Please note, it is entirely possible that the code does not clean and build the first time aroud.  Thereofre, it may be required to re-clean and build a second time in order to properly flash the code.

Project members include:
- Matthew Breach ([breac001](breac001@umn.edu))
- Jimena Jimenez (jimen238)
- Cheo Cedillo (cedil023)
- Kevin Sarmiento-Alvarez (sarmi003)

The microcontoller used was a PIC24FJ64GA002 and was programmed using a Microchip SNAP debugger.

Here is the [Link](https://github.com/mzbreach/ir_Acrylic_Lamp) to our project source code.


Below are the various static color buttons represented as integers and the GRB color data they correlate to.
- 4: red
    - 0, 255, 0
- 5: green
    - 255, 0, 0
- 6: blue
    - 0, 0, 255
- 7: white
    - 255, 255, 255
- 8: red_orange
    - 15, 255, 0
- 9: light_green
    - 255, 0, 20
- 10: light_blue
    - 80, 0, 255
- 12: orange
    - 30, 255, 0
- 13: cyan
    - 255, 0, 255
- 14: purple
    - 0, 127, 255

- 16: light_orange
    - 50, 255, 0
- 17: dark_blue
    - 0, 0, 75
- 18: magenta
    - 0, 255, 255

- 20: yellow
    - 255, 255, 0
- 21: faint_blue
    - 0, 0, 15
- 22: pink
    - 0, 255, 127