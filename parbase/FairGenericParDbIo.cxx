/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "FairGenericParDbIo.h"
#include "FairParSet.h"

#pragma GCC diagnostic push 
#pragma GCC diagnostic ignored "-Wshadow"

#include "TGenBaseClient/Client.h"
#include "TGenBaseClient/FairParameter.h"
#include "TGenBaseClient/Streamer.h"

#pragma GCC diagnostic pop

ClassImp(FairGenericParDbIo)

FairGenericParDbIo::FairGenericParDbIo(FairParDbIo* parIo)
  : FairDetParIo()
{
  fParIo = parIo;
  fName = "FairGenericParIo";
}

Bool_t FairGenericParDbIo::init(FairParSet* pPar)
{
  return read(pPar);
}

Bool_t FairGenericParDbIo::read(FairParSet *pPar) {
  // // generic read function for parameter containers
  // Text_t *name = const_cast<char*>(pPar->GetName());
  // Int_t version = findInputVersion(name);

  // // cout << "-I- FairDetParRootFileIo#  " << name << " : " << version <<  endl;

  // if (version <= 0) {
  //   pPar->setInputVersion(-1, inputNumber);
  //   return kFALSE;
  // }

  // if (pPar->getInputVersion(inputNumber) == version &&
  //     pPar->getInputVersion(inputNumber) != -1) {
  //   return kTRUE;
  // }

  // TKey *key = dynamic_cast<TKey *>(gDirectory->GetKey(name, version));
  // if (key) {
  //   pPar->clear();
  //   key->Read(pPar);
  //   pPar->setInputVersion(version, inputNumber);
  //   pPar->setChanged();
  //   cout << "Container " << pPar->GetName() << " initialized from ROOT file."
  //        << endl;
  //   return kTRUE;
  // }
  // pPar->setInputVersion(-1, inputNumber);
  // return kFALSE;

  if (!pPar)
    return kFALSE;

  std::vector<TGenBase::FairParameter> result = TGenBase::FairParameter::GetByName(pPar->GetName());
  if (!result.size())
    return kFALSE;

  TGenBase::Streamer ParameterStreamer(result[0].GetParameter());
  if (ParameterStreamer.AsString().size())
  {
    ParameterStreamer.Fill(pPar);
    return kTRUE;
  }

  return kFALSE;
}

Int_t FairGenericParDbIo::write(FairParSet *pPar) {
  if (!pPar) return -1;

  TGenBase::FairParameter par;
  par.SetName(pPar->GetName());
  // TGenBase::Streamer ParameterStreamer(static_cast<TObject*>(pPar));
  TGenBase::Streamer ParameterStreamer(pPar);
  par.SetParameter(ParameterStreamer.AsString());
  par.Store();

  return ParameterStreamer.AsString().size() / 2;
}
