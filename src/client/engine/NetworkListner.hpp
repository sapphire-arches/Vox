#ifndef _CLIENT_ENGINE_NETWORKLISTNER_H_
#define _CLIENT_ENGINE_NETWORKLISTNER_H_

#define MQ_CHUNK_OUT "ClientChunkQueue"
#define MQ_CHUNK_REQ "ClientChunkRequestQueue"

#include <boost/thread/thread.hpp>
#include <boost/interprocess/ipc/message_queue.hpp>

namespace vox {
    namespace engine {
        class NetworkListner {
            private:
                boost::thread _thread;

                //Not copyable.
                NetworkListner(const NetworkListner& Other);
                NetworkListner& operator= (const NetworkListner& Other);
            public:
                NetworkListner();
                ~NetworkListner();

                bool IsRunning();
        };
    }
}

#endif
