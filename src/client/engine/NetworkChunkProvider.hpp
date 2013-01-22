#ifndef _ENGINE_NETWORKCHUNKPROVIDER_H_
#define _ENGINE_NETWORKCHUNKPROVIDER_H_

#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/asio.hpp>
#include "engine/ChunkProvider.hpp"
#include "engine/NetworkListner.hpp"

namespace vox {
    namespace engine {
        class NetworkChunkProvider : public ChunkProvider {
            private:
                NetworkListner _listen;
                boost::interprocess::message_queue _queue;
            public:
                //TODO: Impelent this
//                NetworkChunkProvider(boost::asio::ip::udp::socket& Listen);
                NetworkChunkProvider();
                ~NetworkChunkProvider();

                Chunk* GetChunk(int CX, int CY, int CZ);
        };
    }
}

#endif
