#define Ledpin 2

String okunan; 
String LedOn = "ledon=";
String LedOff = "ledoff=";
String Okunan_Substring;

int Int_On_delay = -1;
int Int_Off_delay = -1;


void setup() {
  Serial.begin(115200);
  Serial.println("hello");
  pinMode(Ledpin, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) { 
    okunan = Serial.readString(); 
      
    if(okunan.substring(0,6) == LedOn){ 
      Okunan_Substring = okunan.substring(6,okunan.length());
      Int_On_delay = Okunan_Substring.toInt();
      Serial.print("Led On ms: "); 
      delay(Int_On_delay);  
      Serial.println(Int_On_delay);
    }
    else if(okunan.substring(0,7) == LedOff){
      Okunan_Substring = okunan.substring(7,okunan.length());
      Int_Off_delay = Okunan_Substring.toInt();
      Serial.print("Led Off ms: "); 
      delay(Int_Off_delay);      
      Serial.println(Int_Off_delay);
      }         
    }
    if(Int_On_delay != -1 && Int_Off_delay != -1){
      digitalWrite(Ledpin, HIGH);
      delay(Int_On_delay);
      digitalWrite(Ledpin, LOW);
      delay(Int_Off_delay);
    } 
}
