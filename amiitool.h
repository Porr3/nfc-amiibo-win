#include <stdint.h>
#include <stdlib.h>

class Amiitool {
public:
  Amiitool();
  int decryptBuffer(uint8_t encryptedBuffer[], uint8_t *decryptedBuffer);
  int encryptBuffer(uint8_t encryptedBuffer[], uint8_t *decryptedBuffer);

  static Amiitool *shared();
  static void setKeyPath(const char *keyPath);

  void printHex(const uint8_t *buffer, const size_t size);

private:
  static Amiitool *_shared;
  static const char *_keyPath;
};
