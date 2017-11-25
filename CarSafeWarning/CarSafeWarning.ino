/*
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4
*/
#include <SPI.h>
#include <SD.h>

#define LATITUDE "Lat"
#define LONGITUDE "Lon"
File myFile;


int numberOfValue = 1;
String numberOfLatAndLon_str;
int numberOfLatAndLon;



float Lat1 = 10.770467;
float Lon1 = 106.658204;
float Lat2 = 10.763794;
float Lon2 = 106.660052;

String Lat_str;
String Lon_str;
float Lat[10];
float Lon[10];
void setup() {
  Serial.begin(9600);
  /*
  initSDCard();
  writeFileSDCard("Number.txt",String(numberOfValue));
  checkNumberOfLatAndLon();
  SD.remove("Number.txt");
  //getDistanceBetween2Points(Lat1,Lon1,Lat2,Lon2);
  //Ghi toa do moi vao the nho
  writeLatAndLonToSDCard(LATITUDE,Lat1);
  writeLatAndLonToSDCard(LONGITUDE,Lon1);
  Serial.println("Doc toa do: ");
  readAllLatAndLonFromSDCard();
  getDistanceBetween2Points(Lat[1],Lon[1],Lat2,Lon2);
  SD.remove("Lat1.txt");
  SD.remove("Lon1.txt");
  */
  
  /*
   * //getDistanceBetween2Points(Lat1,Lon1,Lat2,Lon2);
  */
}

void loop() {
  // nothing happens after setup
}

void initSDCard (void){
  Serial.print("Initializing SD card...");
  if (!SD.begin(4)) {
    Serial.println("Failed!");
    return;
  }
  Serial.println("Done.");
}

String readFileSDCard (String fileName){
  String result;
  myFile = SD.open(fileName);
  if (myFile) {
    while (myFile.available()) {
      char a = myFile.read();
      if(a != '\n' && a != 13){
        result += a;
      }
    }
    myFile.close();
  } else {
    Serial.println("error read SD card");
  }
  return result;
}

void writeFileSDCard (String fileName, String detail){
  myFile = SD.open(fileName, FILE_WRITE);
  if (myFile) {
    myFile.println(detail);
    myFile.close();
    Serial.println("Wrote successfully");
  } else {
    Serial.println("Wrote Failed");
  }
}

void checkNumberOfLatAndLon(void){
  numberOfLatAndLon_str = readFileSDCard("Number.txt");
  numberOfLatAndLon = numberOfLatAndLon_str.toInt();
  Serial.print("So toa do da luu: ");
  Serial.println(numberOfLatAndLon);
}

void writeLatAndLonToSDCard (String type, float coordinate){
  String fileName = type + numberOfLatAndLon_str + ".txt";
  Serial.println(fileName);
  writeFileSDCard(fileName,String(coordinate,10));
}

void readAllLatAndLonFromSDCard (void){
  int i;
  String fileName;
  for(i = 1 ; i <= numberOfLatAndLon; i++){
    fileName = "Lat" + String(i) +".txt";
    Lat_str = readFileSDCard(fileName);
    Serial.println(Lat_str);
    Lat[i] = convertStringToFloat(Lat_str);
    Serial.println(Lat[i]);
  }
  for(i = 1 ; i <= numberOfLatAndLon; i++){
    fileName = "Lon" + String(i) +".txt";
    Lon_str = readFileSDCard(fileName);
    Serial.println(Lon_str);
    Lon[i] = convertStringToFloat(Lon_str);
    Serial.println(Lon[i]); 
  }
}

double dec2rad(double deg){
  return (deg*(PI/180));
}

float convertStringToFloat (String detail){
  int i;
  char detailArray[10];
  detail.toCharArray(detailArray, 10);
  Serial.print("Chuyen qua array: ");
  Serial.println(detailArray);
  float result;
  int positionOfDot = detail.indexOf(".");
  Serial.print("vi tri dau cham: ");
  Serial.println(positionOfDot);
  
  for (i=0; i < positionOfDot;i++){
     result += (detailArray[i] - 48)* pow(10,positionOfDot - 1 - i); 
  }
  for (i = positionOfDot+1; i <= 9; i++){
     result += (detailArray[i] - 48)* pow(10,positionOfDot - i);
  }
  return result;
}

double getDistanceBetween2Points (double Lat1, double Lon1, double Lat2,double Lon2){
  double R = 6371;
  double dLat_dec = Lat2 - Lat1;
  double dLat = dec2rad(dLat_dec);
  double dLon_dec = Lon2 - Lon1;
  double dLon = dec2rad(dLon_dec);
  double a = sin(dLat/2) * sin(dLat/2) + cos(dec2rad(Lat1))*cos(dec2rad(Lat2))*sin(dLon/2)*sin(dLon/2);
  double b = 2 * atan2(sqrt(a),sqrt(1-a));
  double c = R*b*1000;
  Serial.println(c,10);
  return c;
}



