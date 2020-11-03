#include <Wire.h>
#include <Adafruit_GFX.h> // OLED kuvari kuvamiseks
#include <Adafruit_SSD1306.h> // OLED kuvari kuvamiseks
#define SCREEN_WIDTH 128 // OLED kuvari laius, pikslites
#define SCREEN_HEIGHT 64 // OLED kuvari kõrgus, pikslites
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int counter = 0; // Määratleb muutujaid
int currentState = 0;
int previousState = 0;
const int trigPin = 10;
const int echoPin = 9;
long duration;
float distance;

void setup() {
    Serial.begin(9600);
      if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Adresseerib 0x3C 128x64
      Serial.println(F("SSD1306 allocation failed"));
      for(;;); 
      }  
    delay(500);
    display.clearDisplay(); // Kuvab kuvarile teksti andmeid (Kasutatud valmis kirjutatud OLED koodi)
    display.setTextSize(2.9);
    display.setTextColor(WHITE);
    display.setCursor(20,25);
    display.print("LOENDUR");  
    display.display(); 
    pinMode(trigPin, OUTPUT); // Määrab trigPin Outputiks
    pinMode(echoPin, INPUT); // Määrab echoPin Inputiks  
    previousState = 0;
}

void loop() {
    previousState = currentState;
    digitalWrite(trigPin, LOW); // Määrab trigPin LOW'iks  (Kasutatud valmis kirjutatud HF sensori koodi)
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); // Määrab trigPin HIGH'ks 10 mikrosekundiks
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH); // Loeb echoPin sisendit ja tagastab helilaine levimise kiiruse mikrosekundites
    distance = duration*0.034/2; // Kalkuleerib kauguse
      if (distance <= 9.5) {  // Kui distants <= 9.5 , siis võtab väärtuseks 1
      currentState = 1;
      }
        else { // Kui väärtus on suurem 9.5'st, siis võtab väärtuseks 0
        currentState = 0;
        }
          if (currentState == 0 && previousState == 1){ // Kontrollib, et esimene väärtus ei ole võrdne teisega
          if (currentState = 1){
          counter = counter + 1;} // Kui on, liidab ta olemasolevale +1 juurde
    Serial.print("counter: "); // Pantud kontrolliks sisse, et vaadata Serial Monitoris ka
    Serial.println(counter);
    display.clearDisplay(); // Kuvab uut väärtust OLED kuvaril
    display.setTextSize(5);
    display.setTextColor(WHITE);
    display.setCursor(38,10);
    display.println(counter);
    display.display();
    delay(500);
 }
}
