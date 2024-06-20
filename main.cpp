#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <vector>
#include <fstream>
#include <SDL.h>

using namespace std;

SDL_Window* window;
SDL_Renderer* renderer;
bool gameCont = true;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "SDL Hangman";

void logSDLError(std::ostream& os, const std::string &msg, bool fatal = false);
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();
SDL_Texture* loadTexture(const string &file, SDL_Renderer *renderer);
void renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y, int w, int h);

const int MAX_BAD_GUESS = 7;
const char DATA_FILE[] = "data/Ogden_Picturable_200.txt";

string chooseWord(const char* fileName);
string secretWord = chooseWord(DATA_FILE);
string guessWord = string(secretWord.length(), '-');
int badGuessCount = 0;
char guess;

bool contain(char guess, string secretWord);
string update(char guess, string secretWord, string guessWord);
bool gameWon(string guessWord, string secretWord, int badGuessCount);
void draw(int badGuessCount, SDL_Renderer* renderer);

void showGuessWord(string guessWord, SDL_Renderer* renderer);
//void showWrongGuess(char c, SDL_Renderer* renderer);

void gameLoop(SDL_Window* window, SDL_Renderer* renderer, SDL_Event e);

int main(int argc, char* argv[])
{
    SDL_Event e;
    char guess;

    gameLoop(window, renderer, e);


    cout << secretWord << endl;

    quitSDL(window, renderer);
    return 0;
}

void logSDLError(std::ostream& os, const std::string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
       SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);


    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}

SDL_Texture* loadTexture(const string &file, SDL_Renderer *renderer)
{
	SDL_Texture *texture = nullptr;

	SDL_Surface *loadedImage = SDL_LoadBMP(file.c_str());

	if (loadedImage != nullptr){
		texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
		SDL_FreeSurface(loadedImage);

		if (texture == nullptr){
			logSDLError(cout, "CreateTextureFromSurface");
		}
	}
	else {
		logSDLError(cout, "LoadBMP");
	}
	return texture;
}

void renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y, int w, int h)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
    dst.w = w;
    dst.h = h;

	SDL_RenderCopy(renderer, texture, NULL, &dst);
}

bool contain(char guess, string secretWord)
{
    for (int i = 0; i < secretWord.length(); i++)
    {
        if (guess == secretWord[i]) return true;
    }
    return false;
}

string update(char guess, string secretWord, string guessWord)
{
    for (int i = 0; i < secretWord.length(); i++)
    {
        if (guess == secretWord[i]) guessWord[i] = guess;
    }
    return guessWord;
}

void draw(int badGuessCount, SDL_Renderer* renderer)
{
    switch(badGuessCount)
    {
        case 0: {
            SDL_Texture *human = loadTexture("Picture/fig_0.bmp", renderer);
            renderTexture(human, renderer, 400, 0, 400, 400);
            SDL_RenderPresent(renderer);
            break;
        }
        case 1: {
            SDL_Texture *human = loadTexture("Picture/fig_1.bmp", renderer);
            renderTexture(human, renderer, 400, 0, 400, 400);
            SDL_RenderPresent(renderer);
            break;
        }
        case 2: {
            SDL_Texture *human = loadTexture("Picture/fig_2.bmp", renderer);
            renderTexture(human, renderer, 400, 0, 400, 400);
            SDL_RenderPresent(renderer);
            break;
        }
        case 3: {
            SDL_Texture *human = loadTexture("Picture/fig_3.bmp", renderer);
            renderTexture(human, renderer, 400, 0, 400, 400);
            SDL_RenderPresent(renderer);
            break;
        }
        case 4: {
            SDL_Texture *human = loadTexture("Picture/fig_4.bmp", renderer);
            renderTexture(human, renderer, 400, 0, 400, 400);
            SDL_RenderPresent(renderer);
            break;
        }
        case 5: {
            SDL_Texture *human = loadTexture("Picture/fig_5.bmp", renderer);
            renderTexture(human, renderer, 400, 0, 400, 400);
            SDL_RenderPresent(renderer);
            break;
        }
        case 6: {
            SDL_Texture *human = loadTexture("Picture/fig_6.bmp", renderer);
            renderTexture(human, renderer, 400, 0, 400, 400);
            SDL_RenderPresent(renderer);
            break;
        }
        case 7: {
            SDL_Texture *human = loadTexture("Picture/fig_7.bmp", renderer);
            renderTexture(human, renderer, 400, 0, 400, 400);
            SDL_RenderPresent(renderer);
            break;
        }
    }
}

