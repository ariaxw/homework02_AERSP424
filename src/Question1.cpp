#include <iostream>
#include <string>
#include <vector>
#include <memory>

// Implement an abstract base class “Sensor”
class Sensor {
public:
    virtual ~Sensor() = default;
    virtual void gatherData() const = 0;
    virtual void processData() const = 0;
    virtual std::string getType() const = 0; // Add method to get sensor type
};

// Temperature Sensor
class TemperatureSensor : public Sensor {
public:
    TemperatureSensor() {
        std::cout << "sensor created " << this << " of type \"Temperature\"" << std::endl;
    }
    ~TemperatureSensor() override {
        std::cout << "sensor deleted " << this << " of type \"Temperature\"" << std::endl;
    }
    void gatherData() const override {
        std::cout << "Gathering data from Temperature Sensor." << std::endl;
    }
    void processData() const override {
        std::cout << "Processing data from Temperature Sensor." << std::endl;
    }
    std::string getType() const override {
        return "Temperature";
    }
};

// Altitude Sensor
class AltitudeSensor : public Sensor {
public:
       AltitudeSensor() {
           std::cout << "sensor created " << this << " of type \"Altitude\"" << std::endl;
       }
       ~AltitudeSensor() override {
           std::cout << "sensor deleted " << this << " of type \"Altitude\"" << std::endl;
       }
       void gatherData() const override {
           std::cout << "Gathering data from Altitude Sensor." << std::endl;
       }
       void processData() const override {
           std::cout << "Processing data from Altitude Sensor." << std::endl;
       }
       std::string getType() const override {
           return "Altitude";
       }
};

// Airspeed Sensor
class AirspeedSensor : public Sensor {
public:
    AirspeedSensor() {
        std::cout << "sensor created " << this << " of type \"Airspeed\"" << std::endl;
    }
    ~AirspeedSensor() override {
        std::cout << "sensor deleted " << this << " of type \"Airspeed\"" << std::endl;
    }
    void gatherData() const override {
        std::cout << "Gathering data from Airspeed Sensor." << std::endl;
    }
    void processData() const override {
        std::cout << "Processing data from Airspeed Sensor." << std::endl;
    }
    std::string getType() const override {
        return "Airspeed";
    }
};

// Create another class named “SensorFactory”
class SensorFactory {
public:
    static std::unique_ptr<Sensor> createSensor(const std::string& type) {
        if (type == "Temperature") {
            return std::make_unique<TemperatureSensor>();
        } else if (type == "Altitude") {
            return std::make_unique<AltitudeSensor>();
        } else if (type == "Airspeed") {
            return std::make_unique<AirspeedSensor>();
        }
        return nullptr;
    }
};

// Implement a control system class “AerospaceControlSystem”
class AerospaceControlSystem {
private:
    std::vector<std::unique_ptr<Sensor>> sensors;

public:
    void addSensor(std::unique_ptr<Sensor> sensor) {
        if (sensor) {
            sensors.push_back(std::move(sensor));
        }
    }

    void monitorAndAdjust() const {
        for (const auto& sensor : sensors) {
            sensor->gatherData();
            sensor->processData();
            std::cout << "Adjusting controls based on sensor data." << std::endl;
        }
    }
    void clearSensors() {
           sensors.clear(); // This will explicitly destroy all sensors
       }
};


int main() {
    std::cout << "#################### Question 01 ####################" << std::endl;

    AerospaceControlSystem ctrlSys;

    // Add sensors
    ctrlSys.addSensor(SensorFactory::createSensor("Temperature"));
    ctrlSys.addSensor(SensorFactory::createSensor("Altitude"));
    ctrlSys.addSensor(SensorFactory::createSensor("Airspeed"));

    // Monitor and adjust
    ctrlSys.monitorAndAdjust();
    
    // Clear sensors to ensure they are deleted before the end marker
    ctrlSys.clearSensors();

    std::cout << "#################### End Question 01 ####################" << std::endl;
    return 0;
}
