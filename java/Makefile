PKG_DIR = application

FLAGS = --module-path /Users/tomberne/Downloads/javafx-sdk-21.0.7/lib --add-modules javafx.controls,javafx.fxml

JC = javac
JC_FLAGS = -g -Xlint $(FLAGS)

JV = java
JV_FLAGS = -Djava.library.path=.:/usr/lib/x86_64-linux-gnu/jni/ $(FLAGS)

.SUFFIXES: .java .class

_CLASSES = Intersections.java UserInterface.java
CLASSES = $(patsubst %,$(PKG_DIR)/%,$(_CLASSES))

default: classes

classes: $(CLASSES:.java=.class)

.java.class:
	$(JC) $(JC_FLAGS) $*.java

run: classes
	$(JV) $(JV_FLAGS) $(PKG_DIR).UserInterface

clean:
	rm -f $(PKG_DIR)/*.class
