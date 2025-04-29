// Definição dos pinos
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
int fspeed = 100;     // Velocidade padrão
int cspeed = 140;     // Velocidade de curva

// Variáveis do PID
double kp = 0.5;      // Ganho proporcional
double ki = 0.1;      // Ganho integral
double kd = 0.1;      // Ganho derivativo

double setpoint = 0;  // Ponto de referência (linha)
double input;         // Leitura dos sensores
double output;        // Saída do PID
double prevError = 0; // Erro anterior
double integral = 0;  // Integral do erro

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

  // Calcular o erro
  int erro = (leituraEsquerda - leituraDireita); // Diferença entre os sensores

  // PID
  double timeChange = 0.1; // Intervalo de tempo (ajuste conforme necessário)
  integral += erro * timeChange;
  double derivative = (erro - prevError) / timeChange;
  output = (kp * erro) + (ki * integral) + (kd * derivative);
  prevError = erro;

  // Ajustar a velocidade dos motores com base na saída do PID
  int velocidadeEsquerda = fspeed + output;
  int velocidadeDireita = fspeed - output;

  // Limitar as velocidades para não exceder 150
  velocidadeEsquerda = constrain(velocidadeEsquerda, 0, 150);
  velocidadeDireita = constrain(velocidadeDireita, 0, 150);

  // Controlar os motores
  analogWrite(ENA, velocidadeEsquerda);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  
  analogWrite(ENB, velocidadeDireita);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  delay(10); // Delay para estabilizar a leitura
}
