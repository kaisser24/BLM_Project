//This is the file for wireless communication between the arduino and the web app
//#include <string>
//sample data
int dataArray[] = {120, 132, 124, 157, 170};
String input = "";
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(1000); //delay to allow serial monitor to initialize
  Serial.flush();
}
void loop() {
  while(Serial.available()){
    input = Serial.readStringUntil('\n');
    if(input == "t" || sizeof(dataArray) != 0){
      Serial.println("start");
      for(int i=0;i<5;i++){
        Serial.println(dataArray[i]);
      }
      Serial.println("end");
    }
    else{
      Serial.println("none");
    }
  }
}
