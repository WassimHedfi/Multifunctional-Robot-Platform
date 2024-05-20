import processing.serial.*;

Serial arduino; // Serial communication with Arduino
float temperature; // Temperature value (in °C)
float humidity; // Humidity value (in %)

void setup() {
  size(400, 200); // Set canvas size
  arduino = new Serial(this, "COM7", 9600); // Replace "COM3" with your Arduino's port
  arduino.bufferUntil('\n'); // Read data until newline character
}

void draw() {
  background(255); // White background

  // Read data from Arduino
  while (arduino.available() > 0) {
    String data = arduino.readStringUntil('\n');
    if (data != null) {
      String[] values = data.trim().split(",");
      if (values.length == 2) {
        temperature = float(values[0]);
        humidity = float(values[1]);
      }
    }
  }

  // Draw temperature bar (red)
  fill(255, 0, 0); // Red color
  float thermometerHeight = map(temperature, 15, 35, 0, height);
  rect(80, height - thermometerHeight, 50, thermometerHeight);
  textAlign(CENTER);
  fill(0);
  text("Temperature", 40, height - 100); // Label
  text(nf(temperature, 0, 1) + "°C", 40, height / 2 - 20);


  // Draw humidity bar (blue)
  fill(0, 0, 255); // Blue color
  float dropletSize = map(humidity, 50, 100, 10, height);
  rect(270, height - dropletSize, 50, dropletSize);
  textAlign(CENTER);
  fill(0);
  text("Humidity", 360, height - 100); // Label
  text(nf(humidity, 0, 1) + "%", 360, height / 2 - 20); // Actual value
}
