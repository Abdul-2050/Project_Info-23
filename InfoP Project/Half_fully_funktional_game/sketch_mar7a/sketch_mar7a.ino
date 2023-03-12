// Define the pins for the joysticks
#define X_PIN_1 A0
#define Y_PIN_1 A1
#define X_PIN_2 A2
#define Y_PIN_2 A3

const int buttonPin = 3;

// Define the filter coefficients
const float FILTER_ALPHA = 0.2;

// Define the range for the mapped y-value
const int Y_MIN = 55;
const int Y_MAX = 595;

// Variables for storing the filtered values
float x_filtered_1 = 0.0;
float y_filtered_1 = 0.0;
float x_filtered_2 = 0.0;
float y_filtered_2 = 0.0;

void setup() {
  // Initialize the serial communication for debugging purposes
  Serial.begin(115200);

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(8, OUTPUT);
}

void loop() {
  // Read the raw values from the joysticks
  int x_raw_1 = analogRead(X_PIN_1);
  int y_raw_1 = analogRead(Y_PIN_1);
  int x_raw_2 = analogRead(X_PIN_2);
  int y_raw_2 = analogRead(Y_PIN_2);
  
  // Check if the joysticks are in the neutral position
  bool neutral_1 = (y_raw_1 > 470 && y_raw_1 < 550);
  bool neutral_2 = (y_raw_2 > 470 && y_raw_2 < 550);
  
  // Only update the filtered values if the joystick is not in the neutral position
  if (!neutral_1) {
    // Apply the filter to the x-axis value of the first joystick
    x_filtered_1 = x_filtered_1 * (1 - FILTER_ALPHA) + x_raw_1 * FILTER_ALPHA;
    
    // Apply the filter to the y-axis value of the first joystick, but limit the rate of change
    float y_target_1 = y_raw_1 * (1 - FILTER_ALPHA) + y_filtered_1 * FILTER_ALPHA;
    float y_delta_1 = y_target_1 - y_filtered_1;
    if (y_delta_1 > 10) {
      y_filtered_1 += 10;
    } else if (y_delta_1 < -10) {
      y_filtered_1 -= 10;
    } else {
      y_filtered_1 = y_target_1;
    }
  }
  
  if (!neutral_2) {
    // Apply the filter to the x-axis value of the second joystick
    x_filtered_2 = x_filtered_2 * (1 - FILTER_ALPHA) + x_raw_2 * FILTER_ALPHA;
    
    // Apply the filter to the y-axis value of the second joystick, but limit the rate of change
    float y_target_2 = y_raw_2 * (1 - FILTER_ALPHA) + y_filtered_2 * FILTER_ALPHA;
    float y_delta_2 = y_target_2 - y_filtered_2;
    if (y_delta_2 > 10) {
      y_filtered_2 += 10;
    } else if (y_delta_2 < -10) {
      y_filtered_2 -= 10;
    } else {
      y_filtered_2 = y_target_2;
    }
  }

  // Map the y-axis values to the new range
  float y_filtered_mapped_1 = map(y_filtered_1, 0, 1023, Y_MIN, Y_MAX);
  float y_filtered_mapped_2 = map(y_filtered_2, 0, 1023, Y_MIN, Y_MAX);


// Debug output
  Serial.print( y_filtered_mapped_1);
  Serial.print(";"); // add a comma to separate the values
  Serial.print(y_filtered_mapped_2);
  Serial.print(";");

  delay(10);


   int buttonState = digitalRead(buttonPin);

  if (buttonState == LOW) {
    Serial.print("HIGH");
    digitalWrite(8, HIGH);
    Serial.println();
  } else {
    Serial.print("LOW");
    digitalWrite(8, LOW);
    Serial.println();
  }

}


