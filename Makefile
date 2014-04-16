PFLTK=~/tmp/FLTK/FltkLinux64
PFMOD=~/tmp/FLTK/FModLinux64
PREOPTIONS=-I$(PFMOD) -I$(PFLTK) -I$(PFLTK)/jpeg
POSTOPTIONS=$(PFLTK)/lib/libfltk.a $(PFLTK)/lib/libfltk_forms.a $(PFLTK)/lib/libfltk_gl.a $(PFLTK)/lib/libfltk_images.a $(PFLTK)/lib/libfltk_jpeg.a $(PFLTK)/lib/libfltk_png.a $(PFMOD)/api/lib/libfmodex64.so -lX11 -lXext -ldl -lm

EXENAME=projet
FICHIERS=main.cpp u1-interface.cpp u2-dessin.cpp u3-callbacks.cpp u4-fonctions.cpp

.PHONY:all view

all:$(EXENAME)

view:$(EXENAME)
	./$(EXENAME)

$(EXENAME):$(FICHIERS)
	g++ $(PREOPTIONS) -o $(EXENAME) $(FICHIERS) $(POSTOPTIONS)


git:
	git add * && git commit -a && git push origin master

git_down:
	git pull origin master