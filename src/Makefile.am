AM_CFLAGS = -Wall 
bin_PROGRAMS = ld23
ld23_SOURCES = game.cpp resource.cpp shader.cpp tilemap.cpp input.cpp \
               audio.cpp sound.cpp drawable.cpp image.cpp renderer.cpp \
               resourcemanager.cpp tile.cpp tileset.cpp font.cpp sprite.cpp \
               camera.cpp \
               osd.cpp overlay.cpp player.cpp gamestate.cpp item.cpp key.cpp \
               door.cpp blob.cpp minidragon.cpp flame.cpp checkpoint.cpp \
               background.cpp doublejump.cpp blackkey.cpp bosscontrol.cpp \
               bosscreature.cpp

ld23_LDADD = -L../lib/lib_json -ljsoncpp \
                -L../lib/stb_image -lstbimage

if NACL
ld23_LDADD += -lppapi -lppapi_cpp -lppapi_gles2
ld23_SOURCES += nacl.cpp
endif
if SDL
ld23_SOURCES += main.cpp
ld23_LDADD += $(OPENAL_LIBS) \
			     $(GL_LIBS) \
                 $(SDL_LIBS) \
                 $(GLEW_LIBS)
endif

EXTRA_DIST = camera.h drawable.h game.h image.h renderer.h resource.h \
             resourcemanager.h shader.h tile.h tilemap.h tileset.h font.h \
             sprite.h megaman.h

ld23_CFLAGS = -Wall -Wextra -g 

ld23_CXXFLAGS = -Wall -Wextra -g \
				   -I../include \
                   -I../lib/

if NACL
ld23_CXXFLAGS += -DTARGET_NACL
endif
if SDL
ld23_CXXFLAGS += -DTARGET_SDL \
                    $(OPENAL_CFLAGS) \
				    $(GL_CFLAGS) \
				    $(SDL_CFLAGS) \
                    $(GLEW_CFLAGS)
endif
