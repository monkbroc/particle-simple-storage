// Example usage for Simple storage library by Julien Vanier

#include "simple-storage.h"

/* Add a version field if you need to do custom version migrations of
 * the config as you add new fields
 */
struct Config {
    uint32_t app;
    uint16_t version;
    int gain;
    int limit;
    int count;
} config;

Config defaultConfig = {
    /* app */ APP_CODE('M','F', 0, 1),
    /* version */ 3,    // Started at 1
    /* gain */ 100,     // This field was always there
    /* limit */ 30000,  // This field added in version 2
    /* count */ 0,      // This field added in version 3
};

Storage<Config> storage(defaultConfig);

void setup() {
    storage.load(config);
    migrateConfig();
}

void migrateConfig() {
  if (config.version == defaultConfig.version) {
    // no need to migrate config
    return;
  }

  switch (config.version) {
    case 1:
      // Add new fields for version 2
      config.limit = defaultConfig.limit;
      // FALL THROUGH: code continues executing on next line
    case 2:
      // Add new fields for version 3
      config.count = defaultConfig.count;
      // FALL THROUGH: code continues executing on next line
  }
        
  config.version = defaultConfig.version;
  storage.store(config);
}

void loop() {
}
