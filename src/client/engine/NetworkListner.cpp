#include "NetworkListner.hpp"
#include <iostream>

using namespace vox::engine;
using namespace boost::asio;
using namespace boost::asio::ip;

NetworkListner::NetworkListner(const ip::udp::endpoint Endpoint, World& W) :
     ChunkProvider()
    , _service()
    , _world(W)
    , _TEMPTHINGY(100) {
    _TEMPBLOCKS = new Block[CHUNK_BLOCKS];
    _sock = new ip::udp::socket(_service, Endpoint);
    if (_sock->is_open()) {
        std::cout << "We have an open socket to the server!" << std::endl;
    } else {
        std::cerr << "We couldn't open a connection to the server =(" << std::endl;
        exit(-1);
    }
}

NetworkListner::~NetworkListner() {
    delete _sock;
    delete[] _TEMPBLOCKS;
    int qcount;
    if ((qcount = _service.poll()) > 0) {
        std::cout << "Client network listner service object has " << qcount << " more tasks." << std::endl;
        _service.run();
    }
    _service.stop();
}

Chunk* NetworkListner::GetChunk(int CX, int CY, int CZ) {
    _TEMPTHINGY.Fill(CX, CY, CZ, _TEMPBLOCKS);
    return new Chunk(CX, CY, CZ, _TEMPBLOCKS);
}

void NetworkListner::HandleEvents(vox::state::Gamestate& GS) {
}
