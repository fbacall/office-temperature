 #include "DHT.h"  
 DHT dht2(2,DHT22);  
 void setup()  
 {  
  Serial.begin(9600);  
  Serial.println("Starting");  
  dht2.begin();
 }  
 void loop()  
 {  
  // Wait a few seconds between measurements.
  delay(5000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht2.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht2.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht2.computeHeatIndex(t, h, false);

  Serial.print(F("{ \"humidity\" : "));
  Serial.print(h);
  Serial.print(F(", \"temperature\" : "));
  Serial.print(t);
  Serial.print(F(", \"heat_index\" : "));
  Serial.print(hic);
  Serial.println(F(" }"));
 } 