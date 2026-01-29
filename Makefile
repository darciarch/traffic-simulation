CXX = g++
# Boost başlık dosyaları ve C++ standartı
CXXFLAGS = -std=c++17 -I/opt/homebrew/include -I/usr/local/include
# Boost kütüphane yolları ve gerekli linkler
LDFLAGS = -L/opt/homebrew/lib -L/usr/local/lib

SRC = Main.cpp Fahrzeug.cpp PKW.cpp Fahrrad.cpp Weg.cpp Simulationsobjekt.cpp \
      Verhalten.cpp Fahrausnahme.cpp SimuClient.cpp SimuClientSocket.cpp Kreuzung.cpp
TRG = Main

all: $(TRG)

$(TRG): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TRG) $(LDFLAGS)
	./$(TRG)

run: $(TRG)
	./$(TRG)

clean:
	rm -f $(TRG)