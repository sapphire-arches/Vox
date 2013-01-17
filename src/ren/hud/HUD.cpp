#include "HUD.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <string>

using namespace std;
using namespace vox::ren::hud;

HUD::HUD(vox::engine::entity::PlayerEntity& Moniter) : 
    _moniter(Moniter),
    _prog("res/ui.frag", "res/ui.vert"){
    
    string m("MView");
    string p("MProj");
    _mloc = _prog.GetUniformLoc(m);
    _ploc = _prog.GetUniformLoc(p);

    _proj = glm::ortho(0.f, 800.f, 600.f, 0.f, -1.f, 10.f);
    _mview = glm::mat4(1.f);
}

HUD::~HUD() {
}

static void Draw2DBox(float x1, float y1, float x2, float y2, float Layer) {
    glVertex3f(x1, y1, Layer);
    glVertex3f(x2, y1, Layer);
    glVertex3f(x2, y2, Layer);
    glVertex3f(x1, y2, Layer);
}

#define LAYER_DATA 0.1f
#define LAYER_BACK 0.2f

void HUD::Render() {
    _prog.Use();
    glUniformMatrix4fvARB(_mloc, 1, GL_FALSE, glm::value_ptr(_mview));
    glUniformMatrix4fvARB(_ploc    , 1, GL_FALSE, glm::value_ptr(_proj));

    float lvl = _moniter.GetJetpackLevel() / 10.f;
    glBegin(GL_QUADS);
        glColor3f(0.2, 0.2, 0.2);
        Draw2DBox(0., 585., 110., 600., LAYER_DATA);
        glColor3f(1., 0., 0.);
        Draw2DBox(5., 590., 100. * lvl + 5., 600., LAYER_BACK);
    glEnd();
}
