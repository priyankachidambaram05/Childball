const int sensor1Pin = 2; // Example pin for sensor 1
const int sensor2Pin = 3; // Example pin for sensor 2
const int sensor3Pin = 4; // Example pin for sensor 3
const int trueButtonPin = 5; //green
const int falseButtonPin = 6; //blue
String size[5] = {"Jupiter is the smallest planet in our solar system", "Jupiter is made mostly of gasses like hydrogen and helium", "Jupiter has a solid surface beneath its clouds",
"Jupiters nickname is “The Gas Giant”", "Jupiter cannot be seen with just the human eye" }; // Example category for sensor 1
bool answers1[] = {false, true, false, true, false}; // Example answers for sensor 1

String moons[5] = {"Jupiter has no moons orbiting around it", "Jupiter has rings similar to Saturn", "Jupiter has 20 moons",
 "Jupiter has more moons than any other planet in our solar system","Jupiters rings are easy to see"}; // Example category for sensor 2
bool answers2[] = {false, true, false, true, false}; // Example answers for sensor 2

String features[5] = {"Jupiter's Great Red Spot is a massive storm that has been raging for centuries ", 
"The Great Red Spot is not as big as Earth", 
"Jupiter's gravity pulls in asteroids and comets, protecting Earth from potential impacts",
"The composition of Jupiters core is still unknown",
"Jupiter's atmosphere is composed primarily of carbon dioxide"}; // Example category for sensor 3
bool answers3[] = {true, false, true, true, false};
String currentQuestion;
bool currentAnswer;
int points=1;
int sensor3State = 0, lastState=0;
int sensor2State = 0, last2State=0;
int sensor1State = 0, last1State=0;

#define LEDPIN 13
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // Set the pinMode for breakbeam sensors
  pinMode(trueButtonPin, INPUT_PULLUP);
  pinMode(falseButtonPin, INPUT_PULLUP);
  pinMode(LEDPIN, OUTPUT);
  pinMode(sensor3Pin, INPUT);     
  digitalWrite(sensor3Pin, HIGH); 
  pinMode(sensor2Pin, INPUT);     
  digitalWrite(sensor2Pin, HIGH);
  pinMode(sensor1Pin, INPUT);     
  digitalWrite(sensor1Pin, HIGH);
}

void loop() {
  sensor3State = digitalRead(sensor3Pin);
  sensor1State = digitalRead(sensor1Pin);
  sensor2State = digitalRead(sensor2Pin);
  if (sensor3State == LOW) {     
    // turn LED on:
    digitalWrite(LEDPIN, HIGH);  
  } 
  else {
    // turn LED off:
    digitalWrite(LEDPIN, LOW); 
  }
  
  if (sensor3State && !lastState) {
    Serial.println("Unbroken");
  } 
  if (!sensor3State && lastState) {
     displayQuestion(size, answers1);
  }
  lastState = sensor3State;
    
  if (sensor2State == LOW) {     
    // turn LED on:
    digitalWrite(LEDPIN, HIGH);  
  } 
  else {
    // turn LED off:
    digitalWrite(LEDPIN, LOW); 
  }
  
  if (sensor2State && !last2State) {
    Serial.println("Unbroken");
  } 
  if (!sensor2State && last2State) {
     displayQuestion(moons, answers2);
  }
  last2State = sensor2State;

    if (sensor1State == LOW) {     
    // turn LED on:
    digitalWrite(LEDPIN, HIGH);  
  } 
  else {
    // turn LED off:
    digitalWrite(LEDPIN, LOW); 
  }
  
  if (sensor1State && !last1State) {
    Serial.println("Unbroken");
  } 
  if (!sensor1State && last1State) {
     displayQuestion(features, answers1);
  }
  last1State = sensor1State;
  if (digitalRead(trueButtonPin) == LOW) {
    checkAnswer(true);
  }
  
  // Check if the false button is pressed
  if (digitalRead(falseButtonPin) == LOW) {
    checkAnswer(false);
  }
  // Add some delay to avoid continuous reading
  delay (100);
  

}

void displayQuestion(String category[], bool answers[]) 
{
  // Generate a random index within the size of the category array
 int randomIndex = random(5);

  // Display the question at the random index
  
  Serial.println(category[randomIndex]);

  // Store the correct answer
  currentAnswer = answers[randomIndex];
}
void checkAnswer(bool userAnswer) 
{
  // Check if the user's answer matches the correct answer
 if (userAnswer == currentAnswer) {
    Serial.print("Correct!");
    Serial.println(points);
    points++; // Increment points if the answer is correct
    if (points > 3) {
      points = 1; // Reset points
    }
  } else {
    Serial.println("Incorrect!");
  }
  delay (100);
}
