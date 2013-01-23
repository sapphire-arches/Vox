#ifndef _ENGINE_INTERNALMESSAGE_H_
#define _ENGINE_INTERNALMESSAGE_H_

namespace vox {
    namespace engine {
        namespace client {
            //Every message must have this as the first element, or weirdness
            typedef enum {
                MSG_NO_MSG = 0,     //Unused, do not remove.
                MSG_QUIT = 1,       //Quit event
                MSG_CHUNK_REQ = 2,  //Chunk request message.
            } MessageType;
            
            struct Message {
                MessageType Type;
                union {
                    struct QuitMessage {} Quit;
                    struct ChunkRequest {int X, Y, Z;} CRequest;
                } Data;
            };
        }
    }
}

#endif
