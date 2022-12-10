#include <stdlib.h>
#include <nfc/nfc-types.h>

#define UUID_SIZE 7

class Amiibo;

class NFCHandler {
public:
  NFCHandler();
  ~NFCHandler();
  bool readTagUUID(uint8_t uuidBuffer[]);
  bool writeAmiibo(Amiibo *amiibo);

private:
  nfc_target target;
  nfc_context *context;
  nfc_device *device;

  void writeBuffer(const uint8_t buffer[]);
  void writePage(uint8_t page, const uint8_t buffer[]);
  void writeDataPages(const uint8_t buffer[]);
  void writeDynamicLockBytes();
  void writeStaticLockBytes();
};
