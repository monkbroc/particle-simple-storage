#pragma once

/* Simple storage library by Julien Vanier <jvanier@gmail.com>
 */

#include "Particle.h"

// Utility macro to define a numerical code representing your app
// Useful if you flash your device with different apps
// Use a combination of letters within single quote and/or numbers less than 255
#define APP_CODE(a,b,c,d) ((a)<<24|(b)<<16|(c)<<8|(d))

template <class D>
class Storage
{
public:
  Storage(const D& defaultData, uint16_t address = 0)
   : defaultData(defaultData), address(address) {
  }

  void load(D &data) const {
    EEPROM.get(address, data);
    if (data.app != defaultData.app) {
      reset(data);
    }
  }

  void store(D &data) const {
    EEPROM.put(address, data);
  }

  void reset(D &data) const {
    data = defaultData;
    store(data);
  }

  size_t size() const {
    return sizeof(D);
  }

protected:
  const D& defaultData;
  const uint16_t address;
};
