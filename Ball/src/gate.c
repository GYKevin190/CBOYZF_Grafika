#include "gate.h"

void init_gate(Gate *gate)
{
    load_model(&(gate->gate), "assets/models/soccer_gate.obj");
    gate->gate_texture = load_texture("assets/textures/gate.jpg");
}