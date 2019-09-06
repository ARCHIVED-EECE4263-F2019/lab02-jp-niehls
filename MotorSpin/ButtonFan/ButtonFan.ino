const int buttonPin = D4; // the number of the pushbutton pin for speed
const int buttonPin2 = D8;// the number of the pushbutton pin for direction
const int motorIn1 = D6;
const int motorIn2 = D5;
int stat = 0;
int stat2 = 0; 
#define rank1 800
#define rank2 400
// Variables will change:
int ledState = HIGH; // the current state of the output pin
int buttonState; // the current reading from the input pin
int lastButtonState = LOW; // the previous reading from the input pin
int buttonState2; // the current reading from the input pin
int lastButtonState2 = LOW; // the previous reading from the input pin

// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime = 0; // the last time the output pin was toggled
long debounceDelay = 50; // the debounce time; increase if the output flickers
/******************************************************************************/
void setup() 
{
//set theled,motors as OUTPUT,button as INPUT
pinMode(buttonPin, INPUT);
pinMode(buttonPin2, INPUT);

pinMode(motorIn1,OUTPUT);
pinMode(motorIn2,OUTPUT);
}

void loop() {
// read the state of the switch into a local variable:
int reading = digitalRead(buttonPin);
int reading2 = digitalRead(buttonPin2);
// check to see if you just pressed the button 
// (i.e. the input went from LOW to HIGH), and you've waited 
// long enough since the last press to ignore any noise:

// If the switch changed, due to noise or pressing:
if (reading != lastButtonState) {
// reset the debouncing timer
lastDebounceTime = millis();
}
/*if (reading2 != lastButtonState2) {
// reset the debouncing timer
lastDebounceTime = millis();
}*/

if ((millis() - lastDebounceTime) > debounceDelay) {
// whatever the reading is at, it's been there for longer
// than the debounce delay, so take it as the actual current state:

// if any button state has changed:
// both pressed resets both speed and direction to default
if ((reading != buttonState)&&(reading2 != buttonState2)) {
buttonState = reading;
buttonState2 = reading2;
stat = 0;
stat2 = 0;
//}
}
// if pushbutton for speed has been pressed
// increase speed variable or reset to 0 if it goes above 2
if (reading != buttonState) {
buttonState = reading;

if (buttonState == HIGH) {
stat = stat + 1;
if(stat >= 3)
{
stat = 0;
}
}
}
// if pushbutton for direction has been pressed
// invert the direction variable(stat2) to switch direction
if (reading2 != buttonState2) {
buttonState2 = reading2;

if (buttonState2 == HIGH) {
stat2 = !stat2;
}
}
}

// Speed switch case for clockwise
if (stat2 == 0){
switch(stat)
{
case 1:
clockwise(rank1);
break;
case 2:
clockwise(rank2);
break;
default:
clockwise(0);
}
}

// Speed switch case for counterclockwise
if (stat2 == 1){
switch(stat)
{
case 1:
counterclockwise(rank1);
break;
case 2:
counterclockwise(rank2);
break;
default:
counterclockwise(0);
}
}
// save the reading. Next time through the loop,
// it'll be the lastButtonState:
lastButtonState = reading;
lastButtonState2 = reading2;
}
/***********************************************************/
void clockwise(int Speed)//
{
analogWrite(motorIn1,0);
analogWrite(motorIn2,Speed);
}
void counterclockwise(int Speed)
{
analogWrite(motorIn1,Speed);
analogWrite(motorIn2,0);
}
/***********************************************************/
