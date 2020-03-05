#include <Arduino.h>

/*
  TO DO
  1. Konfiguracja wstępna
    1.1 Stworzenie tymczasowego AP
    1.2 Strona konfiguracyjna
    1.2.1 Nazwa Sieci
    1.2.2 Hasło
    1.2.3 (opcjonalne)
  2. Nowy AP
    2.1 WebSocket z danymi prosto na stronę
    2.2 (opcjonalne) Data logger? W pamięci urządzenia można by przechowywać x danych
    2.3 (opcjonalne) Jakieś fajny wykresik albo coś?
  3. Przycisk RESET do fabrycznych
    3.1 W momecie setup wykrywać czy w czasie uruchamiania przycisk zewnętrzny był wciśnięty?
      3.1.1 Jeśli tak to wyczyścić config i wrócić do Pkt1
    3.2. (opcjonalne) reset do fabrycznych po zalogowaniu do AP
  4. (WISH LIST)
    4.1. Coś jeszcze?
*/

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Hello world");
  delay(1000);
}