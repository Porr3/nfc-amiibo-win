#include "amiitool.h"
#include "amiibo.h"

#include <amiitool_lib.h>

#include <stdio.h>
#include <string.h>
#ifndef _MSC_VER
#include <unistd.h>
#endif

Amiitool *Amiitool::_shared = NULL;
const char *Amiitool::_keyPath = NULL;

Amiitool *Amiitool::shared() {
  if (!_shared) { _shared = new Amiitool(); }

  return _shared;
}

void Amiitool::setKeyPath(const char *keyPath) {
  Amiitool::_keyPath = keyPath;
}

Amiitool::Amiitool() {}

int Amiitool::decryptBuffer(uint8_t *encryptedBuffer, uint8_t *decryptedBuffer) {
  printf("\nDecrypting bin\n");
  int ret = decrypt(Amiitool::_keyPath, encryptedBuffer, decryptedBuffer, AMIIBO_SIZE, AMIIBO_SIZE);
  return ret;
}

int Amiitool::encryptBuffer(uint8_t *encryptedBuffer, uint8_t *decryptedBuffer) {
  printf("Encrypting\n");
  int ret = encrypt(Amiitool::_keyPath, decryptedBuffer, encryptedBuffer, AMIIBO_SIZE, AMIIBO_SIZE);
  return ret;
}

void Amiitool::printHex(const uint8_t *buffer, const size_t size) {
  size_t i;

  for (i = 0; i < size; i++) {
    printf("%02x  ", buffer[i]);
  }
  printf("\n");
}
