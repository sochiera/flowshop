TODO
====
  * mutacje - JS
    * złożenie z losową premutacją o ~75% punktów stałych
    * cykliczne przesunięcie całej permutacji
  * metody przeszukiwania lokalnego - JS
    * w jakimś promieniu od osobnika
    * coś mądrzejszego, np. tak jak w wyżażaniu
  * instancja problemu - KCH - zrobione
    * wyliczanie kosztu osobnika
  * wybór rodziców - KCH
    * k najlepszych
    * k zgodnie z przetransformowaną funkcją przystosowania
  * obcinanie populacji - JS
    * najlepsze
    * najlepsze z czwórki (rodzice, dzieci)
  * RPC - KCH
  * szkielet algorytmu - KCH


  
Potrzebne biblioteki i programy
===============================
  
  * boost::python
  * openMP (prawdopodobnie jest już wbudowane w kompilator)
  * cmake
  * python 2.7



Kompilacja
==========
  1. wejdź do program/cpp/build 
  2. cmake ..
  3. make


Dodawanie nowego pliku .cpp 
===========================
  W program/cpp/CMakeLists.txt trzeba dopisać jego nazwę do set(SOURCES ...)
