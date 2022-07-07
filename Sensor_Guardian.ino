/*
  Este programa muestra los datos de metano con el sensor MQ-4 y el valor de la Humedad relativa y temperatura con el sensor DTH11, imprimiendo
  en el monitor serial y serial plotter los valores obtenidos 
  Autor: Club Guardas Urbanos y G4N1D 
  Agradecimientos: bitwiseAr  

*/

#include "DHT.h"
#define DHTPIN 2 // Pin entrada donde esta el sensor
#define DHTTYPE DHT22 // Sensor DHT22 (AM2302)

DHT dht(DHTPIN, DHTTYPE); //llamado al medidor DHT11
int pinRedLed = 3; //pin conexion del led
int TRESHOLD = 200; //parametro limite para la alarma del gas
int valor_gas;      // almacena valor leido del sensor
int pinZumbador = 5; //pin conexion zumbador
int frecuencia = 220; //frecuencia a la zuena el zumbador (LA)


void setup(){ //Imprime los datos de la cabecera
  Serial.begin(9600);   // inicializa comunicacion serie a 9600 bps
  Serial.println("Iniciando Sensor Guardian V1.1...");
  Serial.println("Club Cientifico Guardas Urbanos");
  Serial.println("IE Concejo Municipal el Porvenir");
  Serial.println("--------------------------------");
  dht.begin();  // entradas digital del DHT11 requiere inicializacion
  pinMode(pinRedLed, OUTPUT); //establece el led rojo como salida
  // entradas analogica del MQ-4 no requiere inicializacion
  
}

void loop(){
  delay(2000); //Leer cada 2 segundos
  
  //Lecturas
  valor_gas = analogRead(A0); // Lee entrada A0 y asigna a variable valor_gas
  float h = dht.readHumidity(); // Lee entrada de la humedad.
  float t = dht.readTemperature(); // Lee entrada temperatura en Centigrados. 

  //Imprime en pantalla
  Serial.print("Valor Metano: "); // Imprime las palabras Valor Gas
  Serial.println(valor_gas);  // imprime en monitor serial el dato valor_gas
  Serial.print("Humedad relativa: "); // Imprime la palabra humedad.
  Serial.print(h);// Imprime el valor de la humedad 
  Serial.println("% "); // Imprimimos el texto *C
  Serial.print("Temperatura ambiental: "); // Imprime la palabra temperatura
  Serial.print(t); // Imprime el valor de temperatura en centigrados
  Serial.println("ºC "); // Imprimimos el texto *C
  Serial.println("--------------------------------");

  if (valor_gas >= TRESHOLD) { //si se sobrepasa Treshold alumbra el led y suena zumbador
    digitalWrite(pinRedLed, HIGH);
    tone(pinZumbador,frecuencia);
    delay(2000);
    }
    else { //si el Treshold baja el limite se apaga el led y el zumbador
     digitalWrite(pinRedLed, LOW);
     noTone(pinZumbador);
     delay(1000);
      }
     delay(500);     // breve demora de medio segundo
}
