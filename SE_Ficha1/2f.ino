int h = 4;
int o = 3;

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void ponto() {
  digitalWrite(13, HIGH);
  Serial.print(".");
  delay(500);
  digitalWrite(13, LOW);
  delay(300);
}

void traco() {
  digitalWrite(13, HIGH);
  Serial.print("-");
  delay(1500);
  digitalWrite(13, LOW);
  delay(300);
}

// H = ....
void h_letra() {
  for(int i = 0; i < 4; i++) ponto();
}

// E = .
void e_letra() {
  ponto();
}

// L = .-..
void l_letra() {
  ponto();
  traco();
  ponto();
  ponto();
}

// O = ---
void o_letra() {
  for(int i = 0; i < 3; i++) traco();
}

// W = .--
void w_letra() {
  ponto();
  traco();
  traco();
}

// R = .-.
void r_letra() {
  ponto();
  traco();
  ponto();
}

// D = -..
void d_letra() {
  traco();
  ponto();
  ponto();
}

void espaço_entre_letras() {
  delay(1000);
}

void espaço_entre_palavras() {
  delay(2000);
}

void loop() {

  // -------- HELLO --------
  h_letra(); espaço_entre_letras();
  e_letra(); espaço_entre_letras();
  l_letra(); espaço_entre_letras();
  l_letra(); espaço_entre_letras();
  o_letra(); espaço_entre_palavras();

  // -------- WORLD --------
  w_letra(); espaço_entre_letras();
  o_letra(); espaço_entre_letras();
  r_letra(); espaço_entre_letras();
  l_letra(); espaço_entre_letras();
  d_letra(); espaço_entre_palavras();

  // Repetir mensagem após pausa
  delay(5000);
}
