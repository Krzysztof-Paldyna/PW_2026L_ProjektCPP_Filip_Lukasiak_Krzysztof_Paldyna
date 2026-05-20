# PW_2026L_ProjektCPP_Filip_Lukasiak_Krzysztof_Paldyna
Celem projektu jest zaprogramowanie w języku C++ turowej gry karcianej, z szatą graficzną w SFML

PLAN PROGRAMU:

generowanie klatek:
- EKRAN MA STAŁĄ ROZDZIELCZOŚĆ
- OPCJONALNE stabilne max fps za pomocą chrono - 24 na start (mierzymy czas na początku i na końcu klatki, jeżeli delta t jest mniejsza od 1/24 sekundy to sleep(1/24 - delta t) )
- rysowanie klatki: klasa EKRAN przechowująca (vector) wszystkie OBIEKTY GRAFICZNE w kolejności od tła do highlightowanego obiektu pod myszką
-   klasa OBIEKT GRAFICZNY - ładuje sprite/tekst (OPCJONALNIE PROXY, master lista wszystkich spriteów),
    zawiera swoją pozycję na ekranie oraz rozmiar, do sprawdzania czy mysz jest nad obiektem / czy obiekt został kliknięty
    zawiera czas życia (ile ma być wyświetlany, po tym czasie jest usuwany)

klasa KARTA:
- grafika:
  - prostokąt SFMLowy, zawiera mały textbox na górze (nazwa), miejsce na sprite i textbox na dole (opis działania) - jak karta jest pod myszką to jest rysowana nad wszystkim innym,
    (OPCJONALNE jak kliknięta to pod nią rysujemy odrobinkę większy kolorowy prostokąt, aby zaznaczyć wybór karty dla użytkownika, kolor zielony jak możliwe jest użycie karty, czerwone mignięcie jak nie)
- gameplay:
  - zawiera metodę zadającą obrażenia, wywoływane efekty itp
  - status effekt - zawiera to co robi, oraz ENUM KIEDY WYWOŁAĆ(0 -początek tury, 1 - tura, 
 
klasa POSTAĆ:
- grafika:
  - sprite oraz pasek zdrowia z textboxem pokazującym zdrowie (np. 21/100), pasek zdrowia można zrobić za pomocą dwóch prostokątów: pełnowymiarowy biały/czarny pod spodem, i przeskalowany czerwony w osi X (np 0.21)
- dane:
  - zdrowie (int),
  - vector aktywnych status effektów (TYPY), który jest iterowany w każdej turze
  - typy - (master tablica zawierająca mnożniki skuteczności)
  - metody:
    - przyjmowanie obrażeń (sprawdza typ POSTACI i KARTY, STAB(typ postaci atakującej), status effekty itp ZAWSZE SPRAWDZA CZY HP <= 0),
    - umożliwianie KARTOM sprawdzanie, czy jest dany status effect
   
przebieg tury:
  - gracz:
    - dobranie kart ze stosu, jeżeli stos jest pusty przerzuca stos kart odrzuconych na stos i go przetasowuje
    - status effekty na początku tury
    - granie KARTAMI
    - przycisk koniec tury
    - status effekty na końcu tury
    - odrzucenie kart na stos kart odrzuconych
  - przeciwnik:
    - status effekty na początku tury
    - jedna akcja wybrana losowo LUB cyklicznie z listy akcji dla danego wroga
    - status effekty na końcu tury 

pętkla gry poza walkami: 
  podliczenie XP, wybór nowych kart do dorzucenia do stosu, MOŻE EWOLUCJA (nowe abilitki - permanentne status effekty, nowe typy ect)
  plik zapisu postaci/tury
  rosnąca trudność - trudniejsi przeciwnicy, przeciwnicy startujący z buffami ect
