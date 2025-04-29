int sensorCentro = A2;
int sensorDireita = A0;
int sensorEsquerda = A1;

int ENA = 5;
int IN1 = 6;
int IN2 = 7;
int IN3 = 8;
int IN4 = 9;
int ENB = 10;

int valorLinha = 500; // Valor de referência para detectar a linha
int fspeed = 100;
int cspeed = 120;

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  Serial.begin(9600); // Inicializa a comunicação serial para debug (opcional)
}

void loop() {
  int leituraCentro = analogRead(sensorCentro);
  int leituraDireita = analogRead(sensorDireita);
  int leituraEsquerda = analogRead(sensorEsquerda);

  Serial.print("Centro: ");
  Serial.print(leituraCentro);
  Serial.print(" Direita: ");
  Serial.print(leituraDireita);
  Serial.print(" Esquerda: ");
  Serial.println(leituraEsquerda);
 if(leituraCentro > valorLinha && leituraEsquerda > valorLinha && leituraDireita > valorLinha){
  seguirEmFrente();
 }
 else if (leituraCentro > valorLinha && leituraDireita > valorLinha){
   if (leituraCentro > leituraDireita){
    seguirEmFrente();
   }
   else{
   virarDireita();
   }
  }
  
  else if (leituraCentro > valorLinha && leituraEsquerda > valorLinha){
   if (leituraCentro > leituraEsquerda){
    seguirEmFrente();
   }
   else{
   virarEsquerda();
   }
  }
  else if (leituraCentro > valorLinha && leituraDireita < valorLinha && leituraEsquerda < valorLinha) {
    seguirEmFrente();
  } else if (leituraEsquerda > valorLinha) {
    virarEsquerda();
  } else if (leituraDireita > valorLinha) {
    virarDireita();
  } else {
    seguirEmFrente();
  }

  delay(10);
}

void seguirEmFrente() {
  analogWrite(ENA, fspeed);
  digitalWrite(IN1, LOW); // Inverteu o sentido
  digitalWrite(IN2, HIGH); // Inverteu o sentido
  analogWrite(ENB, fspeed);
  digitalWrite(IN3, LOW); // Inverteu o sentido
  digitalWrite(IN4, HIGH); // Inverteu o sentido
}

void virarEsquerda() {
  analogWrite(ENA, cspeed);
  digitalWrite(IN1, LOW); // Inverteu o sentido
  digitalWrite(IN2, HIGH); // Inverteu o sentido
  analogWrite(ENB, cspeed);
  digitalWrite(IN3, HIGH); // Inverteu o sentido
  digitalWrite(IN4, LOW); // Inverteu o sentido
  delay(80);
}

void virarDireita() {
  analogWrite(ENA, cspeed);
  digitalWrite(IN1, HIGH); // Inverteu o sentido
  digitalWrite(IN2, LOW); // Inverteu o sentido
  analogWrite(ENB, cspeed);
  digitalWrite(IN3, LOW); // Inverteu o sentido
  digitalWrite(IN4, HIGH); // Inverteu o sentido
  delay(80);
}

void parar() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}
