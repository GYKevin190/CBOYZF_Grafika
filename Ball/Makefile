all:
	gcc -Iinclude/ src/scoreboard.c src/gate.c src/app.c src/fog_settings.c src/camera.c src/tree.c src/main.c src/scene.c src/texture.c src/utils.c src/ball.c src/fence.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lobj -lopengl32 -lm -o ball.exe -Wall -Wextra -Wpedantic -w 

linux:
	gcc -Iinclude/ src/app.c src/camera.c src/main.c src/scene.c src/texture.c src/utils.c -lobj -lSDL2 -lSDL2_image -lGL -lm -o cube -Wall -Wextra -Wpedantic
