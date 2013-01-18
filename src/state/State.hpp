#ifndef _STATE_STATE_H_
#define _STATE_STATE_H_

namespace vox {
    class App;

    namespace state {
        class State {
            public:
                State();
                State(State& Next);
                virtual ~State();

                virtual void Enter(App& TheApp);
                virtual void Leave(App& TheApp);
                virtual void Render(App& TheApp);
                virtual void Tick(App& TheApp);

                virtual bool Finished();
                State* GetNext();

                virtual void OnMouseClick(int Button, int X, int Y);

                State& operator= (const State& rhs);
            private:
                State* _next;
        };
    }
}

#endif
