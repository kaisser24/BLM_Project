//This is the file for wireless communication between the arduino and the web app
#include <map>
#include <string>
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
  map<string,int> data; //each time a shot occurs a time will be linked to a decible level
  //sample data below
  map["1:43pm"] = 120
  map["11:43am"] = 150
  map["2:43pm"] = 132
  //create iterator for map
  map<string, int>::iterator it = data.begin();
  //iterate though map until end of data
  while(it != data.end()){
    Serial.println(it->first + ", " + it->second)
  }
}

void loop() {

  
}
