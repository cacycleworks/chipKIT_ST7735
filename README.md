### chipKIT_ST7735

Port of Adafruit's GFX and ST7735 libraries for Arduino to chipKIT to get their 1.8" TFT shield working on chipKIT boards.

Initial work by Chris K to get the code de-AVR'd and initially working on chipKIT.
Much credit to Majenko for amazing chipKIT-specific improvements as well as actual
new work in what this this particular 1.8" ST7735 TFT capabilities are! :D 
**Thanks Majenko!**

#### Includes game and kittehs demos
Be sure to check out the ST7735B "Buffered" examples! Fantastic demonstration of what this hardware can do. ST7735 is a more utilitarian text only demo more along the lines of a simple UI on an embedded device.

#### Install
1. Click the "Download Zip" button (usually at bottom of right column on Github project page).
2. Copy or move the `chipKIT_ST7735-master.zip` file to your mpide folder (normally Documents\mpide).
3. Extract to this folder (do not need to make 'chipKIT_ST7735-master' subfolder).
4. The folders from this project, `GFX`, `ST7735`, and `ST7735B` will then extract into your Libraries folder.
5. Start `mpide` (or must close and reopen already running mpide) and the demo examples will appear in the mpide menu File -> Examples -> ST7735 and ST7735B

#### Experimental
Majenko is working on an epic single body of code for controllers. "Experimental" is the manifestation of such. To use the Experimental code, first move GFX and ST7735 folders out from Libraries. Then copy TFT from Experimental to your Libraries folder. Or, use Majenko's UECIDE compiler, which won't confuse the ST7735.cpp in TFT/ with the ST7735 library. :)

This project has anecdotal notations and discussion on http://www.chipkit.org/forum/viewtopic.php?f=18&t=2530

Please make contributions or requests on that thread.
