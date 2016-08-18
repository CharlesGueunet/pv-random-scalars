#include "vtkRandomScalars.h"

#include "vtkDataSet.h"
#include "vtkDataArray.h"
#include "vtkFloatArray.h"
#include "vtkInformation.h"
#include "vtkInformationVector.h"
#include "vtkObjectFactory.h"
#include "vtkPointData.h"

#include <random>

vtkStandardNewMacro(vtkRandomScalars);

// Public
// {{{

//----------------------------------------------------------------------------
void vtkRandomScalars::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
}

// }}}
// Protected
// {{{

//----------------------------------------------------------------------------
vtkRandomScalars::vtkRandomScalars()
{
  this->MaxValue = 0;
}

//----------------------------------------------------------------------------
vtkRandomScalars::~vtkRandomScalars()
{
}

int vtkRandomScalars::FillOutputPortInformation(int port, vtkInformation* info)
{
  switch (port)
    {
    case 0:
      info->Set(vtkDataObject::DATA_TYPE_NAME(), "vtkDataSet");
      break;
    default:
      info->Set(vtkDataObject::DATA_TYPE_NAME(), "vtkDataObject");
      break;
    }

  return 1;
}

int vtkRandomScalars::RequestData(vtkInformation*        request,
                          vtkInformationVector** inputVector,
                          vtkInformationVector*  outputVector)
{

  vtkDataSet* inputData = vtkDataSet::GetData(inputVector[0]);

  vtkInformation* outputInfo = outputVector->GetInformationObject(0);
  vtkDataSet*     outputData =
      vtkDataSet::SafeDownCast(outputInfo->Get(vtkDataObject::DATA_OBJECT()));
  // this plugin does not modify the input
  outputData->ShallowCopy(inputData);

  // number of scalar values
  const auto &nbScalars = inputData->GetNumberOfPoints();

  // random scalar array
  vtkDataArray* randScalars = vtkFloatArray::New();
  randScalars->SetName("RandomScalars");
  randScalars->SetNumberOfTuples(nbScalars);

  // random generation
  std::random_device rd;     // only used once to initialise (seed) engine
  std::mt19937 rng(rd());    // random-number engine used : Mersenne-Twister

  // fill array
  for (unsigned i = 0; i < nbScalars; i++) {
      std::uniform_real_distribution<float> uni(0, MaxValue);
      const auto&                          randScalar = uni(rng);
      randScalars->SetTuple1(i, randScalar);
  }

  // Add array in output
  outputData->GetPointData()->AddArray(randScalars);

  return 1;
}

// }}}
