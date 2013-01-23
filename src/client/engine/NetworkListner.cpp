#include "NetworkListner.hpp"
#include "engine/Chunk.hpp"
#include "engine/WorldGenerator.hpp"
#include "InternalMessage.hpp"

using namespace vox::engine;
using namespace vox::engine::client;
using namespace boost::interprocess;

static void ListenFunc();

NetworkListner::NetworkListner() :
    _thread(ListenFunc) {
}

NetworkListner::~NetworkListner() {
}

bool NetworkListner::IsRunning() {
    return _thread.joinable();
}

static void ListenFunc() {
    message_queue::remove(MQ_CHUNK_OUT); //Delete from last crash.
    message_queue _chunkOut(create_only, MQ_CHUNK_OUT, 4, CHUNK_BLOCKS * sizeof (Block));
    message_queue _chunkReq(open_only, MQ_CHUNK_REQ);
    Block temp[CHUNK_BLOCKS];
    WorldGenerator g(100);

    client::Message msg;
    msg.Type = MSG_NO_MSG;
    unsigned int priority;
    message_queue::size_type recieveSize;

    while (msg.Type != MSG_QUIT) {
        _chunkReq.receive(&msg, sizeof(Message), recieveSize, priority);
        if (msg.Type == MSG_CHUNK_REQ) {
            int x = msg.Data.CRequest.X;
            int y = msg.Data.CRequest.Y;
            int z = msg.Data.CRequest.Z;
            g.Fill(x, y, z, temp);
            std::cout << "Magic" << std::endl;
            _chunkOut.send(temp, sizeof(Block) * CHUNK_BLOCKS, 0);
        } else {
            std::cout << "Network listning thread got message of type: " << msg.Type << std::endl;
        }
    }

    message_queue::remove(MQ_CHUNK_REQ);
}
