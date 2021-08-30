echo -e "This will install all required dependencies for linux machine"
echo
read -p "[+] Install SDL2 libraries? (sudo required) [Y/N]: " -n 1 -r
echo    # (optional) move to a new line
if [[ $REPLY =~ ^[Yy]$ ]]
then
 sudo apt-get install libsdl2-2.0-0 && sudo apt-get install libsdl2-dev
 sudo apt-get install libsdl2-mixer-2.0-0 && sudo apt-get install libsdl2-mixer-dev
 sudo apt-get install libsdl2-ttf-2.0-0  && sudo apt-get install libsdl2-ttf-dev 
 sudo apt-get install libsdl2-image-2.0-0 && sudo apt-get install libsdl2-image-dev
fi
echo

echo [+] Attempting to compile game.....
gcc -c game.c
echo gcc -c game.c
gcc game.o  -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lm -Wall -o game
echo gcc game.o -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lm -Wall -o game

echo -e "\nCONGRATULATIONS !!!!!!!!! Game is Compiled successfully :)"
echo -e "To play the game just type \e[93m./game\e[0m in terminal\n"
