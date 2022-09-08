#pragma once

#include "core/titanscript/scriptnode.h"
#include "vector.h"

class NodeManager {
   public:
    static void AddNode(ScriptNode *n) { nodes.push_back(n); }

    static void Free() {
        for (int c = 0; c < nodes.size(); c++) delete nodes[c];

        nodes.clear();
    }

   private:
    static Vector<ScriptNode> nodes;
};
