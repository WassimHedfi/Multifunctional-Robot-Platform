import processing.serial.*;

Serial arduino; // Serial port for communication with Arduino
float ax, ay, az; // Accelerometer data

void setup() {
  size(800, 600); // Set canvas size
  arduino = new Serial(this, Serial.list()[0], 9600); // Change the port name as needed
}

void draw() {
  background(255); // White background

  // Read accelerometer data from Arduino
  if (arduino.available() > 0) {
    String data = arduino.readStringUntil('\n');
    if (data != null) {
      String[] values = data.trim().split(",");
      if (values.length == 3) {
        ax = float(values[0]);
        ay = float(values[1]);
        az = float(values[2]);
      }
    }
  }

  // Calculate tilt angles (assuming a car-like visualization)
  float tiltX = map(ax, -1, 1, -PI / 4, PI / 4); // Tilt around X-axis
  float tiltY = map(ay, -1, 1, -PI / 4, PI / 4); // Tilt around Y-axis

  // Draw car tilted over X-axis (side view)
  pushMatrix();
  translate(width / 4, height / 2); // Position left car
  rotate(tiltX); // Apply X-axis tilt
  fill(0, 150, 200); // Blue color
  rect(-60, -30, 120, 60); // Bigger car body
  fill(255); // White color
  ellipse(-30, 20, 40, 40); // Front wheel (bigger)
  ellipse(30, 20, 40, 40); // Rear wheel (bigger)
  textAlign(CENTER);
  fill(0);
  text("Side View", 0, -40); // Label
  popMatrix();

  // Draw car tilted over Y-axis (front view)
  pushMatrix();
  translate(3 * width / 4, height / 2); // Position right car
  rotate(tiltY); // Apply Y-axis tilt
  fill(0, 150, 200); // Blue color
  rect(-60, -30, 120, 60); // Bigger car body
  fill(255); // White color
  rect(-70, 10, 10, 40); // Front wheel (bigger)
  rect(60, 10, 10, 40); // Rear wheel (bigger)
  textAlign(CENTER);
  fill(0);
  text("Front View", 0, -40); // Label
  popMatrix();
}
