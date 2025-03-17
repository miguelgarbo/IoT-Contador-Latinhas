const int pinoSensor = 2; 
volatile int totalDeLatinhas = 0; 
int ultimoEstado = LOW; 

void setup() {
  pinMode(pinoSensor, INPUT);
  Serial.begin(115200); // Comunicação Serial com ESP8266
  Serial.println("0");
}

void loop() {
  int estadoAtual = digitalRead(pinoSensor); 

  // Detecta a mudança de estado no sensor 
  if (estadoAtual == HIGH && ultimoEstado == LOW) {
    totalDeLatinhas++;
    Serial.println(totalDeLatinhas); // Envia o valor via Serial para o ESP8266
  }

  ultimoEstado = estadoAtual; 
  delay(50); //evitando leituras duplicadas
}
