//===--- APINotesWriter.h - API Notes Writer ----------------------*- C++ -*-===//
//
// This source file is part of the Swift.org open source project
//
// Copyright (c) 2014 - 2015 Apple Inc. and the Swift project authors
// Licensed under Apache License v2.0 with Runtime Library Exception
//
// See http://swift.org/LICENSE.txt for license information
// See http://swift.org/CONTRIBUTORS.txt for the list of Swift project authors
//
//===----------------------------------------------------------------------===//
//
// This file defines the \c APINotesWriter class that writes out source
// API notes data providing additional information about source code as
// a separate input, such as the non-nil/nilable annotations for
// method parameters.
//
//===----------------------------------------------------------------------===//
#ifndef SWIFT_API_NOTES_WRITER_H
#define SWIFT_API_NOTES_WRITER_H

#include "swift/APINotes/Types.h"

namespace llvm {
  class raw_ostream;
}

namespace swift {
namespace api_notes {

/// A class that writes API notes data to a binary representation that can be
/// read by the \c APINotesReader.
class APINotesWriter {
  class Implementation;
  Implementation &Impl;

public:
  APINotesWriter();
  ~APINotesWriter();

  APINotesWriter(const APINotesWriter &) = delete;
  APINotesWriter &operator=(const APINotesWriter &) = delete;

  /// Write the API notes data to the given stream.
  void writeToStream(llvm::raw_ostream &os);

  /// Add information about a specific Objective-C class.
  ///
  /// \param name The name of this class.
  /// \param info Information about this class.
  void addObjCClass(StringRef name, const ObjCContextInfo &info);

  /// Add information about a specific Objective-C property.
  ///
  /// \param className The class in which this property resides.
  /// \param name The name of this property.
  /// \param info Information about this property.
  void addObjCProperty(StringRef className, StringRef name, 
                       const ObjCPropertyInfo &info);

  /// Add information about a specific Objective-C method.
  ///
  /// \param className The class in which this method resides.
  /// \param selector The selector that names this method.
  /// \param isInstanceMethod Whether this method is an instance method
  /// (vs. a class method).
  /// \param info Information about this method.
  void addObjCMethod(StringRef className, ObjCSelectorRef selector, 
                     bool isInstanceMethod, const ObjCMethodInfo &info);
};

} // end namespace api_notes
} // end namespace swift

#endif // LLVM_SWIFT_API_NOTES_WRITER_H

