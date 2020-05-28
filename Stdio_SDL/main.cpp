#include <stdio.h>
#include <SDL.h>
#include <time.h>
#include <random>
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
#undef main
        //desRect.x = 0;
        //desRect.y = x++;
        //desRect.w = sourceRect.w;
        //desRect.h = sourceRect.h;

int figures[7][4]
{
    1,3,5,7, // I
    2,4,5,7, // Z
    3,5,4,6, // S
    3,5,4,7, // T
    2,3,5,7, // L
    3,5,7,6, // J
    2,3,4,5, // O
};
struct Point{int x;int y;}a[4],b[4];
int main()
{
    unsigned int lastTime = 0.3, currentTime;
    SDL_Event e;
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Surface* tempSurface = NULL;
	SDL_Texture* texture = NULL;
	SDL_Event mainEvent;
	SDL_Rect sourceRect;
	SDL_Rect desRect;
	bool isRunning = true;

	//initializes  the subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("Unable to initialize SDL %s\n", SDL_GetError());
		return -1;
	}

	//Create window
	window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 320, 480, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		printf("Could not create window %s", SDL_GetError());
		return -1;
	}


	//create a renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		printf("Could not create render %s", SDL_GetError());
		return -1;
	}

	//create a tempSurface
	tempSurface = SDL_LoadBMP("tiles.bmp");
	//create a texutre from surface
	texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	//free surface
	SDL_FreeSurface(tempSurface);


	SDL_QueryTexture(texture, NULL, NULL, &sourceRect.w, &sourceRect.h);
    sourceRect.x = 0;
    sourceRect.y = 0;
    sourceRect.w = sourceRect.w / 8;
    sourceRect.h = sourceRect.h ;
    int dx=0;
    bool rotate=0;
    int colorNum=1;
    while(1)
    {
        currentTime = SDL_GetTicks();
        // Nếu không có sự kiện gì thì tiếp tục trở về đầu vòng lặp

        if ( SDL_WaitEvent(&e) == 0) continue;
        // Nếu sự kiện là kết thúc (như đóng cửa sổ) thì thoát khỏi vòng lặp

        // Nếu có một phím được nhấn, thì xét phím đó là gì để xử lý tiếp
        if (e.type == SDL_KEYDOWN) {
            // Nếu nhấn phìm ESC thì thoát khỏi vòng lặp


            // Nếu phím mũi tên trái, dịch sang trái
            // (cộng chiều rộng, trừ bước, rồi lấy phần dư để giá trị luôn dương, và hiệu ứng quay vòng)
            if (e.key.keysym.sym == SDLK_LEFT)dx=-1;
            // Tương tự với dịch phải, xuống và lên
            if (e.key.keysym.sym == SDLK_RIGHT)dx=1;
            if (e.key.keysym.sym == SDLK_UP)rotate=true;
        }
        for(int i=0;i<4;i++) a[i].x+=dx;
        if (rotate)
      {
        Point p = a[1]; //center of rotation
        for (int i=0;i<4;i++)
          {
            int x = a[i].y-p.y;
            int y = a[i].x-p.x;
            a[i].x = p.x - x;
            a[i].y = p.y + y;
           }

      }
      if(currentTime>lastTime+1000)
      {
          for(int i=0;i<4;i++)
            a[i].y+=1;
          lastTime=currentTime;
      }
        srand(time(NULL));
        int n=2;
        if(a[0].x==0)
        for(int i=0;i<4;i++)
        {
            a[i].x=figures[n][i]%2;
            a[i].y=figures[n][i]/2;
        }
        dx=0,rotate=0;
            for(int i=0;i<4;i++)
        {
            desRect.x =a[i].x*sourceRect.w;
            desRect.y =a[i].y*sourceRect.h;
            desRect.w = sourceRect.w;
            desRect.h = sourceRect.h;
            SDL_RenderCopy(renderer, texture, &sourceRect, &desRect);
            SDL_RenderPresent(renderer);
        }

        SDL_RenderClear(renderer);
        SDL_Delay(50);
    }

	return 0;
}
