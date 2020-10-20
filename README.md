# StarrySky
A WIP platformer game, written in C++17, using GLFW.

It uses sprite-batching and texture atlases to recreate the experience of games from the 16-bit and 32-bit eras, but with a maintainable, modern code-base.

## Design Philosophy:
- Inspired by the Suckless project's minimalist design philosophy
- Data-oriented design in the backend, hidden behind object-oriented abstraction layers in an API
- Focus on balancing performance and easy-to-read code
- Performance goals:
  - To run at 60fps on a Raspberry Pi Zero
  - To keep the total binary size less than 100 MB

## Building:
```
git clone --recursive https://github.com/Kieran-Weaver/StarrySky
cd StarrySky
make
```

Building on Windows:

Git, at least in msys2, does not handle symlinks properly on Windows.
Before running `make` on Windows, run `./symlinks.sh` to restore the symlinks.

## Usage:
`./Platformer`

## Features:
- Pixel-perfect collision
- DDS/DXT5 Textures
- Custom sprite-batching algorithm
- RAII classes:
  - Sprite and Texture
  - Window and Camera
  - Map and MovingEntity
  - SpriteBatch and TextureAtlas

## Todo:
- Add proper unit tests
- Implement editor functionality
- Add documentation for APIs
- Add plugin system
- Replace imgui example files with custom implementations
  - Render through the sprite-batching API - Done
  - Handle input through the Window class
- Improve graphics backend:
  - Add 3D functionality
- Add game features:
  - Sprites
  - Enemy AI
  - Dynamically load resources

## Project Layout:
- src/GL contains the graphics backend, which is currently based on OpenGL 3.x and GLFW
- src/util contains common code that everything else uses.
- src/file contains APIs to read and write text, memory mapped, and JSON files
- src/core contains the physics and map system and any helper files.
- src/game contains the game's AI and higher-level game concepts such as game mechanics.

## Using Starry Sky as a Library
The GL portion of Starry Sky can be used as a standalone rendering library. The `lib` target in the Makefile creates `build/libSSGL.a`, which contains the implementation of the GL, util, and file folders, as well as code required to use ImGui.
The rendering library can draw 3 different types of objects: Sprites, Tilemaps, and ImGui windows. Both Sprites and Tilemaps are drawn using the SpriteBatch object, while ImGui windows are drawn automatically when ImGui is used.
See include/GL/Sprite.hpp, include/GL/Tilemap.hpp, and https://github.com/ocornut/imgui for information on Sprites, Tilemaps, and ImGui respectively.

## Example code:
```C++
#include <GL/TextureAtlas.hpp>
#include <GL/SpriteBatch.hpp>
#include <GL/Camera.hpp>
#include <GL/Window.hpp>
#include <GL/Sprite.hpp>
#include <GLFW/glfw3.h>
int main(int, char const**) {
	float x1=0.0, y1=360.0;
	Window window(1280, 720, 3, 3, "data/fonts/boxfont_round.ttf", "Example");
	window.getWindowState() = { new Camera(Rect<float>(-2000.f,-2000.f,4000.f,4000.f),Rect<float>(0.f,0.f,800.f,400.f), window) };
	TextureAtlas atlas("resources/data/atlas.json");
	SpriteBatch batch(atlas, "resources/data/shaders.json");
	Texture t = atlas.findSubTexture("test1");
	Sprite s;
	s.setTexture(t);
	while (window.isOpen()){
		s.setPosition(x1,y1);
		x1 += 1.0f;
		s.rotate(0.1f);
		window.startFrame();
		batch.Draw(s);
		batch.Draw(window);
		window.endFrame();
	}
	return 0;
}
```


## Acknowledgements and Links:
include/GL/Sprite.h, include/GL/SpriteBatch.h, include/GL/Texture.h, include/GL/TextureAtlas.h, and src/GL/TextureAtlas.cpp are originally from https://github.com/ricanteja/Moony-SpriteBatch, but were rewritten for Starry Sky.

The original engine for Starry Sky was based off of https://github.com/pixelpicosean/PlatformerEngine, but it was also rewritten.

The engine uses texture atlases which are generated by https://github.com/Kieran-Weaver/crunch
