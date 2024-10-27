import processing.serial.*;

Serial arduinoPort;
String receivedData = ""; // Variable to store received data from Arduino
String currentQuestion = ""; // Variable to store the current question
boolean waitingForResponse = false; // Flag to indicate whether waiting for user's response
String points = "";

void setup() {
  fullScreen(); // Set the display to fullscreen
  arduinoPort = new Serial(this, "COM5", 9600); // Replace "COM5" with your Arduino's port
  arduinoPort.bufferUntil('\n'); // Set buffer until new line
  String intro = "Welcome to Jupiter! To start playing, roll the ball into one of the holes!";
  int midW = width / 2;  // Calculate midW based on the width of the window
  int midL = height / 2; // Calculate midL based on the height of the window

  textSize(125);
  fill(255, 255, 255);
  textAlign(CENTER);
  rectMode(CENTER);
  imageMode(CENTER);
  text(intro, midW, midL - 175, 2000, 500); 

}

void draw() {
  background(135, 206, 235); // Set background color

  // Display the current question
  textSize(32);
  textAlign(CENTER);
  fill(255);
  text(currentQuestion, width/2, height/2 - 50);

  // If waiting for response, display instructions
  if (waitingForResponse) {
    textSize(50);
    fill(255, 0, 0);
    text("Press blue to select True o False", width/2, height/2 + 50);
  }

  // Display the result received from Arduino
  textSize(40);
  fill(255);
  text(receivedData, width/2, height/2 + 100);
}

void serialEvent(Serial arduinoPort) 
{
  receivedData = arduinoPort.readStringUntil('\n'); // Read the serial data
}

void keyPressed() {
  if(points.contains("Correct!")){
      background(135,206,235);  // Set background color to white
      fill(0, 255, 0);  // Set text color to green
      textSize(100);     // Set text size
      textAlign(CENTER, CENTER);  // Align text to center
      text("Yay! You did it!", width/2, height/2); 
    }
    if(points.contains("Incorrect!")){
      background(135,206,235);  // Set background color to white
      fill(0, 255, 0);  // Set text color to green
      textSize(100);     // Set text size
      textAlign(CENTER, CENTER);  // Align text to center
      text("It's okay! You were so close! The right answer was true", width/2, height/2); 
    }
    waitingForResponse = false;
  }

void displayQuestion(String question) {
  currentQuestion = question;
  waitingForResponse = true; // Set flag to true when waiting for response
}
