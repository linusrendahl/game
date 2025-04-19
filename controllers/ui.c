#include <stdio.h>
#include "../vendored/SDL_ttf/include/SDL3_ttf/SDL_ttf.h"
#include "../models.h"
#include "../assets/tiny_ttf.h"
#include "SDL3/SDL_stdinc.h"

void drawUI(Game *game) {
	static TTF_Font *font = NULL;
	extern unsigned char tiny_ttf[];
	extern unsigned int tiny_ttf_len;
	SDL_Color color = { 255, 255, 255, SDL_ALPHA_OPAQUE };
	SDL_Surface *textHP;
	SDL_Surface *textXP;
	static SDL_Texture *textureHP = NULL;
	static SDL_Texture *textureXP = NULL;


	if (!TTF_Init()) {
		SDL_Log("Couldn't initialise SDL_ttf: %s\n", SDL_GetError());
		return;
	}

	/* Open the font */
	font = TTF_OpenFontIO(SDL_IOFromConstMem(tiny_ttf, tiny_ttf_len), true, 18.0f);
	if (!font) {
		SDL_Log("Couldn't open font: %s\n", SDL_GetError());
		return;
	}

	/* Create the text */
	char hitpoints[100];
	sprintf(hitpoints, "HP: %i", game->player.hitpoints);
	char experience[100];
	sprintf(experience, "XP: %i", game->player.xp);


	textHP = TTF_RenderText_Blended(font, hitpoints, 0, color);
	textXP = TTF_RenderText_Blended(font, experience, 0, color);
	if (textHP) {
		textureHP = SDL_CreateTextureFromSurface(game->renderer, textHP);
		textureXP = SDL_CreateTextureFromSurface(game->renderer, textXP);
		SDL_DestroySurface(textHP);
		SDL_DestroySurface(textXP);
	}
	if (!textureHP) {
		SDL_Log("Couldn't create text: %s\n", SDL_GetError());
		return;
	}

	int w = 0, h = 0;
	SDL_FRect dst;

	/* Center the text and scale it up */
	SDL_GetTextureSize(textureHP, &dst.w, &dst.h);
	dst.x = 24;
	dst.y = 72;
	SDL_RenderTexture(game->renderer, textureHP, NULL, &dst);
	
	SDL_GetTextureSize(textureXP, &dst.w, &dst.h);
	dst.x = 24;
	dst.y = 96;
	SDL_RenderTexture(game->renderer, textureXP, NULL, &dst);

}
