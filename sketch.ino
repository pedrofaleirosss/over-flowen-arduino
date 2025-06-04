// Pedro Faleiros - 562523
// Luan Felix - 565541
// João Lopes - 565737

// Inclusão das bibliotecas necessárias
#include <Wire.h>  // Comunicação I2C
#include <LiquidCrystal_I2C.h>  // Controle do display LCD com interface I2C
#include <Servo.h>  // Controle do servo motor
#include <EEPROM.h>  // Leitura e escrita na memória EEPROM

// Inicializa o LCD com endereço I2C 0x27 e tamanho 16x2
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Definição dos pinos dos sensores e atuadores
#define TRIG_PIN 9
#define ECHO_PIN 10

#define LED_VERDE 2
#define LED_AMARELO 3
#define LED_VERMELHO 4
#define BUZZER 5
#define SERVO_PIN 6

// Controle do buzzer (evita tocar continuamente)
bool buzzerAtivo = false;
unsigned long buzzerStartTime = 0;

// Cria objeto do servo
Servo barreira;

// Variáveis do menu e medição
int menu = 0;
int altura_sensor = 150;  // Altura padrão entre o sensor e o chão
int nivel_agua = 0;  // Nível atual da água


// Caractere personalizado
byte customChar[] = {
  B00000,
  B00000,
  B00110,
  B11001,
  B00000,
  B00110,
  B11001,
  B00000
};

// Símbolo Alerta
byte image31[8] = {B00100, B00100, B00000, B00100, B00000, B00000, B11111, B00000};
byte image30[8] = {B00100, B00100, B01000, B01000, B10000, B10000, B01111, B00000};
byte image32[8] = {B00100, B00100, B00010, B00010, B00001, B00001, B11110, B00000};
byte image14[8] = {B00000, B00000, B00000, B00000, B00000, B00001, B00001, B00001};
byte image16[8] = {B00000, B00000, B00000, B00000, B00000, B10000, B10000, B10000};
byte image15[8] = {B00000, B01110, B10001, B10001, B00100, B00100, B00100, B00100};


// Desenha o ícone de onda no canto do LCD
void desenhaIcone() {
  lcd.createChar(0, customChar);
  lcd.setCursor(0, 0); lcd.write(0);
  lcd.setCursor(0, 1); lcd.write(0);
  lcd.setCursor(1, 0); lcd.write(0);
  lcd.setCursor(1, 1); lcd.write(0);
  lcd.setCursor(2, 0); lcd.write(0);
  lcd.setCursor(2, 1); lcd.write(0);
}

// Função que ícone de alerta no LCD
void alertImage() {
  lcd.createChar(0, image31);
  lcd.createChar(1, image30);
  lcd.createChar(2, image32);
  lcd.createChar(3, image14);
  lcd.createChar(4, image16);
  lcd.createChar(5, image15);

  lcd.setCursor(14, 1);
  lcd.write(byte(0));
  lcd.setCursor(13, 1);
  lcd.write(byte(1));
  lcd.setCursor(15, 1);
  lcd.write(byte(2));
  lcd.setCursor(13, 0);
  lcd.write(byte(3));
  lcd.setCursor(15, 0);
  lcd.write(byte(4));
  lcd.setCursor(14, 0);
  lcd.write(byte(5));
}


// Configuração inicial
void setup() {
  lcd.init();
  lcd.clear();
  lcd.backlight();

  // Animação "Overflowen Iniciando..." no LCD
  desenhaIcone();

  lcd.setCursor(4, 0);
  lcd.print("O");
  delay(200);
  lcd.print("v");
  delay(200);
  lcd.print("e");
  delay(200);
  lcd.print("r");
  delay(200);
  lcd.print("F");
  delay(200);
  lcd.print("l");
  delay(200);
  lcd.print("o");
  delay(200);
  lcd.print("w");
  delay(200);
  lcd.print("e");
  delay(200);
  lcd.print("n");
  delay(200);
  lcd.setCursor(4, 1);
  lcd.print("I");
  delay(200);
  lcd.print("n");
  delay(200);
  lcd.print("i");
  delay(200);
  lcd.print("c");
  delay(200);
  lcd.print("i");
  delay(200);
  lcd.print("a");
  delay(200);
  lcd.print("n");
  delay(200);
  lcd.print("d");
  delay(200);
  lcd.print("o");
  delay(200);
  lcd.print(".");
  delay(200);
  lcd.print(".");
  delay(200);
  lcd.print(".");
  delay(200);

  Serial.begin(9600);  // Inicializa comunicação serial

  // Define os modos dos pinos
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  
  // Posiciona a barreira em aberto (posição inicial)
  barreira.attach(SERVO_PIN);
  barreira.write(0);

  // Verifica se há altura salva na EEPROM
  byte flag;
  EEPROM.get(0, flag);

  if (flag == 0xAB) {
    EEPROM.get(1, altura_sensor);
  } else {
    altura_sensor = 150; // Valor padrão
  }

  // Exibe menu inicial no Serial
  Serial.println("====================== Menu ======================");
  Serial.print("[0] Menu - [1] Definir Altura do Sensor - [2] - Exibir alrura do nível da água");
  Serial.print("\n");
  Serial.print("\n");
}

