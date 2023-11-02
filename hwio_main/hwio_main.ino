
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int analogPin = A0;
int value;      //variable que almacena la lectura analógica raw de pot
int litros_s;   //variable que almacena la lectura analógica raw de flujo
int pwm_motores;   //posicion del potenciometro en tanto por ciento
int position;   //posicion del potenciometro en tanto por ciento
int ENA = 11;   //ENB conectada al pin 3 de Arduino
int ENB = 10;    // ENB conectada al pin 3 de Arduino
int IN1 = 2;    // Input3 conectada al pin 5
int IN2 = 3;    // Input4 conectada al pin 4 
int IN3 = 4;    // Input3 conectada al pin 5
int IN4 = 5;    // Input4 conectada al pin 4 

void setup() {
 Serial.begin(115200);
 if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
   Serial.println(F("SSD1306 allocation failed"));
   for(;;);
 }
 pinMode (ENA, OUTPUT); 
 pinMode (ENB, OUTPUT); 
 pinMode (IN1, OUTPUT);
 pinMode (IN2, OUTPUT);
 pinMode (IN3, OUTPUT);
 pinMode (IN4, OUTPUT);
 //Preparamos la salida para que el motor gire en un sentido
 digitalWrite (IN1, HIGH);
 digitalWrite (IN2, LOW);
 digitalWrite (IN3, HIGH);
 digitalWrite (IN4, LOW);

 display.setTextColor(WHITE);
 delay(2000);
 display.clearDisplay();
 
}

void loop() {
  delay(500);
  display.clearDisplay();
  // Aplicamos PWM al pin ENB, haciendo girar el motor, cada 2 seg aumenta la velocidad
  value = analogRead(analogPin);       // realizar la lectura analógica raw
  pwm_motores = map(value, 0, 1023, 0, 255);  // convertir a porcentaje
  position = map(pwm_motores, 0, 255, 0, 100);  // convertir a porcentaje
  //...hacer lo que se quiera, con el valor de posición medido
  analogWrite(ENA,pwm_motores);
  analogWrite(ENB,pwm_motores);
  
  //Mostramos datos en la pantalla
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("Velocidad");
  display.setTextSize(2);
  display.setCursor(0,10);
  display.print(position);
  display.print(" ");
  display.print(" %");
  
  // display humidity
  display.setTextSize(1);
  display.setCursor(0, 35);
  display.print("Flujo de agua: ");
  display.setTextSize(2);
  display.setCursor(0, 45);
  display.print(litros_s);
  display.print("L/s");

  Serial.println(position);
  display.display();

}
