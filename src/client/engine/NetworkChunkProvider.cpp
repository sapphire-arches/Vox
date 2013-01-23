#include "NetworkChunkProvider.hpp"
#include "InternalMessage.hpp"

using namespace vox::engine;
using namespace boost::interprocess;

NetworkChunkProvider::NetworkChunkProvider() : _listen() {
    _in = new message_queue(open_only, MQ_CHUNK_OUT);
    message_queue::remove(MQ_CHUNK_REQ);
    _req = new message_queue(create_only, MQ_CHUNK_REQ, 16, sizeof(vox::engine::client::Message));
}

NetworkChunkProvider::~NetworkChunkProvider() {
    message_queue::remove(MQ_CHUNK_OUT);
    client::Message disconnect;
    disconnect.Type = client::MSG_QUIT;
    //Higher priority so that we are sent before extra processing.
    _req->send(&disconnect, sizeof(client::Message), 10);
    delete _in;
    delete _req;
}

Chunk* NetworkChunkProvider::GetChunk(int CX, int CY, int CZ) {
    client::Message msg;
    msg.Type = client::MSG_CHUNK_REQ;
    msg.Data.CRequest.X = CX;
    msg.Data.CRequest.Y = CY;
    msg.Data.CRequest.Z = CZ;
    //TODO: replace this with code that computes priority of request.
    _req->send(&msg, sizeof(client::Message), 0);
    return NULL;
}
