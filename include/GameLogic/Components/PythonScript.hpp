//
// Created by nicolas on 08/02/17.
//

#ifndef PANCAKE_PYTHONSCRIPT_HPP
#define PANCAKE_PYTHONSCRIPT_HPP

#include "Component.hpp"
#include <Python.h>

namespace PancakeEngine {
    class PythonScript : public Component {
    public:

    private:
        friend class GameObject;

        PythonScript() {
            FILE* fp;

            Py_Initialize();
            fp = fopen("../resources/scripts/test.py", "r");
            PyRun_AnyFile(fp, "");
        }

        ~PythonScript() {
            Py_Finalize();
        }
    };
}

#endif //PANCAKE_PYTHONSCRIPT_HPP
