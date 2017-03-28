// Example usage for Simple storage library by Julien Vanier

#include "simple-storage.h"

/* The config you want to store
 * The first field must be called app and represents the application
 * that is using this config.
 * Always add new fields at the end.
 * NEVER delete fields in the middle after flashing your app
 * since that would shift remaining fields forward. Just rename unused
 * fields to reserved1, reserved2, etc.
 */
struct Config {
    uint32_t app;
    int gain;
    int limit;
} config;

Config defaultConfig = {
    /* app */ APP_CODE('M','F', 0, 1),
    /* gain */ 100,
    /* limit */ 30000,
};

Storage<Config> storage(defaultConfig);

void setup() {
    storage.load(config);
    Particle.function("set", updateConfig);
}

// Call Particle cloud function "set" with name=value to update a config value
int updateConfig(String arg) {
    int equalPos = arg.indexOf('=');
    if (equalPos < 0) {
        return -1;
    }
    String name = arg.substring(0, equalPos);
    String value = arg.substring(equalPos + 1);

    if (name.equals("gain")) {
        config.gain = value.toInt();
    } else if (name.equals("limit")) {
        config.limit = value.toInt();
    } else {
        return -2;
    }

    storage.store(config);
    return 0;
}

void loop() {
    Serial.printlnf("gain=%d, limit=%d", config.gain, config.limit);
    delay(1000);
}
