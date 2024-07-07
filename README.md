# Zestaw 5
Projekt umożliwia generowanie obietktów na płótnie ASCII. Projekt składa się z kilku klas: Canvas, ASCIICanvas, Figure, Rectangle, Square, Circle oraz Light. Klasy te pozwalają na rysowanie figur geometrycznych na płótnie ASCII oraz generowanie cieni za pomocą źródła światła.

## Jak używać projektu

**Kompilacja**\
Aby skompilować projekt, przejdź do katalogu z projektem i wykonaj polecenie:
> g++ -o zestaw5 zestaw5.cpp

**Uruchomienie**\
Po skompilowaniu projektu można go uruchomić, podając jako argument nazwę pliku konfiguracyjnego:
> ./zestaw5 plik.txt

**Format pliku konfiguracyjnego**\
Przykładowy format pliku konfiguracyjnego:

canvas 30 15\
output output.txt\
empty_symbol   \
circle 8 7 2 0\
square 20 3 3 #\
rectangle 22 12 4 2 @\
light 15 3 .

gdzie:
- **canvas width height**: Definiuje rozmiar płótna ASCII.
- **output filename**: Określa nazwę pliku, do którego zostanie zapisane płótno ASCII.
- **empty_symbol symbol**: Ustala symbol pustego miejsca na płótnie.
- **rectangle x y width height symbol**: Tworzy prostokąt na płótnie ASCII.
- **square x y size symbol**: Tworzy kwadrat na płótnie ASCII.
- **circle x y radius symbol**: Tworzy koło na płótnie ASCII.
- **light x y symbol**: Dodaje źródło światła na płótnie ASCII oraz definiuje symbol rzucanego cienia.

