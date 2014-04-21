PFLTK=/home/felix/tmp/FLTK/lib/FltkLinux64
PFMOD=/home/felix/tmp/FLTK/lib/FModLinux64
OPTIONS=-I$(PFMOD) -I$(PFLTK) -I$(PFLTK)/jpeg
POSTOPTIONS=$(PFLTK)/lib/libfltk.a $(PFLTK)/lib/libfltk_forms.a $(PFLTK)/lib/libfltk_gl.a $(PFLTK)/lib/libfltk_images.a $(PFLTK)/lib/libfltk_jpeg.a $(PFLTK)/lib/libfltk_png.a $(PFMOD)/api/lib/libfmodex64.so -lX11 -lXext -ldl -lm

EXENAME=projet
FICHIERS=main.cpp u1-interface.cpp u2-dessin.cpp u3-callbacks.cpp u4-fonctions.cpp

.PHONY:all view

all:$(EXENAME)

view:all
	./$(EXENAME)

clean:
	rm -f *.o *.h.gch projet

$(EXENAME):u1-interface.o u2-dessin.o u3-callbacks.o u4-fonctions.o main.cpp main.h
	g++ $(OPTIONS) main.cpp u1-interface.o u2-dessin.o u3-callbacks.o u4-fonctions.o $(POSTOPTIONS) -o $(EXENAME)


u1-interface.o:       u1-interface.cpp u1-interface.h u2-dessin.h u3-callbacks.h u4-fonctions.h main.h
	g++ $(OPTIONS) -c u1-interface.cpp

u2-dessin.o:          u2-dessin.cpp u1-interface.h u2-dessin.h u3-callbacks.h u4-fonctions.h main.h
	g++ $(OPTIONS) -c u2-dessin.cpp

u3-callbacks.o:       u3-callbacks.cpp u1-interface.h u2-dessin.h u3-callbacks.h u4-fonctions.h main.h
	g++ $(OPTIONS) -c u3-callbacks.cpp

u4-fonctions.o:       u4-fonctions.cpp u1-interface.h u2-dessin.h u3-callbacks.h u4-fonctions.h main.h
	g++ $(OPTIONS) -c u4-fonctions.cpp






git:
	git add * && git commit -a && git push

git_down:
	git pull origin master