string chooseWord(const char* fileName)
{
    vector<string> wordList;
	ifstream file(fileName);
  	if (file.is_open()) {
	    string word;
		while (file >> word) {
            wordList.push_back(word);
        }
    	file.close();
  	}
  	if (wordList.size() > 0) {
        srand(time(0));
  		int randomIndex = rand() % wordList.size();
    	return wordList[randomIndex];
	} else return "";
}

void showGuessWord(string guessWord, SDL_Renderer* renderer)
{
    int x = 200;
    for (int i = 0; i < guessWord.length(); i++)
    {
        switch(guessWord[i])
        {
            case '-': {
                SDL_Texture *background = loadTexture("Picture/-.bmp", renderer);
                renderTexture(background, renderer, x, 500, 50, 50);
                SDL_RenderPresent(renderer);
                break;
            }
            case 'a': {
                SDL_Texture *background = loadTexture("Picture/a.bmp", renderer);
                renderTexture(background, renderer, x, 500, 50, 50);
                SDL_RenderPresent(renderer);
                break;
            }
            case 'b': {
                SDL_Texture *background = loadTexture("Picture/b.bmp", renderer);
                renderTexture(background, renderer, x, 500, 50, 50);
                SDL_RenderPresent(renderer);
                break;
            }
            case 'c': {
                SDL_Texture *background = loadTexture("Picture/c.bmp", renderer);
                renderTexture(background, renderer, x, 500, 50, 50);
                SDL_RenderPresent(renderer);
                break;
            }
            case 'd': {
                SDL_Texture *background = loadTexture("Picture/d.bmp", renderer);
                renderTexture(background, renderer, x, 500, 50, 50);
                SDL_RenderPresent(renderer);
                break;
            }
            case 'e': {
                SDL_Texture *background = loadTexture("Picture/e.bmp", renderer);
                renderTexture(background, renderer, x, 500, 50, 50);
                SDL_RenderPresent(renderer);
                break;
            }
            case 'f': {
                SDL_Texture *background = loadTexture("Picture/f.bmp", renderer);
                renderTexture(background, renderer, x, 500, 50, 50);
                SDL_RenderPresent(renderer);
                break;
            }
            case 'g': {
                SDL_Texture *background = loadTexture("Picture/g.bmp", renderer);
                renderTexture(background, renderer, x, 500, 50, 50);
                SDL_RenderPresent(renderer);
                break;
            }
            case 'h': {
                SDL_Texture *background = loadTexture("Picture/h.bmp", renderer);
                renderTexture(background, renderer, x, 500, 50, 50);
                SDL_RenderPresent(renderer);
                break;
            }
            case 'i': {
                SDL_Texture *background = loadTexture("Picture/i.bmp", renderer);
                renderTexture(background, renderer, x, 500, 50, 50);
                SDL_RenderPresent(renderer);
                break;
            }
            case 'j': {
                SDL_Texture *background = loadTexture("Picture/j.bmp", renderer);
                renderTexture(background, renderer, x, 500, 50, 50);
                SDL_RenderPresent(renderer);
                break;
            }
            case 'k': {
                SDL_Texture *background = loadTexture("Picture/k.bmp", renderer);
                renderTexture(background, renderer, x, 500, 50, 50);
                SDL_RenderPresent(renderer);
                break;
            }
            case 'l': {
                SDL_Texture *background = loadTexture("Picture/l.bmp", renderer);
                renderTexture(background, renderer, x, 500, 50, 50);
                SDL_RenderPresent(renderer);
                break;
            }
            case 'm': {
                SDL_Texture *background = loadTexture("Picture/m.bmp", renderer);
                renderTexture(background, renderer, x, 500, 50, 50);
                SDL_RenderPresent(renderer);
                break;
            }
            case 'n': {
                SDL_Texture *background = loadTexture("Picture/n.bmp", renderer);
                renderTexture(background, renderer, x, 500, 50, 50);
                SDL_RenderPresent(renderer);
                break;
            }
            case 'o': {
                SDL_Texture *background = loadTexture("Picture/o.bmp", renderer);
                renderTexture(background, renderer, x, 500, 50, 50);
                SDL_RenderPresent(renderer);
                break;
            }
            case 'p': {
                SDL_Texture *background = loadTexture("Picture/p.bmp", renderer);
                renderTexture(background, renderer, x, 500, 50, 50);
                SDL_RenderPresent(renderer);
                break;
            }
            case 'q': {
                SDL_Texture *background = loadTexture("Picture/q.bmp", renderer);
                renderTexture(background, renderer, x, 500, 50, 50);
                SDL_RenderPresent(renderer);
                break;
            }
            case 'r': {
                SDL_Texture *background = loadTexture("Picture/r.bmp", renderer);
                renderTexture(background, renderer, x, 500, 50, 50);
                SDL_RenderPresent(renderer);
                break;
            }
            case 's': {
                SDL_Texture *background = loadTexture("Picture/s.bmp", renderer);
                renderTexture(background, renderer, x, 500, 50, 50);
                SDL_RenderPresent(renderer);
                break;
            }
            case 't': {
                SDL_Texture *background = loadTexture("Picture/t.bmp", renderer);
                renderTexture(background, renderer, x, 500, 50, 50);
                SDL_RenderPresent(renderer);
                break;
            }
            case 'u': {
                SDL_Texture *background = loadTexture("Picture/u.bmp", renderer);
                renderTexture(background, renderer, x, 500, 50, 50);
                SDL_RenderPresent(renderer);
                break;
            }
            case 'v': {
                SDL_Texture *background = loadTexture("Picture/v.bmp", renderer);
                renderTexture(background, renderer, x, 500, 50, 50);
                SDL_RenderPresent(renderer);
                break;
            }
            case 'w': {
                SDL_Texture *background = loadTexture("Picture/w.bmp", renderer);
                renderTexture(background, renderer, x, 500, 50, 50);
                SDL_RenderPresent(renderer);
                break;
            }
            case 'x': {
                SDL_Texture *background = loadTexture("Picture/x.bmp", renderer);
                renderTexture(background, renderer, x, 500, 50, 50);
                SDL_RenderPresent(renderer);
                break;
            }
            case 'y': {
                SDL_Texture *background = loadTexture("Picture/y.bmp", renderer);
                renderTexture(background, renderer, x, 500, 50, 50);
                SDL_RenderPresent(renderer);
                break;
            }
            case 'z': {
                SDL_Texture *background = loadTexture("Picture/z.bmp", renderer);
                renderTexture(background, renderer, x, 500, 50, 50);
                SDL_RenderPresent(renderer);
                break;
            }
        }
        x += 70;
    }
}

