#include "synch.h"
//implement by one lock and two sem
class BoundedBuffer {
   public:
     // create a bounded buffer with a limit of 'maxsize' bytes
     BoundedBuffer(int maxsize);
     ~BoundedBuffer();

     // read 'size' bytes from the bounded buffer, storing into 'data'.
     // ('size' may be greater than 'maxsize')
     void Read(void *data, int size);

     // write 'size' bytes from 'data' into the bounded buffer.
     // ('size' may be greater than 'maxsize')
     void Write(void *data, int size);
   private:
     // void *buffer;
     int *buffer;
     Lock *lock;
     Condition *bufferFull;
     Condition *bufferEmpty;
     int bsize;
     int count;
     int nextRead;
     int nextWrite;
     // ???
};

