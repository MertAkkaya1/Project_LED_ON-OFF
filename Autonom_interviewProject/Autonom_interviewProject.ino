#define Ledpin 2

String okunan; 
String LedOn = "ledon=";
String LedOff = "ledoff=";
String Start = "start";
String Stop = "stop";
String Okunan_Substring;
String serial_read_Substring;
String serial_read_Substring_On;
String serial_read_Substring_Off;
String serial_read;

int Int_On_delay = -1;
int Int_Off_delay = -1;


void setup() {
  Serial.begin(115200);
  
  pinMode(Ledpin, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    okunan = Serial.readString();
  }       
  if (okunan.substring(0, 4) == Stop) {
    //Serial.println(okunan);
    Normal_Mode();
  }
  if (okunan.substring(0, 5) == Start) {
    Echo_Mode();
  }
}

void Normal_Mode(){
  Serial.println("Normal Mode Active");
  digitalWrite(Ledpin, HIGH);
  delay(1000);
  digitalWrite(Ledpin, LOW);
  delay(1000);
}

void Echo_Mode(){
  Serial.println("Echo Mode Active");

  if (Serial.available() > 0) {
    serial_read = Serial.readString();
    if (serial_read.substring(0, 6) == LedOn) {
      serial_read_Substring_On = serial_read.substring(6, serial_read.length());
      Int_On_delay = serial_read_Substring_On.toInt();
      Serial.print("Led On ms: ");
      //delay(Int_On_delay);
      Serial.println(Int_On_delay);
    }
    //serial_read = Serial.readString();
    else if (serial_read.substring(0, 7) == LedOff) {
      serial_read_Substring_Off = serial_read.substring(7, serial_read.length());
      Int_Off_delay = serial_read_Substring_Off.toInt();
      Serial.print("Led Off ms: ");
      //delay(Int_Off_delay);
      Serial.println(Int_Off_delay);
    }
    if (Int_On_delay != -1 && Int_Off_delay != -1) {
      digitalWrite(Ledpin, HIGH);
      delay(Int_On_delay);
      digitalWrite(Ledpin, LOW);
      delay(Int_Off_delay);
    }
  }
}
