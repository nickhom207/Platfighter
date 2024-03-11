To run in Visual Studio:
1. Open .sln file
2. Solution properties -> C/C++ -> General > Additional Library Directories -> Add "Platfighter\SDL2\include"
3. Solution properties -> Linker -> General > Additional Library Directories -> Add "Platfighter\SDL2\lib\x64"
4. Solution properties -> Linker -> Input > Additional Dependencies -> Add "SDL2.lib" and "SDL2main.lib"

The steps above should be repeated for SDL_Mixer and SDL_Image

For errors regarding external symbols or persistent missing files, install the latest Windows SDK.
