# Simple Storage

A Particle library for simple persistent storage in EEPROM.

## Usage

Define the config fields you want to store, provide default config and
load the config on boot. Store the config after you modify it.

```
#include "simple-storage.h"

struct Config {
    uint32_t app;
    int counter;
} config;

Config defaultConfig = {
    /* app */ APP_CODE('C','N', 'T', 1),
    /* counter */ 0,
};

Storage<Config> storage(defaultConfig);

void setup() {
    storage.load(config);
}

void loop() {
  config.counter++;
  if (config.counter % 1000 == 0) {
    storage.store(counter);
  }
}
```

See the [examples](examples) folder for more details.

## Documentation

TODO: Describe `Storage`

## LICENSE
Copyright 2017 Julien Vanier <jvanier@gmail.com>

Licensed under the MIT license
