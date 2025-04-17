# Aim
To measure the temperature and humidity of the environment using DHT11 sensor and ESP32, and send the data to ThingSpeak for remote monitoring

# Algorithm
1. Initialize the ESP32 WiFi module and connect to the WiFi network
2. Initialize the DHT11 sensor on GPIO4
3. Read the temperature and humidity data from the DHT11 sensor
4. Check if the readings are valid
5. Send the sensor data to ThingSpeak using HTTP POST request
6. Wait for 15 seconds before taking the next reading
7. Repeat steps 3-6 indefinitely
