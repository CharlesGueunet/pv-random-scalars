// .NAME vtkRandomScalars - save a dataset on disc
// .SECTION Description
// vtkRandomScalars is a filter to save a dataset on the disk
// while using it. A typical example is saving a plane with
// random scalar-field when tracking a bug on a plugin.
// It will allow you to keep the problematic data-set.

#ifndef __vtkGenericWriter_h
#define __vtkGenericWriter_h

#include "vtkDataSetAlgorithm.h"

class VTK_EXPORT vtkRandomScalars : public vtkDataSetAlgorithm
{
public:
  static vtkRandomScalars* New();
  vtkTypeMacro(vtkRandomScalars, vtkDataSetAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent);

  vtkSetMacro(MaxValue, int);
  vtkGetMacro(MaxValue, int);

protected:
  vtkRandomScalars();
  ~vtkRandomScalars();

  // VTK Interface

  virtual int FillOutputPortInformation(int port, vtkInformation* info);

  int RequestData(vtkInformation* request,
                  vtkInformationVector** inputVector,
                  vtkInformationVector* outputVector);

  // fields

  int MaxValue;

private:
  vtkRandomScalars(const vtkRandomScalars&);  // Not implemented.
  void operator=(const vtkRandomScalars&);  // Not implemented.
};

#endif
