#include "NetworkChunkProvider.hpp"

using namespace vox::engine;
using namespace boost::interprocess;

NetworkChunkProvider::NetworkChunkProvider() : _listen(), _queue(open_only, MQ_CHUNK_OUT) {
}

NetworkChunkProvider::~NetworkChunkProvider() {
    message_queue::remove(MQ_CHUNK_OUT);
}

Chunk* NetworkChunkProvider::GetChunk(int CX, int CY, int CZ) {
    return NULL;
}