void gameLoop(SDL_Window* window, SDL_Renderer* renderer, SDL_Event e)
{
    secretWord = chooseWord(DATA_FILE);
    guessWord = string(secretWord.length(), '-');
    badGuessCount = 0;
    initSDL(window, renderer);

    SDL_Texture *background = loadTexture("Picture/Background_Hangman.bmp", renderer);
    renderTexture(background, renderer, 0, 0, 800, 600);
    SDL_RenderPresent(renderer);

    draw(badGuessCount, renderer);

    while (true)
    {
        showGuessWord(guessWord, renderer);

        if (SDL_WaitEvent(&e) == 0) continue;

        if (e.type == SDL_QUIT) break;

        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) break;

        if (e.type == SDL_KEYDOWN)
        {
            switch(e.key.keysym.sym)
            {
                case SDLK_a: {
                    guess = 'a';
                    SDL_Texture *background = loadTexture("Picture/a.bmp", renderer);
                    renderTexture(background, renderer, 250, 40, 50, 50);
                    SDL_RenderPresent(renderer);
                    break;
                }
                case SDLK_b: {
                    guess = 'b';
                    SDL_Texture *background = loadTexture("Picture/b.bmp", renderer);
                    renderTexture(background, renderer, 250, 40, 50, 50);
                    SDL_RenderPresent(renderer);
                    break;
                }
                case SDLK_c: {
                    guess = 'c';
                    SDL_Texture *background = loadTexture("Picture/c.bmp", renderer);
                    renderTexture(background, renderer, 250, 40, 50, 50);
                    SDL_RenderPresent(renderer);
                    break;
                }
                case SDLK_d: {
                    guess = 'd';
                    SDL_Texture *background = loadTexture("Picture/d.bmp", renderer);
                    renderTexture(background, renderer, 250, 40, 50, 50);
                    SDL_RenderPresent(renderer);
                    break;
                }
                case SDLK_e: {
                    guess = 'e';
                    SDL_Texture *background = loadTexture("Picture/e.bmp", renderer);
                    renderTexture(background, renderer, 250, 40, 50, 50);
                    SDL_RenderPresent(renderer);
                    break;
                }
                case SDLK_f: {
                    guess = 'f';
                    SDL_Texture *background = loadTexture("Picture/f.bmp", renderer);
                    renderTexture(background, renderer, 250, 40, 50, 50);
                    SDL_RenderPresent(renderer);
                    break;
                }
                case SDLK_g: {
                    guess = 'g';
                    SDL_Texture *background = loadTexture("Picture/g.bmp", renderer);
                    renderTexture(background, renderer, 250, 40, 50, 50);
                    SDL_RenderPresent(renderer);
                    break;
                }
                case SDLK_h: {
                    guess = 'h';
                    SDL_Texture *background = loadTexture("Picture/h.bmp", renderer);
                    renderTexture(background, renderer, 250, 40, 50, 50);
                    SDL_RenderPresent(renderer);
                    break;
                }case SDLK_i: {
                    guess = 'i';
                    SDL_Texture *background = loadTexture("Picture/i.bmp", renderer);
                    renderTexture(background, renderer, 250, 40, 50, 50);
                    SDL_RenderPresent(renderer);
                    break;
                }case SDLK_j: {
                    guess = 'j';
                    SDL_Texture *background = loadTexture("Picture/j.bmp", renderer);
                    renderTexture(background, renderer, 250, 40, 50, 50);
                    SDL_RenderPresent(renderer);
                    break;
                }
                case SDLK_k: {
                    guess = 'k';
                    SDL_Texture *background = loadTexture("Picture/k.bmp", renderer);
                    renderTexture(background, renderer, 250, 40, 50, 50);
                    SDL_RenderPresent(renderer);
                    break;
                }
                case SDLK_l: {
                    guess = 'l';
                    SDL_Texture *background = loadTexture("Picture/l.bmp", renderer);
                    renderTexture(background, renderer, 250, 40, 50, 50);
                    SDL_RenderPresent(renderer);
                    break;
                }
                case SDLK_m: {
                    guess = 'm';
                    SDL_Texture *background = loadTexture("Picture/m.bmp", renderer);
                    renderTexture(background, renderer, 250, 40, 50, 50);
                    SDL_RenderPresent(renderer);
                    break;
                }
                case SDLK_n: {
                    guess = 'n';
                    SDL_Texture *background = loadTexture("Picture/n.bmp", renderer);
                    renderTexture(background, renderer, 250, 40, 50, 50);
                    SDL_RenderPresent(renderer);
                    break;
                }
                case SDLK_o: {
                    guess = 'o';
                    SDL_Texture *background = loadTexture("Picture/o.bmp", renderer);
                    renderTexture(background, renderer, 250, 40, 50, 50);
                    SDL_RenderPresent(renderer);
                    break;
                }
                case SDLK_p: {
                    guess = 'p';
                    SDL_Texture *background = loadTexture("Picture/p.bmp", renderer);
                    renderTexture(background, renderer, 250, 40, 50, 50);
                    SDL_RenderPresent(renderer);
                    break;
                }
                case SDLK_q: {
                    guess = 'q';
                    SDL_Texture *background = loadTexture("Picture/q.bmp", renderer);
                    renderTexture(background, renderer, 250, 40, 50, 50);
                    SDL_RenderPresent(renderer);
                    break;
                }
                case SDLK_r: {
                    guess = 'r';
                    SDL_Texture *background = loadTexture("Picture/r.bmp", renderer);
                    renderTexture(background, renderer, 250, 40, 50, 50);
                    SDL_RenderPresent(renderer);
                    break;
                }
                case SDLK_s: {
                    guess = 's';
                    SDL_Texture *background = loadTexture("Picture/s.bmp", renderer);
                    renderTexture(background, renderer, 250, 40, 50, 50);
                    SDL_RenderPresent(renderer);
                    break;
                }
                case SDLK_t: {
                    guess = 't';
                    SDL_Texture *background = loadTexture("Picture/t.bmp", renderer);
                    renderTexture(background, renderer, 250, 40, 50, 50);
                    SDL_RenderPresent(renderer);
                    break;
                }
                case SDLK_u: {
                    guess = 'u';
                    SDL_Texture *background = loadTexture("Picture/u.bmp", renderer);
                    renderTexture(background, renderer, 250, 40, 50, 50);
                    SDL_RenderPresent(renderer);
                    break;
                }
                case SDLK_v: {
                    guess = 'v';
                    SDL_Texture *background = loadTexture("Picture/v.bmp", renderer);
                    renderTexture(background, renderer, 250, 40, 50, 50);
                    SDL_RenderPresent(renderer);
                    break;
                }
                case SDLK_w: {
                    guess = 'w';
                    SDL_Texture *background = loadTexture("Picture/w.bmp", renderer);
                    renderTexture(background, renderer, 250, 40, 50, 50);
                    SDL_RenderPresent(renderer);
                    break;
                }
                case SDLK_x: {
                    guess = 'x';
                    SDL_Texture *background = loadTexture("Picture/x.bmp", renderer);
                    renderTexture(background, renderer, 250, 40, 50, 50);
                    SDL_RenderPresent(renderer);
                    break;
                }
                case SDLK_y: {
                    guess = 'y';
                    SDL_Texture *background = loadTexture("Picture/y.bmp", renderer);
                    renderTexture(background, renderer, 250, 40, 50, 50);
                    SDL_RenderPresent(renderer);
                    break;
                }
                case SDLK_z: {
                    guess = 'z';
                    SDL_Texture *background = loadTexture("Picture/z.bmp", renderer);
                    renderTexture(background, renderer, 250, 40, 50, 50);
                    SDL_RenderPresent(renderer);
                    break;
                }
            }
            if (contain(guess, secretWord) == true) guessWord = update(guess, secretWord, guessWord);
            else badGuessCount ++;

            draw(badGuessCount, renderer);
        }

        if (guessWord == secretWord)
        {
            SDL_Texture *endBackground = loadTexture("Picture/WinBackground.bmp", renderer);
            renderTexture(endBackground, renderer, 0, 0, 800, 600);
            SDL_RenderPresent(renderer);

            while (true)
            {
                if (SDL_WaitEvent(&e) == 0) continue;

                if (e.type == SDL_QUIT) break;

                if (e.type == SDL_KEYDOWN)
                {
                    if (e.key.keysym.sym == SDLK_n) {
                        SDL_Quit();
                    }
                    if (e.key.keysym.sym == SDLK_y) gameLoop(window, renderer, e);
                }
            }

        }

        if (badGuessCount == MAX_BAD_GUESS)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderClear(renderer);
            SDL_Texture *endBackground = loadTexture("Picture/LoseBackground.bmp", renderer);
            renderTexture(endBackground, renderer, 0, 0, 800, 600);
            SDL_RenderPresent(renderer);

            while (true)
            {
                if (SDL_WaitEvent(&e) == 0) continue;

                if (e.key.keysym.sym == SDLK_n) {
                        SDL_Quit();
                        break;
                    }

                if (e.type == SDL_KEYDOWN)
                {
                    if (e.key.keysym.sym == SDLK_n) {
                        SDL_Quit();
                        break;
                    }
                    if (e.key.keysym.sym == SDLK_y) gameLoop(window, renderer, e);
                }
            }
        }
    }
}

