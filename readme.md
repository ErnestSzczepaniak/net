1. ETH 

Dopisałem typy eth jako stałe. Wielokrotnie powtarza się funkcja budowy nagłówka eth w protokołach warstwy wyższej. Może można by było to przemyśleć czy może nie dziedziczyć tej metody żeby nie powtarzać definicji w każdym protokole. 

2. ARP

Tutaj wszystko działa klient i serwer. Wysyła poprawne zapytania o adres MAC. Należy przemyśleć sprawę jak zbudować tablicę ARP. Odpowiada poprawnie na zapytania ARP.

3. IPv4

Problematyczne jest pole w nagłówku Fragment_offset oraz wszystkie Flags. Flagi mają po 3 bity a Fragment offset 13 bitów łącznie daje to 16. Więc fragment offset jest tak naprawdę "rozbity" na dwie zmienne 8 bitowe. Nie potrafiłem poprawnie wpisać tego pola trzeba wprowadzić jakieś manipulacje bitowe które obejmują jakby dwa pola. Czyli w  Bytefield & operator=(const T & value) sizeof(T) jest równy 2. 

4. ICMP 

Wysyłanie pingów działa. W linijkach kodu w których wydaje mi się że mogą wyagać objaśnienia lub powinny zostać zrobione lepiej dodałem komentarze. Odbieranie pingów nie działa. Głównie dlatego że trzeba wymyślić jakiś rozdzielacz pakietów który identyfikuje odpowiednio typ pakietu i przesyła do odpowiedniej obsługi. 