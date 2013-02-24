#ifndef _VOX_ENGINE_NETWORKLISTNER_H_
#define _VOX_ENGINE_NETWORKLISTNER_H_

#include "engine/World.hpp"
#include "engine/ChunkProvider.hpp"
#include "engine/WorldGenerator.hpp"
#include <boost/asio.hpp>
#include <boost/bind.hpp>

namespace vox {
    namespace engine {
        class NetworkListner : public ChunkProvider {
            private:
                boost::asio::ip::udp::socket* _sock;
                boost::asio::io_service _service;
                vox::engine::World& _world;
                //Temporary stuff
                WorldGenerator _TEMPTHINGY;
                Block* _TEMPBLOCKS;
            public:
                NetworkListner(
                        const boost::asio::ip::udp::endpoint Endpoint,
                        vox::engine::World& World
                        );
                ~NetworkListner();

                virtual vox::engine::Chunk* GetChunk(int CX, int CY, int CZ);
        };
    }
}

#endif
