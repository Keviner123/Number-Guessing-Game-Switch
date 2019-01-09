#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <switch.h>
#include <iostream>

using namespace std;


short int CorrectNumber;
short int UserGuess;
short int Lifes;
short int Wins;
short int Defeats;
std::string GuessResult;


void SetGame();
void SubtractLift();
void RenderGame();

int main(int argc, char* argv[])
{
    //Initialize console. Using NULL as the second argument tells the console library to use the internal console structure as current one.
    consoleInit(NULL);
    Wins = 0;
    Defeats = 0;

    SetGame();

    while(appletMainLoop())
    {
		
		RenderGame();
		
        //Scan all the inputs. This should be done once for each frame
        hidScanInput();

        //hidKeysDown returns information about which buttons have been just pressed (and they weren't in the previous frame)
        u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);

        if (kDown & KEY_PLUS) break; // break in order to return to hbmenu


        if (kDown & KEY_UP){
            UserGuess = UserGuess+1;
            if (UserGuess > 10){
                UserGuess = 10;
            }
        }

        if (kDown & KEY_DOWN){
            UserGuess = UserGuess-1;

            if (UserGuess < 1){
                UserGuess = 1;
            }
        }

        if (kDown & KEY_PLUS){
             break; // break in order to return to hbmenu
        }

        if (kDown & KEY_A){			
			

            if (CorrectNumber > UserGuess){
                GuessResult = "Higher";
                SubtractLift();
            }
            if (CorrectNumber < UserGuess){
                GuessResult = "Lower";
                SubtractLift();
            }
            if (CorrectNumber == UserGuess){
                GuessResult = "Winner";
                
                Wins = Wins + 1;

                SetGame();
            }
        }

		if (Lifes == 0){
            GuessResult = "Game over";

            Defeats = Defeats + 1;

			SetGame();
			RenderGame();
		}	
		
        consoleUpdate(NULL);
    }

    consoleExit(NULL);
    return 0;
}


void SetGame(){
	UserGuess = 1;
	CorrectNumber = rand() % 10 + 1;
	Lifes = 3;
}

	
void SubtractLift(){
	Lifes = Lifes - 1;
}

void RenderGame(){
	consoleInit(NULL); 
	printf("\x1b[16;20HInput guess: %d\n", UserGuess);
	printf("\x1b[17;20H%d Lifes left", Lifes);
    std::cout << "\x1b[19;20H"+GuessResult;
	printf("\x1b[21;20H%d Wins: ", Wins);
	printf("\x1b[22;20H%d Defeats", Defeats);

}