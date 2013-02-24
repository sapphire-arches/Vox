#include "HUD.hpp"
#include "state/GameState.hpp"
#include "GraphicsDefs.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <string>

using namespace std;
using namespace vox::ren::hud;
using namespace vox::engine;

HUD::HUD(vox::engine::entity::PlayerEntity& Moniter) : 
    _moniter(Moniter),
    _prog("res/ui.frag", "res/ui.vert"){
    
    string m("MView");
    string p("MProj");
    _mloc = _prog.GetUniformLoc(m);
    _ploc = _prog.GetUniformLoc(p);

    _proj = glm::ortho(0.f, WIDTH, HEIGHT, 0.f, -1.f, 10.f);
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

static void DrawStat(Stat<float> S, float x1, float y1, float width, float height, float Layer) {
    glColor3f(0., 0., 1.);
    Draw2DBox(x1, y1, x1 + width * S.Max, y1 + height, Layer - 2);
    glColor3f(0., 1., 0.);
    Draw2DBox(x1, y1, x1 + width * S.Current, y1 + height, Layer - 1);
    glColor3f(1., 0., 0.);
    Draw2DBox(x1, y1, x1 + width * S.Min, y1 + height, Layer);
}

#define LAYER_DATA 0.2f
#define LAYER_BACK 0.1f

void HUD::Render(vox::state::Gamestate* GS) {
    _prog.Use();
    glUniformMatrix4fvARB(_mloc, 1, GL_FALSE, glm::value_ptr(_mview));
    glUniformMatrix4fvARB(_ploc, 1, GL_FALSE, glm::value_ptr(_proj));

    float lvl = _moniter.GetJetpackLevel() / float(PLAYER_MAX_JETPACK);
    float health = _moniter.GetHealth() / float(PLAYER_MAX_HEALTH);
    vox::engine::Stat<float> delta = GS->GetDeltaStat();
    glBegin(GL_QUADS);
        glColor3ub(0xFD, 0xF6, 0xE3);
        Draw2DBox(0., 565., 115., 600., LAYER_BACK);
        glColor3ub(0xDC, 0x32, 0x2F);
        Draw2DBox(5., 590., 100. * lvl + 5., 600., LAYER_DATA);
        glColor3ub(0x85, 0x99, 0x00);
        Draw2DBox(5., 575., 100. * health + 5., 585., LAYER_DATA);
        DrawStat(delta, 0, 0, 100, 16, LAYER_DATA);
    glEnd();
}
