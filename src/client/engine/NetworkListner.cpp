#include "NetworkListner.hpp"
#include "engine/Chunk.hpp"

using namespace vox::engine;
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
    message_queue _chunkMQ(create_only, MQ_CHUNK_OUT, 4, CHUNK_BLOCKS * sizeof (Block));
}
