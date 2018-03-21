#include "generator/MipsOptimizer.hpp"
#include "generator/MipsDefines.hpp"
#include <memory>
#include <vector>

using namespace mips;

void MipsOptimizer::optimize() {
  removeTrailingPopIfRegisterIsUnusedAfter();
}

void MipsOptimizer::removeTrailingPopIfRegisterIsUnusedAfter() {
  std::vector<int> popRegisters(NUM_REGISTERS);
  for(auto& i : popRegisters)
      i = 0;

  for(auto it = statements.rbegin(); it != statements.rend(); ++it) {
      std::shared_ptr<MipsStatement> obj = *it;
      if(std::shared_ptr<MipsPop> pop = std::dynamic_pointer_cast<MipsPop>(obj)) {
          if(pop->getRegister() < popRegisters.size()) {
              if(!popRegisters[pop->getRegister()]) {
                  statements.erase(std::next(it).base());
                  --it;
              } else {
                  --popRegisters[pop->getRegister()];
              }
          }
      } else if(std::shared_ptr<MipsPush> push = std::dynamic_pointer_cast<MipsPush>(obj)) {
          if(push->getRegister() < popRegisters.size())
              ++popRegisters[push->getRegister()];
      } else if(std::shared_ptr<MipsOp> op = std::dynamic_pointer_cast<MipsOp>(obj)) {
          if(op->getArg1Register() < popRegisters.size())
              ++popRegisters[op->getArg1Register()];
          if(op->getArg2Register() < popRegisters.size())
              ++popRegisters[op->getArg2Register()];
      }
  }
}
