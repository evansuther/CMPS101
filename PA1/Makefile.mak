JAVASRC    = Bard.java Word.java
SOURCES    = README Makefile $(JAVASRC)
MAINCLASS  = Bard
CLASSES    = Bard.class Word.class
JARFILE    = Bard.jar

all: $(JARFILE)

$(JARFILE): $(CLASSES)
	echo Main-class: $(MAINCLASS) > Manifest
	jar cvfm $(JARFILE) Manifest $(CLASSES)
	rm Manifest
	chmod +x $(JARFILE)
$(CLASSES): $(JAVASRC)
	javac -Xlint $(JAVASRC)
clean:
	rm $(CLASSES) $(JARFILE)