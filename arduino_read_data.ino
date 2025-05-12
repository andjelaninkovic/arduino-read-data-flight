#include <TinyGPS++.h>
#include <SPI.h>
#include <SD.h>

TinyGPSPlus gps;

const int chipSelect = 53;
File logFile;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);

  Serial.println("System startup...");

  if (!SD.begin(chipSelect)) {
    Serial.println("Error initializing SD card!");
    while (true);
  }

  // Creating unique file for every flight
  int fileIndex = 0;
  String fileName;
  do {
    fileName = "GPS"+String(fileIndex++)+".csv";
  } while (SD.exists(fileName));

  logFile = SD.open(fileName, FILE_WRITE);
  if (logFile) {
    logFile.println("Time,Latitude,Longitude,Altitude(m),Satellites,HDOP,Speed(km/h)");
    logFile.flush();
    Serial.println("Created: "+fileName);
  } else {
    Serial.println("Couldn't open file!");
    while (true);
  }
}

void loop() {
  while (Serial1.available() > 0) {
    gps.encode(Serial1.read());

    if (gps.location.isUpdated() &&
        gps.altitude.isUpdated() &&
        gps.satellites.isUpdated() &&
        gps.hdop.isUpdated() &&
        gps.speed.isUpdated()) {

      float lat = gps.location.lat();
      float lon = gps.location.lng();
      float alt = gps.altitude.meters();
      int sats = gps.satellites.value();
      float hdop = gps.hdop.hdop();
      float speed = gps.speed.kmph();

      String dataString = String(gps.time.hour()) + ":" +
                          String(gps.time.minute()) + ":" +
                          String(gps.time.second()) + "," +
                          String(lat, 6) + "," +
                          String(lon, 6) + "," +
                          String(alt, 2) + "," +
                          String(sats) + "," +
                          String(hdop, 2) + "," +
                          String(speed, 2);

      logFile.println(dataString);
      logFile.flush();
      Serial.println("Recorded: " + dataString);
    }
  }
}
