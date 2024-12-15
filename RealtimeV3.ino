// Variabel filter
float yn1 = 0;  // Output sebelumnya
float xn1 = 0;  // Input sebelumnya

// Koefisien filter IIR orde 1
float b0 = 0.42080778;
float b1 = 0.42080778;
float a1 = -0.15838444;

// Variabel untuk interval sampling
unsigned long previousMicros = 0;
const unsigned long interval = 500;  // Interval sampling dalam mikrosekon (500 µs = 2 kHz)

void setup() {
  Serial.begin(115200); 
  while (!Serial) {
    ; 
  }
}

void loop() {
  unsigned long currentMicros = micros();

 
  if (currentMicros - previousMicros >= interval) {
    previousMicros = currentMicros;

    // Membaca nilai sensor
    int sensorValue = analogRead(A0);  
    float xn = (float)sensorValue;

    // Filter low-pass
    // y[n] = b0 * x[n] + b1 * x[n-1] - a1 * y[n-1]
    float yn = b0 * xn + b1 * xn1 - a1 * yn1;

    // Update nilai sebelumnya untuk iterasi berikutnya
    xn1 = xn;
    yn1 = yn;

    // Menampilkan data
    Serial.print(xn);  // Data asli
    Serial.print(" ");
    Serial.println(yn); // Data filter
  }
}