/*void showWrongGuess(char c, SDL_Renderer* renderer, int& x, int& y, int& w, int&h)
{
    switch(char c)
    {
        case 'a': {
                SDL_Texture *background = loadTexture("Picture/a.bmp", renderer);
                renderTexture(background, renderer, x, y, w, h);
                SDL_RenderPresent(renderer);
                break;
            }
            case 'b': {
                SDL_Texture *background = loadTexture("Picture/b.bmp", renderer);
                renderTexture(background, renderer, x, y, w, h);
                SDL_RenderPresent(renderer);
                break;
            }
            case 'c': {
                SDL_Texture *background = loadTexture("Picture/c.bmp", renderer);
                renderTexture(background, renderer, x, y, w, h);
                SDL_RenderPresent(renderer);
                break;
            }
            case 'd': {
                SDL_Texture *background = loadTexture("Picture/d.bmp", renderer);
                renderTexture(background, renderer, x, y, w, h);
                SDL_RenderPresent(renderer);
                break;
            }
            case 'e': {
                SDL_Texture *background = loadTexture("Picture/e.bmp", renderer);
                renderTexture(background, renderer, x, y, w, h);
                SDL_RenderPresent(renderer);
                break;
            }
            case 'f': {
                SDL_Texture *background = loadTexture("Picture/f.bmp", renderer);
                renderTexture(background, renderer, x, y, w, h);
                SDL_RenderPresent(renderer);
                break;
            }
            case 'g': {
                SDL_Texture *background = loadTexture("Picture/g.bmp", renderer);
                renderTexture(background, renderer, x, y, w, h);
                SDL_RenderPresent(renderer);
                break;
            }
            case 'h': {
                SDL_Texture *background = loadTexture("Picture/h.bmp", renderer);
                renderTexture(background, renderer, x, y, w, h);
                SDL_RenderPresent(renderer);
                break;
            }
            case 'i': {
                SDL_Texture *background = loadTexture("Picture/i.bmp", renderer);
                renderTexture(background, renderer, x, y, w, h);
                SDL_RenderPresent(renderer);
                break;
            }
            case 'j': {
                SDL_Texture *background = loadTexture("Picture/j.bmp", renderer);
                renderTexture(background, renderer, x, y, w, h);
                SDL_RenderPresent(renderer);
                break;
            }
            case 'k': {
                SDL_Texture *background = loadTexture("Picture/k.bmp", renderer);
                renderTexture(background, renderer, x, y, w, h);
                SDL_RenderPresent(renderer);
                break;
            }
            case 'l': {
                SDL_Texture *background = loadTexture("Picture/l.bmp", renderer);
                renderTexture(background, renderer, x, y, w, h);
                SDL_RenderPresent(renderer);
                break;
            }
            case 'm': {
                SDL_Texture *background = loadTexture("Picture/m.bmp", renderer);
                renderTexture(background, renderer, x, y, w, h);
                SDL_RenderPresent(renderer);
                break;
            }
            case 'n': {
                SDL_Texture *background = loadTexture("Picture/n.bmp", renderer);
                renderTexture(background, renderer, x, y, w, h);
                SDL_RenderPresent(renderer);
                break;
            }
            case 'o': {
                SDL_Texture *background = loadTexture("Picture/o.bmp", renderer);
                renderTexture(background, renderer, x, y, w, h);
                SDL_RenderPresent(renderer);
                break;
            }
            case 'p': {
                SDL_Texture *background = loadTexture("Picture/p.bmp", renderer);
                renderTexture(background, renderer, x, y, w, h);
                SDL_RenderPresent(renderer);
                break;
            }
            case 'q': {
                SDL_Texture *background = loadTexture("Picture/q.bmp", renderer);
                renderTexture(background, renderer, x, y, w, h);
                SDL_RenderPresent(renderer);
                break;
            }
            case 'r': {
                SDL_Texture *background = loadTexture("Picture/r.bmp", renderer);
                renderTexture(background, renderer, x, y, w, h);
                SDL_RenderPresent(renderer);
                break;
            }
            case 's': {
                SDL_Texture *background = loadTexture("Picture/s.bmp", renderer);
                renderTexture(background, renderer, x, y, w, h);
                SDL_RenderPresent(renderer);
                break;
            }
            case 't': {
                SDL_Texture *background = loadTexture("Picture/t.bmp", renderer);
                renderTexture(background, renderer, x, y, w, h);
                SDL_RenderPresent(renderer);
                break;
            }
            case 'u': {
                SDL_Texture *background = loadTexture("Picture/u.bmp", renderer);
                renderTexture(background, renderer, x, y, w, h);
                SDL_RenderPresent(renderer);
                break;
            }
            case 'v': {
                SDL_Texture *background = loadTexture("Picture/v.bmp", renderer);
                renderTexture(background, renderer, x, y, w, h);
                SDL_RenderPresent(renderer);
                break;
            }
            case 'w': {
                SDL_Texture *background = loadTexture("Picture/w.bmp", renderer);
                renderTexture(background, renderer, x, y, w, h);
                SDL_RenderPresent(renderer);
                break;
            }
            case 'x': {
                SDL_Texture *background = loadTexture("Picture/x.bmp", renderer);
                renderTexture(background, renderer, x, y, w, h);
                SDL_RenderPresent(renderer);
                break;
            }
            case 'y': {
                SDL_Texture *background = loadTexture("Picture/y.bmp", renderer);
                renderTexture(background, renderer, x, y, w, h);
                SDL_RenderPresent(renderer);
                break;
            }
            case 'z': {
                SDL_Texture *background = loadTexture("Picture/z.bmp", renderer);
                renderTexture(background, renderer, x, y, w, h);
                SDL_RenderPresent(renderer);
                break;
            }
    }
}*/
