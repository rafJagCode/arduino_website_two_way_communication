int prev;
int curr;
int value = 0;
int webValue = 0;

boolean newData = false;
const byte maxLength = 5;
char webMessage[maxLength];

void setup() {
  // put your setup code here, to run once:
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(11, OUTPUT);
  prev = digitalRead(4);
  Serial.begin(9700);
  
}

void loop() {
  curr = digitalRead(4);
  
  if(prev != curr){
    if(digitalRead(5) != curr && value < 255){
      value ++;
    }else if(value > 0){
      value --;
    }
    Serial.println(value);
  }
  prev = curr;
  readWebValue();
  setValues();

  analogWrite(11, webValue);
}

void readWebValue() {
    static byte pos = 0;
    char endMarker = '\n';
    char sign;
    
    while (Serial.available() > 0 && newData == false) {
        sign = Serial.read();

        if (sign != endMarker) {
            webMessage[pos] = sign;
            pos++;
            if (pos == maxLength) {
                webMessage[pos] = '\0';
                pos = 0;
                newData = true;
            }
        }
        else {
          webMessage[pos] = '\0';
          pos = 0;
          newData = true;
        }
    }
}

void setValues(){
  if(newData == true){
    webValue = atoi(webMessage);
    value = webValue;
    newData = false;
  }
}
