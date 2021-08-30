#include <stdlib.h>
#include <stdio.h>
#include<SDL2/SDL_mixer.h>
#include<SDL2/SDL.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define SIZE 100 //buffer size for reading from file

Mix_Chunk *thank, *crowd, *betterluck, *tryagain;
Mix_Chunk *last;
int ATTEMPTS;

//user defined functions
void loadingscreen();
void loadSounds();
char readCharacter();
void echo(int, char*);
void display_win();
void display_lose();
int MainGameLoop();

int main()
{   
    loadSounds();
    char choice;
    int x;
    do
    {
        system("clear");
        system("echo -n \"Loading\"");
        for(int i = 0; i < 20; i++)
        {
            loadingscreen();
        }
        printf("\n\n");
        system("sleep 0.5");
        MainGameLoop();
        SDL_Delay(1500);
        Mix_PlayChannel(-1, tryagain, 0);
        system("sleep 1");
        printf("Do you want to continue the game [y/n]: ");
        scanf("%c", &choice);
    }
    while(choice == 'y' || choice == 'Y');
    SDL_Delay(100);
    Mix_PlayChannel(-1, last, 0);
    system("sleep 1");
    printf("Thank you for Playing\n");
    system("echo -n \"Exiting\"");
    for(int i = 0; i < 20; i++)
        {
            loadingscreen();
        }
    printf("\n");
    return 0;
    
}

char readCharacter()
{
	char character;
	scanf("%c", &character);
	character = tolower(character);
	while (getchar() != '\n');
	return character;
}

void echo(int count, char* secret) 
{
	printf("\nYou still have %d attempts\n", count);
	printf("What is the secret word? %s\n", secret);
	printf("Enter a letter: ");
}

void display_win()
{
for(int i = 0; i < 20; i++)
{
        //printf("\n\n\n\n");
        printf("\t           O          \n");
        printf("\t          /|\\         \n");
        printf("\t          / \\         \n");
        //printf("\t ----------------------\n");
        SDL_Delay(50);
        system("clear");
        //printf("\n\n\n\n");
        printf("\t          \\O/         \n");
        printf("\t           |          \n");
        printf("\t          / \\         \n");
        //printf("\t ----------------------\n");
        
        SDL_Delay(50);
        system("clear");
}
}
void display_lose()
{
        printf("\t ______________________\n");
        printf("\t |                    |\n");
        printf("\t O                    |\n");
        printf("\t/|\\                   |\n");
        printf("\t/ \\                   |\n");
        printf("\t                      |\n");
        printf("\t                      |\n");
        printf("\t ----------------------\n");
}
int MainGameLoop()
{
    FILE* file = fopen("wordlist.txt", "r");
	    if (file == NULL)
	    {
		    return 1;
		}

	    long size = 0;
	    char current;
	    do
	    {
		    current = fgetc(file);
		    if (current == '\n')
			    size += 1;
	    } while (current != EOF);
	    rewind(file);
	    srand(time(NULL));
	    const long min = 0;
	    const long max = size;
	    long line = (rand() % (max - min + 1)) + min;

	    char buff[SIZE];
	    while (line--)
	    {
		    fgets(buff, SIZE, file);
	    }

	    fclose(file);
	    buff[strcspn(buff, "\n\r")] ='\0'; 
	    ATTEMPTS = strlen(buff) ;
	    int length = strlen(buff) ;
	    char* word = malloc(sizeof(char)*(length));
	    char* secret = malloc(sizeof(char)*(length));
	    for (int i = 0; i < length; i++)
	    {
		    word[i] = buff[i];
		    secret[i] = '*';
	    }
	    word[length] = '\0';
	    secret[length] = '\0';

	    int count = ATTEMPTS;

	    printf("---------------Welcome to Hangman Game-------------------\n");
	    system("sleep 0.5");

	    while (count && strcmp(word, secret))
	    {
		    echo(count, secret);
		    char input = readCharacter();

		    char* found = strchr(word, input);

		    if (found != NULL)
		    {
			    for (int i = 0; i < length; i++)
			    {
				    if (word[i] == input)
				    {
					    secret[i] = input;
				    }
			    }
		    }
		    else
			    count -= 1;
	    }

	    if (count)
	    {
		    Mix_PlayChannel(3, crowd, 0);
		    display_win();
		    printf("\nCongratulation ! The secret word is indeed : %s\n", word);
		    Mix_PlayChannel(4, thank, 0);
	    }
	    else
	    {
	    system("clear");
		    printf("\nYou lost ! :-( The secret word was : %s\n", word);
		    display_lose();
		    Mix_PlayChannel(5, betterluck, 0);
		    SDL_Delay(500);
	    }

	    free(word);
	    free(secret);
	    return 0;
	    
}

void loadSounds()
{
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
      {
        printf("%s", SDL_GetError());
        exit(1);
      }
      Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT,
                    MIX_DEFAULT_CHANNELS, 4096);
  thank = Mix_LoadWAV("sounds/Thank you.wav");
  if (thank == NULL)
  {
    printf("%s", SDL_GetError());
    exit(1);
  }
  Mix_VolumeChunk(thank, MIX_MAX_VOLUME);
  crowd = Mix_LoadWAV("sounds/Cheer.wav");
  if (crowd == NULL)
  {
    printf("%s", SDL_GetError());
    exit(1);
  }
  Mix_VolumeChunk(crowd, MIX_MAX_VOLUME);
  betterluck = Mix_LoadWAV("sounds/better_luck.wav");
  if (betterluck == NULL)
  {
    printf("%s", SDL_GetError());
    exit(1);
  }
  Mix_VolumeChunk(betterluck, MIX_MAX_VOLUME / 2);
  tryagain = Mix_LoadWAV("sounds/tryagain.wav");
  if (tryagain == NULL)
  {
    printf("%s", SDL_GetError());
    exit(1);
  }
  Mix_VolumeChunk(tryagain, MIX_MAX_VOLUME / 2);
  last = Mix_LoadWAV("sounds/last.wav");
  if (last == NULL)
  {
    printf("%s", SDL_GetError());
    exit(1);
  }
  Mix_VolumeChunk(last, MIX_MAX_VOLUME / 3);
  
}
void loadingscreen()
{
    int i;
    system("echo -n \" #\"");
    system("sleep 0.09");
}

//Lets play the game :)

