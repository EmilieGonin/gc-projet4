#include <stdio.h>
#include <iostream>
#include "SDL.h"
#include "SDL_ttf.h"
#include <stdio.h>
#include <stdlib.h>
#include"window.h"

using namespace std;


Window::Window()
{
	this->running = true;
	this->succes = true;
	this->window = NULL;
	this->renderer = NULL;
	//this->surfaceMessage = NULL;
	//this->Message = NULL;

}

Window::~Window(){}


bool Window::init() {


	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		//Create window
		this->window = SDL_CreateWindow("Une fenetre SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->WINDOW_WIDTH, this->WINDOW_HEIGHT,NULL);
		this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); // Cr�ation du renderer
		if (this->window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		if (this->renderer == NULL)//gestion des erreurs
		{
			printf("Window couldn't be rendered! : %s", SDL_GetError());
			return EXIT_FAILURE;
		}
	}

	return this->succes;
}

void Window::destroy() {

	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
	SDL_Quit(); // On quitte la SDL
	//SDL_FreeSurface(surfaceMessage);
	//SDL_DestroyTexture(Message);
	
}

bool Window::homeView() {

	SDL_RenderClear(this->renderer);
	SDL_SetRenderDrawColor(this->renderer, 200, 50, 100, 255);
	SDL_Rect rectangle{ 0,0,this->WINDOW_WIDTH/2,this->WINDOW_HEIGHT };
	SDL_RenderDrawRect(this->renderer, &rectangle);
	SDL_RenderFillRect(this->renderer, &rectangle);

	return this->succes;
}

bool Window::view2() {


	SDL_SetRenderDrawColor(this->renderer, 000, 000, 000, 255);
	SDL_RenderClear(this->renderer);
	SDL_SetRenderDrawColor(this->renderer, 100, 150, 200, 55);
	SDL_Rect rectangle{ 0,0,this->WINDOW_WIDTH,this->WINDOW_HEIGHT };
	SDL_RenderFillRect(this->renderer, &rectangle);
	SDL_SetRenderDrawColor(this->renderer, 200, 150, 130, 255);
	SDL_Rect rectangle1{ 25,25,this->WINDOW_WIDTH - 50,this->WINDOW_HEIGHT - 50 };
	SDL_RenderDrawRect(this->renderer, &rectangle1);
	SDL_Rect rectangle2{ 50,50,200,200 };
	SDL_RenderFillRect(this->renderer, &rectangle2);

	return this->succes;
}


bool Window::renderText(const std::string &font_path) {
	
	//this opens a font style and sets a size
	TTF_Font* Sans = TTF_OpenFont(font_path.c_str(), 24);
	if (!Sans)
	{
		std::cout << "failed to load font" << std::endl;
	}

	// this is the color in rgb format,
	// maxing out all would give you the color white,
	// and it will be your text's color
	SDL_Color White = { 255, 255, 255 };

	// as TTF_RenderText_Solid could only be used on
	// SDL_Surface then you have to create the surface first
	auto surfaceMessage = TTF_RenderText_Solid(Sans, "hello world", White);
	if (!surfaceMessage)
	{
		std::cout << "failed to create text surface" << std::endl;

	}

	// now you can convert it into a texture
	auto Message = SDL_CreateTextureFromSurface(this->renderer, surfaceMessage);
	if (!Message)
	{
		std::cout << "failed to create text texture" << std::endl;

	}

	SDL_Rect Message_rect;
	Message_rect.x = 0;  
	Message_rect.y = 0; 
	Message_rect.w = 100; 
	Message_rect.h = 100; 

	SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

	// Don't forget to free your surface and texture
	//SDL_FreeSurface(surfaceMessage);
	return this->succes;

}



int Window::WindowEvent() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) // R�cup�ration des actions de l'utilisateur
	{
		switch (event.type)
		{
		case SDL_QUIT: // Clic sur la croix
			this->running = false;
			break;
		case SDL_KEYUP: // Rel�chement d'une touche
			if (event.key.keysym.sym == SDLK_2) // Touche 0
			{
				this->view2();
			}
			break;
			if (event.key.keysym.sym == SDLK_1) // Touche 1
			{
				this->homeView();
			}
			break;
		}
	}
	return 0;
}



bool Window::refreshRender() {

	SDL_RenderPresent(this->renderer);

	return this->succes;

}



//int window() {
//
//
//
//
//	SDL_Event evnt;
//	bool quit = false;
//	while (SDL_PollEvent(&evnt) != 0) {
//
//		if (evnt.type == SDL_QUIT) {
//			quit = true;
//		}
//	}
//
//
//	// Destruction du renderer et de la fen�tre :
//
//
//	return 0;
//}