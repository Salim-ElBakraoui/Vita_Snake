
# Snake Clone for PSVita

This is my first PSVita C++ application, it was supposed to be a test I had in class, and I thought about porting it over to the PSVita.
It is made using the `SDL2 SDL2_ttf SDL2_image SDL2_mixer` libraries.

## How to compile
To compile that, you need to have the [VitaSDK](https://vitasdk.org/) suite installed. Once that's done, clone the project and then type in this command

```bash
cmake . && make
```
Once that's done, you'll have a VPK file that's ready to use on your PSVita. Sadly, the game doesnt work on the Vita3K emulator.

## How do I play the game

Well it's Snake, it's quite straightforward
* Use the directional pad to control your snake
* Press START to pause the game
* Press SELECT to leave the game (You can use the PS Button and close the app too, this works)

## Known bugs

On the PSVita build of this game only, sometimes the Red Apple (+1 Section) does not spawn and you have to eat the purple one (-1 Section) to make it spawn again, quite a weird bug because it doesnt happen on PC.

