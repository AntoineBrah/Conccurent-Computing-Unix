CXX=g++
CXX_FLAGS= -ansi -Wall 
SOURCE1= interfaceIPC.cc interfaceSite.cc table_printer.cc client.cc
SOURCE2= interfaceIPC.cc interfaceSite.cc table_printer.cc serveur.cc
PROG1=client
PROG2=serveur
MSG_OK = @ echo "\t\t\t........................OK"

.SUFFIXES : .cc .h .o

all : $(PROG1) $(PROG2)

.o :
	$(CXX) -c $(CXX_FLAGS) $<
	$(MSG_OK)

$(PROG1) : $(SOURCE1:.cc=.o)
	$(CXX) $^ $(CXX_FLAGS) -o $(PROG1) -lpthread
	$(MSG_OK)
$(PROG2) : $(SOURCE2:.cc=.o)
	$(CXX) $^ $(CXX_FLAGS) -o $(PROG2) -lpthread
	$(MSG_OK)
clear :
	rm interfaceIPC.o interfaceSite.o table_printer.o client.o serveur.o
