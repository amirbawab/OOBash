#include <easycc/EasyCCDev.h>
#include <iostream>
#include <bashclass/BashClass.h>

int main(int argc, char *argv[]) {

    // Create an easycc developer mode instance
    ecc::EasyCC easyCC;
    int code;
    code = easyCC.init(argc, argv);
    if(code != ecc::EasyCC::OK_CODE) {
        return code;
    }

    // Create a bash class instance to hold the structure of the code
    BashClass bashClass;
    bashClass.initHandlers();

    // Start registering semantic actions handlers
    easyCC.registerSemanticAction("#startClass#", bashClass.m_startClass);
    easyCC.registerSemanticAction("#className#", bashClass.m_className);
    easyCC.registerSemanticAction("#endClass#", bashClass.m_endClass);

    std::vector<int> phases = {BashClass::PHASE_CREATE, BashClass::PHASE_EVAL_GEN};
    for(int phase : phases) {

        // Set the phase number
        easyCC.setParsingPhase(phase);

        // Show error message on create phase only
        easyCC.setSilentSyntaxErrorMessages(phase != BashClass::PHASE_CREATE);

        // Compile all files passed as arguments
        for(std::string fileName : easyCC.getInputFilesNames()) {
            code = easyCC.compile(fileName);
            if(code != ecc::EasyCC::OK_CODE) {
                return code;
            }
        }
    }
}