// Loop principal do programa
void loop() {
  long duration;
  float distancia_cm;

  // Envia um pulso para medir
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Mede o tempo do retorno
  duration = pulseIn(ECHO_PIN, HIGH);

  // Converte para centímetros (dividido por 58)
  distancia_cm = duration / 58.0;
  
  nivel_agua = altura_sensor - distancia_cm;

  // Verifica o nível da água e toma ações
  if (nivel_agua <= 5) {
    digitalWrite(LED_VERDE, HIGH);
    digitalWrite(LED_AMARELO, LOW);
    digitalWrite(LED_VERMELHO, LOW);
    noTone(BUZZER);
    buzzerAtivo = false;
    barreira.write(0); // Abre barreira
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Agua:");
    lcd.setCursor(6, 0);
    lcd.print(nivel_agua);
    lcd.print(" cm");
    lcd.setCursor(0, 1);
    lcd.print("OK");
  } 
  else if (nivel_agua > 5 && nivel_agua <= 10) {
    // Nível de alerta
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_AMARELO, HIGH);
    digitalWrite(LED_VERMELHO, LOW);
    noTone(BUZZER);
    buzzerAtivo = false;
    barreira.write(90); // Fecha barreira
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Agua:");
    lcd.setCursor(6, 0);
    lcd.print(nivel_agua);
    lcd.print(" cm");
    lcd.setCursor(0, 1);
    lcd.print("Alerta!");
    alertImage();
  }
  else {
    // Nível crítico
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_AMARELO, LOW);
    digitalWrite(LED_VERMELHO, HIGH);

    barreira.write(90); // Fecha a barreira

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Agua:");
    lcd.setCursor(6, 0);
    lcd.print(nivel_agua);
    lcd.print(" cm");
    lcd.setCursor(0, 1);
    lcd.print("Critico!");
    alertImage();

    // Ativa o buzzer por 3 segundos
    if (!buzzerAtivo) {
      tone(BUZZER, 200);
      buzzerStartTime = millis();
      buzzerAtivo = true;
    }
  }

  // Desliga o buzzer após 3 segundos
  if (buzzerAtivo && millis() - buzzerStartTime >= 3000) {
    noTone(BUZZER);
    buzzerAtivo = false;
  }

    // Leitura do Serial (controle do menu)
  if (Serial.available() > 0 && menu != 1) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    if (input == "1") {
      menu = 1;
    } else if (input == "2") {
      menu = 2;
    } else if (input == "0") {
      menu = 0;
    } else {
      for (int i = 0; i < 20; i++) {
        Serial.println();
      }
      Serial.println("Número inválido.");
    }
  }

  // Menu principal (opção 0)
  if (menu == 0) {
    for (int i = 0; i < 20; i++) {
      Serial.println();
    }

    Serial.println("====================== Menu ======================");
    Serial.print("[0] Menu - [1] Definir Altura do Sensor - [2] - Exibir alrura do nível da água");
    Serial.print("\n");
    Serial.print("\n");
  } else if (menu == 1) {
    for (int i = 0; i < 20; i++) {
      Serial.println();
    }

    // Definir altura do sensor (salva na EEPROM)
    Serial.println("========== Configuração de Alrua do Sensor ==========");
    Serial.println("Digite a distância entre o sensor de distância e o chão em centímetros: ");

    String input = Serial.readStringUntil('\n');
    input.trim();

    if (input != "") {
      altura_sensor = input.toInt();
      Serial.print("Alrua do sensor de distância alterada para: ");
      Serial.print(altura_sensor);
      Serial.println(" centímetros.");

      EEPROM.put(0, (byte)0xAB);        // Marca que a EEPROM agora tem valor salvo
      EEPROM.put(1, altura_sensor);     // Salva a altura a partir da posição 1
      Serial.println("Altura salva na memória EEPROM.");

      delay(5000);

      menu = 0;
    }
  } else if (menu == 2) {
    // Exibe o nível atual da água
    Serial.print("Nível da água: ");
    Serial.print(nivel_agua);
    Serial.println(" centímetros");
  }

  delay(3000);  // Tempo entre leituras
}
