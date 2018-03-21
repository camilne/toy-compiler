#ifndef MIPS_DEFINES_HPP
#define MIPS_DEFINES_HPP

namespace mips {
  /// The number of saved registers on a mips machine.
  static const int NUM_SAVED_REGISTERS = 8;
  /// The number of tmp registers on a mips machine.
  static const int NUM_TMP_REGISTERS = 8;
  /// The total number of registers on a mips machine.
  static const int NUM_REGISTERS = 32;
  /// The register number of the first saved register.
  static const int SAVE_BEGIN = 1;
  /// The register number 1 after the last saved register.
  static const int SAVE_END = 9;
  /// The register number of the first tmp register.
  static const int TMP_BEGIN = 9;
  /// The register number 1 after the last tmp register.
  static const int TMP_END = 17;
}

#endif
