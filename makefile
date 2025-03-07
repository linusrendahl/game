game:
	clang main.c controllers/enemy.c controllers/player.c controllers/game.c controllers/map.c controllers/sdl.c `pkg-config --libs --cflags sdl3`
